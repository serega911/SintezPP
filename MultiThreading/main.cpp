#include <iostream>
#include <string>
#include <windows.h>

#include <functional>
#include <thread>
#include <queue>
#include <mutex>
#include <memory>
#include <condition_variable>

typedef std::function<void()> fn_type;

class Worker
{
private:

	bool										m_enabled;
	std::condition_variable						m_cv;
	std::queue<fn_type>							m_fqueue;
	std::mutex									m_mutex;
	std::thread									m_thread;

	void thread_fn()
	{
		while ( m_enabled )
		{
			std::unique_lock<std::mutex> locker( m_mutex );
			// Ожидаем уведомления, и убедимся что это не ложное пробуждение
			// Поток должен проснуться если очередь не пустая либо он выключен
			m_cv.wait( locker, [&](){ return !m_fqueue.empty() || !m_enabled; } );
			while ( !m_fqueue.empty() )
			{
				fn_type fn = m_fqueue.front();
				// Разблокируем мютекс перед вызовом функтора
				locker.unlock();
				fn();
				// Возвращаем блокировку снова перед вызовом fqueue.empty() 
				locker.lock();
				m_fqueue.pop();
			}
		}
	}

public:

	Worker()
		:m_enabled( true ), m_fqueue(), m_thread( &Worker::thread_fn, this )
	{
	}

	~Worker()
	{
		m_enabled = false;
		m_cv.notify_one();
		m_thread.join();
	}

	void appendFn( fn_type fn )
	{
		std::unique_lock<std::mutex> locker( m_mutex );
		m_fqueue.push( fn );
		m_cv.notify_one();
	}

	size_t getTaskCount()
	{
		std::unique_lock<std::mutex> locker( m_mutex );
		return m_fqueue.size();
	}

	bool   isEmpty()
	{
		std::unique_lock<std::mutex> locker( m_mutex );
		return m_fqueue.empty();
	}

};

typedef std::shared_ptr<Worker> worker_ptr;


class ThreadPool
{
private:

	std::vector<worker_ptr> m_workers;

	worker_ptr getFreeWorker()
	{
		worker_ptr pWorker;
		size_t minTasks = UINT32_MAX;
		for ( auto &it : m_workers )
		{
			if ( it->isEmpty() )
			{
				return it;
			}
			else if ( minTasks > it->getTaskCount() )
			{
				minTasks = it->getTaskCount();
				pWorker = it;
			}
		}
		return pWorker;
	}

public:

	ThreadPool( size_t threads = 1 )
	{
		if ( threads == 0 )
			threads = 1;
		for ( size_t i = 0; i < threads; i++ )
		{
			worker_ptr pWorker( new Worker );
			m_workers.push_back( pWorker );
		}
	}

	~ThreadPool()
	{
	}

	template<class _T>
	struct AData
	{
		AData() :ready( false ){}
		bool ready;
		_T data;
	};

	template<class _FN, class... _ARGS>
	void runAsync( _FN _fn, _ARGS... _args )
	{
		getFreeWorker()->appendFn( std::bind( _fn, _args... ) );
	}

	template<class _R, class _FN, class... _ARGS>
	std::shared_ptr<AData<_R>> runAsync( _FN _fn, _ARGS... _args )
	{
		std::function<_R()> rfn = std::bind( _fn, _args... );
		std::shared_ptr<AData<_R>> pData( new AData<_R>() );
		fn_type fn = [=]()
		{
			pData->data = rfn();
			pData->ready = true;
		};
		getFreeWorker()->appendFn( fn );
		return pData;
	}



};

double foo()
{
	return 14.5;
}

int sum( int a, int b )
{
	return a + b;
}

int main()
{
	ThreadPool pool(10);

	std::function<std::string( int, int )> myFn = [&]( int a, int b )
	{
		std::string str = "String = " + std::to_string( a ) + " " + std::to_string( b );
		return str;
	};

	auto r1 = pool.runAsync<double>( &foo );
	auto r2 = pool.runAsync<int>( &sum, 100, 54 );
	auto r3 = pool.runAsync<bool>( [](){ Sleep( 3500 ); return true; } );
	auto r4 = pool.runAsync<std::string>( myFn, 50, 20 );

	while ( !r1->ready );  // Ждем результатов
	std::cout << r1->data << std::endl;
	while ( !r2->ready );
	std::cout << r2->data << std::endl;
	while ( !r3->ready );
	std::cout << r3->data << std::endl;
	while ( !r4->ready );
	std::cout << r4->data << std::endl;

	system( "pause" );
	return 0;
}