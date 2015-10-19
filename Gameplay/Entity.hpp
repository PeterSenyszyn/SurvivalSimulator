#pragma once

#include <map>
#include <list>
#include <cassert>
#include <memory>
#include <stdexcept>

#include <SFML/Graphics.hpp>

#include <Thor/Animations.hpp>

#include "Controller.hpp"

class Entity : public sf::Drawable
{
public:
	typedef std::shared_ptr<Entity> Ptr;

	virtual ~Entity() {};

	void registerProperty(const std::string& id, void* data);

	void setProperty(const std::string& id, void* data);

	template <class T>
	T& getProperty(const std::string& id)
	{
		try
		{
			for (const auto& iter : m_properties)
			{
				if (iter.first == id)
					return *static_cast<T*>(iter.second);
			}
		}

		catch (std::exception& e) { throw std::runtime_error(e.what()); }

		T temp;

		assert(temp);

		return temp;
	}

	bool hasProperty(const std::string& id);

	void addAssociatedController(Controller::Ptr);
	bool isAssociatedWithController(const std::string& controllerID);
	std::list<Controller::Ptr>& getAssociatedControllers() { return m_associatedControllers; }

	const std::string& getID() const { return m_id; }

	virtual void addFrames(thor::FrameAnimation& animation, int x, int yFirst, int yLast, float duration, int xSize, int ySize);

	virtual void update(sf::Time dt);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {};

protected:
	explicit Entity(std::string entityID);

	//virtual bool nextPosValid(const sf::Vector2f& offset) {};

private:
	std::map<std::string, void*> m_properties;
	std::list<Controller::Ptr> m_associatedControllers;

	std::string m_id;
};