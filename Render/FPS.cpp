#include "FPS.hpp"

namespace SE
{
	bool FPS::m_enabled = true;

	FPS::FPS(const std::string& fontPath, unsigned int charSize, const sf::Vector2f& pos)
	{
		m_font.loadFromFile(fontPath);

		m_text.setFont(m_font);
		m_text.setPosition(pos);
		m_text.setCharacterSize(charSize);
	}
	void FPS::update(sf::Time dt)
	{
	    std::stringstream ss;

		float currentTime = m_clock.restart().asSeconds();
		int fps = 1 / (currentTime - m_lastTime);
		m_lastTime = currentTime;

		currentTime = 0;

		ss << fps;

		m_text.setString(ss.str());

		if (fps >= 60)
			m_text.setColor(sf::Color::Green);

		else if (fps >= 30 && fps < 60)
			m_text.setColor(sf::Color::Yellow);

		else
			m_text.setColor(sf::Color::Red);
	}

}
