#include <ctime>
#include <iomanip>
#include "Now.h"

NS_CORE_USING

const Now Now::START_TIME = Now("Start time");
const Now Now::FINISH_TIME = Now("End time");

Now::Now(const std::string &message)
: m_message(message)
{
}

void Now::writeToFile(std::ostream& file) const
{
	std::time_t t = std::time(0);
	char cstr[128];
	tm tm;
	localtime_s(&tm, &t);
	std::strftime(cstr, sizeof(cstr), "%c", &tm);

	file << m_message << ": " << cstr << std::endl;
}

bool Now::loadFromFile(std::istream& file)
{
	return true;
}