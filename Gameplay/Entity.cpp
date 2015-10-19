#include "stdafx.h"
#include "Entity.hpp"

Entity::Entity(std::string entityID) :
	m_id(entityID)
{

}

void Entity::registerProperty(const std::string& id, void* data)
{
	m_properties[id] = data;
}

void Entity::setProperty(const std::string& id, void* data)
{
	for (auto& iter : m_properties)
	{
		if (iter.first == id)
		{
			iter.second = data;
			return;
		}
	}

	registerProperty(id, data);
}

bool Entity::hasProperty(const std::string& id)
{
	for (const auto& iter : m_properties)
	{
		if (iter.first == id)
			return true;
	}

	return false;
}

void Entity::addAssociatedController(Controller::Ptr controller)
{
	for (const auto& iter : m_associatedControllers)
	{
		for (const auto& iter2 : iter->getRequiredProperties())
		{
			if (!hasProperty(iter2))
				throw std::runtime_error("Can't associate controller: " + controller->getID() + " with entity: " + m_id + ", the entity doesn't have the required properties!");
		}
	}

	if (!isAssociatedWithController(controller->getID()))
		m_associatedControllers.push_back(controller);

	else
		throw std::runtime_error("Can't associate controller: " + controller->getID() + " with entity: " + m_id + ", the controller has already been associated with this entity!");
}

bool Entity::isAssociatedWithController(const std::string& controllerID)
{
	if (std::find_if(m_associatedControllers.begin(), m_associatedControllers.end(), [&](const Controller::Ptr& iter) { return controllerID == iter->getID(); }) != m_associatedControllers.end())
		return true;

	return false;
}

void Entity::addFrames(thor::FrameAnimation& animation, int x, int yFirst, int yLast, float duration, int xSize, int ySize)
{
	const int step = (yFirst < yLast) ? +1 : -1;
	yLast += step; // so yLast is excluded in the range

	for (int y = yFirst; y != yLast; y += step)
		animation.addFrame(duration, sf::IntRect(xSize * x, ySize * y, xSize, ySize));
}

void Entity::update(sf::Time dt)
{
	for (const auto& iter : m_associatedControllers)
		iter->update(dt);
}