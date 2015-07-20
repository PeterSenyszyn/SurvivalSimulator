#pragma once

namespace SE
{
	enum
	{
		EVENT_ENTITY_CREATED,
		EVENT_ENTITY_DESTROYED,
	};

	class EventInfo
	{
	public:
		EventInfo(int id) : m_id(id) {};

		const int getId() const { return m_id; }

	private:
		int m_id;
	};
}