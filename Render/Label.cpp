
#include "Label.hpp"

namespace SE
{
	Label::Label(const sf::String& text, const std::string& fontPath, const std::string& id, const sf::Vector2f& pos) :
		Widget(id)
	{
		m_font.loadFromFile(fontPath);

		m_text.setFont(m_font);
		m_text.setString(text);
		setPosition(pos);
		m_text.setPosition(getPosition());
	}

	Label::Ptr Label::create(const sf::String& text, const std::string& fontPath, const std::string& id, const sf::Vector2f& pos)
	{
		Ptr temp(new Label(text, fontPath, id, pos));

		return temp;
	}

	void Label::init(unsigned int charSize, const sf::Color& textColor, const sf::Vector2f& pos)
	{
		m_text.setCharacterSize(charSize);
		m_text.setColor(textColor);
		m_text.setPosition(pos);
		setPosition(pos);
	}

	void Label::update(sf::Time dt)
	{
		setBounds(m_text.getGlobalBounds());

		m_text.setPosition(getPosition());
	}

	void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (getVisible())
			target.draw(m_text, states);
	}
}
