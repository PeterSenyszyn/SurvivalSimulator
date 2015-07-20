
#include "EditBox.hpp"
#include "SceneManager.hpp"

namespace SE
{
	EditBox::EditBox(const std::string& id, const std::string& fontPath,
		const std::string& cursorFilePath, const sf::Vector2f& pos) :
		Widget(id),
		m_edit(false)
	{
		m_cursor_texture.loadFromFile(cursorFilePath);
		m_cursor_sprite.setTexture(m_cursor_texture);

		m_font.loadFromFile(fontPath);

		setPosition(pos);

		m_text_drawn.setFont(m_font);
		m_text_drawn.setCharacterSize(16);
		m_text_drawn.setPosition(pos);
		m_text_drawn.setColor(sf::Color::White);
	}

	EditBox::Ptr EditBox::create(const std::string& id, const std::string& fontPath,
		const std::string& cursorFilePath, const sf::Vector2f& pos)
	{
		Ptr temp(new EditBox(id, fontPath, cursorFilePath, pos));

		return temp;
	}

	void EditBox::handleTextEvent(sf::Uint32 character)
	{
		if (!getInWidget() || !getVisible() || getState() != WidgetState::ACTIVE)
			return;

		if (character == 8)
		{
			if (!m_user_text.isEmpty())
				m_user_text.erase(m_user_text.getSize() - 1);

			return;
		}

		if (character < 127 && character != 8)
		{
			if (hasRoom())
				m_user_text += character;
		}
	}

	void EditBox::handleMouseClick(sf::Mouse::Button button, int x, int y)
	{
		if (button == sf::Mouse::Left)
			setState(WidgetState::ACTIVE);

		else
			setState(WidgetState::NORMAL);
	}

	void EditBox::update(sf::Time dt)
	{
		if (getInWidget() && getVisible())
		{
			SceneManager::getWindow().setMouseCursorVisible(false);
			m_cursor_sprite.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(SceneManager::getWindow())));
		}

		else
			SceneManager::getWindow().setMouseCursorVisible(true);

		if (!m_user_text.isEmpty())
			m_text_drawn.setString(m_user_text);

		else
			m_text_drawn.setString(m_prompt_text);

		setBounds(m_box.getGlobalBounds());
		setPosition(getPosition());
		centerText();
	}

	void EditBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (getVisible())
		{
			target.draw(m_box, states);

			if (getInWidget())
				target.draw(m_cursor_sprite, states);

			target.draw(m_text_drawn);
		}
	}

	void EditBox::centerText()
	{
		m_box.setOrigin(m_box.getGlobalBounds().width / 2, m_box.getGlobalBounds().height / 2);

		m_text_drawn.setPosition(getPosition());
		m_text_drawn.setOrigin(m_text_drawn.getGlobalBounds().width / 2, m_text_drawn.getGlobalBounds().height / 2);
	}

	bool EditBox::hasRoom()
	{
		std::size_t charSize = m_text_drawn.getCharacterSize();

		if (charSize * m_text_drawn.getString().getSize() > m_box.getGlobalBounds().width)
			return false;

		return true;
	}
}
