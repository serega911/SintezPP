#include "TraceFrictionCommand.h"

NS_ARI_USING

ari::TraceFrictionCommand::TraceFrictionCommand( IScheme_p scheme, ITraceStrategy_p traceStrategy, const NS_CORE Link& link )
: m_scheme( scheme ), m_traceStrategy( traceStrategy ), m_link( link ), m_isApplied( false )
{
}

ari::TraceFrictionCommand_p ari::TraceFrictionCommand::create( IScheme_p scheme, ITraceStrategy_p traceStrategy, const NS_CORE Link& link )
{
	return TraceFrictionCommand_p( new TraceFrictionCommand( scheme, traceStrategy, link ) );
}

bool ari::TraceFrictionCommand::execute()
{
	m_isApplied = false;

	m_traceStrategy->init( m_scheme->getWidth(), m_scheme->getHeight() );
	m_trace = m_traceStrategy->run( m_scheme->getAllElements(), m_link.getElem1(), m_link.getElem2() );

	return m_trace.size() > 0;
}

bool ari::TraceFrictionCommand::apply()
{
	m_scheme->addFriction( m_trace, m_link );
	m_isApplied = true;
	return true;
}

bool ari::TraceFrictionCommand::isApplied()
{
	return m_isApplied;
}
