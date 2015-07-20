#pragma once

#include <functional>

#include "Widget.hpp"

namespace SE
{
	class ButtonLabel : public Widget
	{
	public:
		typedef std::shared_ptr<ButtonLabel> Ptr;

		static Ptr create(const sf::String& text = L"", const std::string& fontPath = "",
			const std::string& id = "", const sf::Color& iacolor = sf::Color::Transparent,
			const sf::Color& aColor = sf::Color::Transparent, const sf::Vector2f& pos = sf::Vector2f(0, 0));

		void handleDrag(int x, int y);

		sf::Text& getText() { return m_text; }

		//Connects a function (namely a lambda) to call whenever the button is pressed
		void bindOnButtonLabelPress(std::function<void()> method);

		const void setInactiveColor(const sf::Color& color) { m_iaColor = color; }
		const void setActiveColor(const sf::Color& color) { m_aColor = color; }

		void update(sf::Time dt);

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		ButtonLabel(const sf::String& text = L"", const std::string& fontPath = "",
			const std::string& id = "", const sf::Color& iacolor = sf::Color::Transparent,
			const sf::Color& aColor = sf::Color::Transparent, const sf::Vector2f& pos = sf::Vector2f(0, 0));

		void callBind();

		void handleMouseEnter(int x, int y);
		void handleMouseLeave(int x, int y);
		virtual void handleMouseButtonEvent(sf::Mouse::Button button, bool press, int x, int y) override;

		bool m_active;

		std::function<void()> m_buttonlabel_method;

		sf::Text m_text;
		sf::Font m_font;

		sf::Color m_iaColor, m_aColor;
	};
}
