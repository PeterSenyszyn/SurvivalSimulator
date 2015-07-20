#pragma once

#include "Event.hpp"

namespace SE
{
	struct EntityEvent : public EventInfo
	{
		EntityEvent(int evtType) : EventInfo(evtType) {};
	};
}