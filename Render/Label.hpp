#pragma once

#include "Widget.hpp"

namespace SE
{
	class Label final : public Widget
	{
	public:
		typedef std::shared_ptr<Label> Ptr;

		static Ptr create(const sf::String& text = L"", const std::string& fontPath = "",
			const std::string& id = "", const sf::Vector2f& pos = sf::Vector2f(0, 0));

		void init(unsigned int charSize = 16, const sf::Color& textColor = sf::Color::White,
			const sf::Vector2f& pos = sf::Vector2f(0, 0));

		void handleDrag(int x, int y);

		sf::Text& getText() { return m_text; }

		void update(sf::Time dt);

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		Label(const sf::String& text = "", const std::string& fontPath = "", const std::string& id = "", const sf::Vector2f& pos = sf::Vector2f(0, 0));

		//The text of the label
		sf::Text m_text;

		sf::Font m_font;
	};
}
