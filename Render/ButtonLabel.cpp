
#include "ButtonLabel.hpp"

namespace SE
{
	ButtonLabel::ButtonLabel(const sf::String& text, const std::string& fontPath, const std::string& id,
		const sf::Color& iaColor, const sf::Color& aColor, const sf::Vector2f& pos) :
		Widget(id),
		m_iaColor(iaColor),
		m_aColor(aColor),
		m_active(false)
	{
		m_font.loadFromFile(fontPath);

		m_text.setFont(m_font);
		m_text.setString(text);
		m_text.setColor(iaColor);

		setPosition(pos);
		m_text.setPosition(getPosition());
	}

	ButtonLabel::Ptr ButtonLabel::create(const sf::String& text, const std::string& fontPath,
		const std::string& id, const sf::Color& iaColor,
		const sf::Color& aColor, const sf::Vector2f& pos)
	{
		Ptr temp(new ButtonLabel(text, fontPath, id, iaColor, aColor, pos));

		return temp;
	}

	void ButtonLabel::bindOnButtonLabelPress(std::function<void()> method)
	{
		if (method == nullptr)
			return;

		m_buttonlabel_method = method;
	}

	void ButtonLabel::handleMouseEnter(int x, int y)
	{
        if (getState() == WidgetState::NORMAL)
            setState(WidgetState::PRELIGHT);
	}

	void ButtonLabel::handleMouseLeave(int x, int y)
	{
		if (getState() == WidgetState::PRELIGHT)
            setState(WidgetState::NORMAL);
	}

	void ButtonLabel::handleMouseButtonEvent(sf::Mouse::Button button, bool press, int x, int y)
	{
	    if (!getInWidget())
        {
            if (getState() == WidgetState::ACTIVE)
                setState(WidgetState::NORMAL);

                return;
        }

        if (button == sf::Mouse::Left)
        {
            if (press)
                setState(WidgetState::ACTIVE);

            else if (getState() == WidgetState::ACTIVE)
                setState(WidgetState::PRELIGHT);
        }
	}

	void ButtonLabel::update(sf::Time dt)
	{
	    if (getState() == WidgetState::NORMAL)
            m_text.setColor(m_iaColor);

        else if (getState() == WidgetState::PRELIGHT)
            m_text.setColor(m_aColor);

        else if (getState() == WidgetState::ACTIVE)
            m_buttonlabel_method();

		setBounds(m_text.getGlobalBounds());

		m_text.setPosition(getPosition());
	}

	void ButtonLabel::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (getVisible())
			target.draw(m_text, states);
	}
}
