#pragma once

#include "Entity.hpp"

namespace SE
{
	class Player : public Entity
	{
	public:
		typedef std::shared_ptr<Player> Ptr;

		static Ptr create(const std::string& id = "player") { Ptr temp(new Player(id)); return temp; }

		void handleCollision();

		void move(const sf::Vector2f& offset);

		virtual void update(sf::Time dt);

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		Player(const std::string& id = "player", bool active = true);

        sf::Texture m_texture;
		sf::Sprite m_sprite;

		sf::Vector2f m_viewArea;

		bool nextPosValid(const sf::Vector2f& offset);
	};
}

