#include "Menu.hpp"
#include "GUI.hpp"
#include "SceneManager.hpp"
#include "Engine.hpp"

namespace SE
{
    Menu::Menu(const sf::String& menuTitle, const std::string& fontPath, const std::string& id, const sf::Vector2f& menuSize, const sf::Vector2f& pos,
               const sf::Color& menuColor, const sf::Color& titleBarColor, const sf::Color& titleColor) :
    Widget(id),
    m_xButtonState(XButtonState::NORMAL)
    {
        m_titlebarFont.loadFromFile(fontPath);

        m_titlebarText.setFont(m_titlebarFont);
        m_titlebarText.setString(menuTitle);
        m_titlebarText.setCharacterSize(10);
        m_titlebarText.setColor(titleColor);
        m_titlebarText.setPosition(pos);

        m_menu.setPosition(pos);
        m_titlebar.setPosition(pos);

        m_menu.setSize(menuSize);
        m_titlebar.setSize(sf::Vector2f(menuSize.x, 10));

        m_menu.setFillColor(menuColor);
        m_titlebar.setFillColor(titleBarColor);

        m_xButtonTexture.loadFromFile("Resources/xbuttonia.png");
        m_xButtonSprite.setTexture(m_xButtonTexture);
        m_xButtonSprite.setPosition(sf::Vector2f(pos.x + (menuSize.x - m_xButtonSprite.getTexture()->getSize().x), pos.y));

        setPosition(pos);
    }

    Menu::Ptr Menu::create(const sf::String& menuTitle, const std::string& fontPath, const std::string& id, const sf::Vector2f& menuSize, const sf::Vector2f& pos,
               const sf::Color& menuColor, const sf::Color& titleBarColor, const sf::Color& titleColor)
    {
        Ptr temp(new Menu(menuTitle, fontPath, id, menuSize, pos, menuColor, titleBarColor, titleColor));

        return temp;
    }

    bool Menu::attachWidget(const std::string& widgetId, const sf::Vector2f& posRelativeToMenu)
    {
        //Make sure a widget with same name isn't already in the vector
        for (const auto& iter : m_attachedWidgets)
        {
            if (iter.first == widgetId)
                return false;
        }

        //auto type = SceneManager::getCurrentScene().m_gui.getType(widgetId);

        //SceneManager::getCurrentScene().m_gui.getWidget<decltype(type)>(widgetId)->attachToMenu(getId());
        //SceneManager::getCurrentScene().m_gui.getWidget<decltype(type)>(widgetId)->setPosition(sf::Vector2f(m_menu.getPosition().x + posRelativeToMenu.x, m_menu.getPosition().y + posRelativeToMenu.y));

        m_attachedWidgets[widgetId] = posRelativeToMenu;

        return true;
    }

    bool Menu::detachWidget(const std::string& id)
    {
        for (auto iter = m_attachedWidgets.begin(); iter != m_attachedWidgets.end(); ++iter)
        {
            if (iter->first == id)
            {
                SceneManager::getCurrentScene().m_gui.removeWidget(id);
                m_attachedWidgets.erase(iter++);
            }

            return true;
        }

        return false;
    }

    void Menu::checkHold(sf::Mouse::Button button, bool press, int x, int y)
    {
        if (!getDraggable() || button != sf::Mouse::Middle)
            return;

        if (!press)
        {
            setHolding(false);

            return;
        }

        if (m_menu.getGlobalBounds().contains(static_cast<float>(x), static_cast<float>(y)))
        {
            if (!getHolding())
            {
                setHolding(true);

                setDragOffset(sf::Vector2f(static_cast<float>(x) - m_menu.getGlobalBounds().left, static_cast<float>(y) - m_menu.getGlobalBounds().top));
            }
        }

        else if (m_titlebar.getGlobalBounds().contains(static_cast<float>(x), static_cast<float>(y)))
        {
            if (!getHolding())
            {
                setHolding(true);

                setDragOffset(sf::Vector2f(static_cast<float>(x) - m_titlebar.getGlobalBounds().left, static_cast<float>(y) - m_titlebar.getGlobalBounds().top));
            }
        }
    }

    void Menu::update(sf::Time dt)
    {
        setBounds(m_menu.getGlobalBounds());
        m_menu.setPosition(getPosition());
        m_titlebar.setPosition(getPosition());
        m_titlebarText.setPosition(getPosition());
        m_xButtonSprite.setPosition(sf::Vector2f(getPosition().x + (m_menu.getSize().x - m_xButtonSprite.getTexture()->getSize().x), getPosition().y));

        sf::Vector2f mouseCoords = SceneManager::getGameMouseCoords();

        if (m_xButtonSprite.getGlobalBounds().contains(mouseCoords))
        {
            if (m_xButtonState == XButtonState::NORMAL)
                m_xButtonState = XButtonState::PRELIT;

            if (InputManager::isActive(User_Input::LEFTMOUSEPRESSED))
                m_xButtonState = XButtonState::ACTIVE;
        }

        else
            m_xButtonState = XButtonState::NORMAL;

        switch (m_xButtonState)
        {
        case XButtonState::NORMAL:
            m_xButtonTexture.loadFromFile("Resources/xbuttonia.png");
            break;

        case XButtonState::PRELIT:
            m_xButtonTexture.loadFromFile("Resources/xbuttona.png");
            break;

        case XButtonState::ACTIVE:
            m_xButtonTexture.loadFromFile("Resources/xbuttonia.png");

            SceneManager::getCurrentScene().m_gui.removeWidget(getId());

            break;
        }

        m_xButtonSprite.setTexture(m_xButtonTexture);

        for (const auto& iter : m_attachedWidgets)
            SceneManager::getCurrentScene().m_gui.findObjectWithId(iter.first)->setPosition(sf::Vector2f(getPosition().x + iter.second.x, getPosition().y + iter.second.y));
    }

    void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_menu, states);
        target.draw(m_titlebar, states);
        target.draw(m_xButtonSprite, states);
        target.draw(m_titlebarText);
    }
}
