#pragma once

#include <list>

#include "Entity.hpp"

class EntityGroup
{
public:
	typedef std::unique_ptr<EntityGroup> Ptr;

	static Ptr create(std::string& groupID)
	{
		return std::move(Ptr(new EntityGroup(groupID)));
	}

	void addEntity(Entity::Ptr entity)
	{
		//See if there's another entity of the same ID
		auto found = std::find_if(m_entities.begin(), m_entities.end(), [&](Entity::Ptr& iter) { return iter->getID() == entity->getID(); });

		if (found != m_entities.end())
			throw std::runtime_error("Entity named " + entity->getID() + " could not be made, entity of the same ID already exists!");

		m_entities.push_back(std::move(entity));
	}

	void removeEntity(std::string& entityID)
	{
		m_entities.remove_if([&](Entity::Ptr& iter) { return iter->getID() == entityID; });

		assert(!entityInGroup(entityID));
	}

	bool entityInGroup(std::string& entityID)
	{
		auto found = std::find_if(m_entities.begin(), m_entities.end(), [&](Entity::Ptr& iter) { return iter->getID() == entityID; });

		if (found != m_entities.end())
			return true;

		else
			return false;
	}

	void addAssociatedController(Controller::Ptr controller)
	{
		for (const auto& iter : m_entities)
			iter->addAssociatedController(controller);
	}

private:
	explicit EntityGroup(std::string& groupID) :
		m_groupID(groupID) {};

private:
	std::string m_groupID;

	std::list<Entity::Ptr> m_entities;
	std::list<Controller::Ptr> m_associatedControllers;
};
