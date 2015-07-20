#pragma once

#include "Widget.hpp"

namespace SE
{
	class EditBox final : public Widget
	{
	public:
		typedef std::shared_ptr<EditBox> Ptr;

		static Ptr create(const std::string& id = "", const std::string& fontPath = "",
			const std::string& cursorFilePath = "",
			const sf::Vector2f& pos = sf::Vector2f(0, 0));

		//Getters
		sf::RectangleShape& getRect() { return m_box; }
		const sf::String& getText() const { return m_user_text; }
		sf::Text& getTextDrawn() { return m_text_drawn; }

		const void setPosition(const sf::Vector2f& pos) { m_position = pos; m_box.setPosition(pos); }

		void handleTextEvent(sf::Uint32 character);
		void handleMouseClick(sf::Mouse::Button button, int x, int y);

		void update(sf::Time dt);

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		EditBox(const std::string& id = "", const std::string& fontPath = "",
			const std::string& cursorFilePath = "",
			const sf::Vector2f& pos = sf::Vector2f(0, 0));

		void centerText();

		//If the edit box has room to add more characters
		//without falling off the edge
		bool hasRoom();

		sf::RectangleShape m_box;

		sf::Texture m_cursor_texture;
		sf::Sprite m_cursor_sprite;

		//If the editbox is currently being edited
		bool m_edit;

		sf::String m_user_text;
		sf::String m_prompt_text;

		sf::Font m_font;
		sf::Text m_text_drawn;
	};
}
