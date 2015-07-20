#pragma once

#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

namespace SE
{
	class FPS
	{
	public:
		FPS(const std::string& fontPath, unsigned int charSize, const sf::Vector2f& pos);

		void update(sf::Time dt);

		static const void setEnabled(bool enabled) { m_enabled = enabled; }
		static const bool enabled() { return m_enabled; }

		void render(sf::RenderWindow& window)
		{
			if (m_enabled)
				window.draw(m_text);
		}

	private:
		sf::Font m_font;
		sf::Text m_text;

		//For finding fps
		sf::Clock m_clock;
		unsigned int m_lastTime;

		static bool m_enabled;
	};
}

