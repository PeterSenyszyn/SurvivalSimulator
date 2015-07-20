#pragma once

#include <map>
#include <memory>
#include <iostream>

#include <SFML/Graphics.hpp>

namespace SE
{
	class BackgroundManager	{
	private:
		struct Background;

	public:

		static std::shared_ptr<Background> createBackground(const std::string& filepath, const std::string& id);

		void pushBackground(std::shared_ptr<Background> background);

		void clearBackgrounds() { m_backgrounds.clear(); }

		void enableBackground(const std::string& id);
		void enableEverything();

		void disableEverything();

		void update(sf::Time dt);

		void render(sf::RenderWindow& window);

	private:
		struct Background : public sf::Drawable
		{
			Background(const std::string& filepath, const std::string& id) :
			m_id(id), m_visible(true) {
				m_texture.loadFromFile(filepath); m_sprite.setTexture(m_texture);
			}

			typedef std::shared_ptr<BackgroundManager::Background> Ptr;

			friend class BackgroundManager;

			sf::Texture m_texture;
			sf::Sprite m_sprite;

			std::string m_id;

			void draw(sf::RenderTarget& target, sf::RenderStates states) const
			{
				target.draw(m_sprite, states);
			}

			bool m_visible;
		};

		std::map<std::string, std::shared_ptr<Background> > m_backgrounds;
	};
}