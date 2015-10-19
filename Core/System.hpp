#pragma once

#include "Entity.hpp"
#include "Controller.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

class System
{
public:
	void addEntity(Entity::Ptr entity);
	void addController(Controller::Ptr controller);

	void removeEntity(const std::string& id);
	void removeController(const std::string& id);

	void addControllerRequiredProperty(const std::string& controllerID, const std::string& requiredPropertyID);
	void removeControllerRequiredProperty(const std::string& controllerID, const std::string& requiredPropertyID);

	Entity::Ptr getEntity(const std::string& id);
	Controller::Ptr getController(const std::string& id);

	void update(sf::Time dt);
	void drawEntities(sf::RenderWindow& window) const;

private:
	std::list<Entity::Ptr> m_entities;
	std::list<Controller::Ptr> m_controllers;
};