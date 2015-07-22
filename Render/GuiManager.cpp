#include <GuiManager.hpp>
#include <ResourceHolder.hpp>

std::map<States::ID, GuiManager::StateGuiContext::Ptr> GuiManager::m_stateGuiContexts;
sfg::Desktop GuiManager::m_desktop;

GuiManager::GuiManager()
{
    m_globalFont = std::make_shared<sf::Font>();
    m_globalFont->loadFromFile("Assets/font.ttf");

    m_desktop.GetEngine().GetResourceManager().SetDefaultFont(m_globalFont);
    m_desktop.SetProperty("*", "FontName", "Assets/font.ttf");

    createGuiContext(States::Intro);
    createGuiContext(States::NewGame);
    createGuiContext(States::Settings);
    createGuiContext(States::Game);
    createGuiContext(States::Loading);
}

void GuiManager::update(sf::Time dt)
{
    m_desktop.Update(dt.asSeconds());
}

void GuiManager::handleEvents(const sf::Event& event)
{
    m_desktop.HandleEvent(event);
}

void GuiManager::draw(sf::RenderWindow& window)
{
    m_sfgui.Display(window);
}

void GuiManager::createGuiContext(States::ID stateID)
{
    m_stateGuiContexts[stateID] = std::make_shared<StateGuiContext>();
}

std::shared_ptr<sfg::Window> GuiManager::createWindow(States::ID stateID, const std::string& id, std::uint8_t style)
{
    //Check to make sure the window doesn't already exist
    for (const auto& iter : m_stateGuiContexts[stateID]->windows)
    {
        if (iter.first == id)
            return nullptr;
    }

    auto window = sfg::Window::Create(style);

    window->SetId(id);

    m_desktop.Add(window);

    auto context = m_stateGuiContexts[stateID];

    context->windows[id] = window;

    return window;
}

std::shared_ptr<sfg::Window> GuiManager::getWindow(States::ID stateID, const std::string& id)
{
    auto context = m_stateGuiContexts[stateID];

    return context->windows[id];
}

void GuiManager::resetWindows()
{
    for (auto iter = m_stateGuiContexts.begin(); iter != m_stateGuiContexts.end(); ++iter)
    {
        for (auto iter2 = (*iter).second->windows.begin(); iter2 != (*iter).second->windows.end(); ++iter2)
            (*iter).second->windows.erase(iter2);
    }

    m_desktop.RemoveAll();
}

void GuiManager::setStateWindowsShow(States::ID stateID, bool show)
{
    auto context = m_stateGuiContexts[stateID];

    for (const auto& iter : context->windows)
        iter.second->Show(show);
}

void GuiManager::hideAllWindows()
{
    for (const auto& iter : m_stateGuiContexts)
    {
        for (const auto& iter2 : iter.second->windows)
            iter2.second->Show(false);
    }
}
