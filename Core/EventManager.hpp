#pragma once

#include <queue>
#include <iostream>

#include "Event.hpp"
#include "EntityEvents.hpp"

namespace SE
{
	class EventManager
	{
	public:
		//Inserts event into the queue
		static void fireEvent(const EventInfo& evt) { m_event_queue.push(evt); }

		//For iterating in each scene's processEvents
		const bool queueEmpty() const { return m_event_queue.empty(); }

		//Returns the id of the front element
		//Just for ease of use
		const int getFrontId() const { return m_event_queue.front().getId(); }

		//Pops the front element
		//For ease of use
		const void popFront() const { m_event_queue.pop(); }

	private:
		static std::queue<EventInfo> m_event_queue;
	};
}