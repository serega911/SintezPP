#include "TraceLinkCommand.h"

NS_ARI_USING

ari::TraceLinkCommand::TraceLinkCommand( IScheme_p scheme, ITraceStrategy_p traceStrategy, const NS_CORE Link& link )
: m_scheme( scheme ), m_traceStrategy( traceStrategy ), m_link( link ), m_isApplied( false )
{
}

ari::TraceLinkCommand_p ari::TraceLinkCommand::create( IScheme_p scheme, ITraceStrategy_p traceStrategy, const NS_CORE Link& link )
{
	return TraceLinkCommand_p( new TraceLinkCommand( scheme, traceStrategy, link ) );
}

bool ari::TraceLinkCommand::execute()
{
	m_isApplied = false;

	m_traceStrategy->init( m_scheme->getWidth(), m_scheme->getHeight() );
	m_trace = m_traceStrategy->run( m_scheme->getAllElements(), m_link.getElem1(), m_link.getElem2() );

	return m_trace.size() > 0;
}

bool ari::TraceLinkCommand::apply()
{
	m_scheme->addLink( m_trace, m_link );
	m_isApplied = true;
	return true;
}

bool ari::TraceLinkCommand::isApplied()
{
	return m_isApplied;
}
