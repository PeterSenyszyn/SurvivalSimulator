#pragma once

#include <memory>
#include <list>
#include <unordered_map>
#include <exception>

#include <SFML/Graphics.hpp>

#include "EventManager.hpp"
#include "InputManager.hpp"

namespace SE
{
	/*
	Each entity can only be created through the factory function
	SEntity is meant for inheritance purposes
	*/

	class Entity : public sf::Drawable
	{
	public:
		typedef std::shared_ptr<Entity> Ptr;

		virtual ~Entity() {};

		const std::string& getId() const { return m_id; }

		const sf::Vector2f& getPosition() const { return m_position; }
		const sf::FloatRect& getBounds() const { return m_bounds; }

		const bool getEnabled() const { return m_enabled; }

		virtual void setPosition(const sf::Vector2f& pos) { m_position = pos; }
		virtual void setBounds(const sf::FloatRect& rect) { m_bounds = rect; }

		void registerAttribute(const std::string& id, void* data)
		{
			m_attributes[id] = data;
		}

		void setAttribute(const std::string& id, void* data)
		{
			for (auto& iter : m_attributes)
			{
				if (iter.first == id)
				{
					iter.second = data;
					return;
				}
			}

			registerAttribute(id, data);
		}

		template <class T>
		T& getAttribute(const std::string& id)
		{
			try
			{
				for (const auto& iter : m_attributes)
				{
					if (iter.first == id)
						return *static_cast<T*>(iter.second);
				}
			}

			catch (std::exception& e) { std::cout << "Error getting attribute: " << e.what() << std::endl; }

			static T temp;

			return temp;
		}

		bool hasAttribute(const std::string& id)
		{
			for (const auto& iter : m_attributes)
			{
				if (iter.first == id)
					return true;
			}

			return false;
		}

		virtual void update(sf::Time dt) = 0;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

	protected:
		Entity();

	private:
		std::string m_id;

		bool m_enabled;

		sf::Vector2f m_position;
		sf::FloatRect m_bounds;

		std::unordered_map<std::string, void*> m_attributes;
	};
}

