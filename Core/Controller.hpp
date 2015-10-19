#pragma once

#include <SFML/Graphics.hpp>

#include <list>
#include <algorithm>
#include <memory>

class Controller
{
public:
	virtual ~Controller() {};

	typedef std::shared_ptr<Controller> Ptr;

	const std::string& getID() const { return m_id; }

	virtual void update(sf::Time dt) {};

	void requireProperty(const std::string& id);

	void removeProperty(const std::string& id);

	std::list<std::string>& getRequiredProperties() { return m_requiredProperties; }

private:
	std::string m_id;

	std::list<std::string> m_requiredProperties;
};