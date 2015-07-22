#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <iostream>
#include <map>
#include <memory>

#include <SFML/Graphics.hpp>

#include <SFGUI/Widgets.hpp>
#include <SFGUI/SFGUI.hpp>

#include <StateIdentifiers.hpp>
#include <ResourceIdentifiers.hpp>

class GuiManager
{
public:
    GuiManager();

    void update(sf::Time dt);
    void handleEvents(const sf::Event& event);
    void draw(sf::RenderWindow& window);

    static std::shared_ptr<sfg::Window> createWindow(States::ID stateID, const std::string& id, std::uint8_t style);
    static std::shared_ptr<sfg::Window> getWindow(States::ID stateID, const std::string& id);

    static void resetWindows();

    template <class T>
    void setDesktopProperty(std::string selector, std::string property, const T& value) { m_desktop.SetProperty(selector, property, value); }

    void setStateWindowsShow(States::ID stateID, bool show);
    void hideAllWindows();

    struct StateGuiContext
    {
        typedef std::shared_ptr<StateGuiContext> Ptr;

        std::map<std::string, std::shared_ptr<sfg::Window> > windows;
    };

private:
    void createGuiContext(States::ID stateID);

private:
    sfg::SFGUI m_sfgui;
    static sfg::Desktop m_desktop;

    std::shared_ptr<sf::Font> m_globalFont;

    std::string m_globalFontPath;

private:
    static std::map<States::ID, StateGuiContext::Ptr> m_stateGuiContexts;
};

#endif // GUIMANAGER_H
