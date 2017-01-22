#pragma once

#include "../Libraries/GlobalDefines.h"

#include "ICommand.h"
#include "ITraceStrategy.h"
#include "IScheme.h"
#include "../Libraries/Link.h"

NS_ARI_START

class TraceFrictionCommand;

typedef std::shared_ptr<TraceFrictionCommand> TraceFrictionCommand_p;

class TraceFrictionCommand : public ICommand
{
private:

	TraceFrictionCommand( IScheme_p scheme, ITraceStrategy_p traceStrategy, const NS_CORE Link& link );

	std::vector<Cordinate>						m_trace;
	NS_CORE Link								m_link;
	ITraceStrategy_p							m_traceStrategy;
	IScheme_p									m_scheme;

	bool										m_isApplied;

public:

	static TraceFrictionCommand_p create( IScheme_p scheme, ITraceStrategy_p traceStrategy, const NS_CORE Link& link );

	virtual bool								execute() override;
	virtual bool								apply() override;
	virtual bool								isApplied() override;

};



NS_ARI_END