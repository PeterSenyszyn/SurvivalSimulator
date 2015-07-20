#ifndef MENU_H
#define MENU_H

#include <map>

#include "Widget.hpp"

namespace SE
{
    class Menu : public Widget
    {
    public:
        typedef std::shared_ptr<Menu> Ptr;

        static Ptr create(const sf::String& menuTitle = L"", const std::string& fontPath = "", const std::string& id = "", const sf::Vector2f& menuSize = sf::Vector2f(0, 0),
             const sf::Vector2f& pos = sf::Vector2f(0, 0), const sf::Color& menuColor = sf::Color::Transparent, const sf::Color& titleBarColor = sf::Color::Transparent,
             const sf::Color& titleColor = sf::Color::Transparent);

        virtual void checkHold(sf::Mouse::Button, bool press, int x, int y);

        bool attachWidget(const std::string& id, const sf::Vector2f& posRelativeToMenu);
        bool detachWidget(const std::string& id);

        void update(sf::Time dt);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        enum class XButtonState
        {
            NORMAL,
            ACTIVE,
            PRELIT
        };

        Menu(const sf::String& menuTitle = L"", const std::string& fontPath = "", const std::string& id = "", const sf::Vector2f& menuSize = sf::Vector2f(0, 0),
             const sf::Vector2f& pos = sf::Vector2f(0, 0), const sf::Color& menuColor = sf::Color::Transparent, const sf::Color& titleBarColor = sf::Color::Transparent,
             const sf::Color& titleColor = sf::Color::Transparent);

        sf::RectangleShape m_menu, m_titlebar;

        sf::Texture m_xButtonTexture;
        sf::Sprite m_xButtonSprite;

        sf::Text m_titlebarText;
        sf::Font m_titlebarFont;

        XButtonState m_xButtonState;

        std::map<std::string, sf::Vector2f> m_attachedWidgets;
    };
}

#endif // MENU_H
