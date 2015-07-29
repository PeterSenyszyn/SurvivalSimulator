#ifndef EXAMINEMENU_H
#define EXAMINEMENU_H

#include <Item.hpp>
#include <World.hpp>

class Player;

struct Action
{
    typedef std::shared_ptr<Action> Ptr;

    Action(float actionTime, const std::string& actionName, std::function<void()> finishedMethod) :
    actionTime(actionTime), actionName(actionName), active(false), finishedMethod(finishedMethod) {};

    static Ptr create(float actionTime, const std::string& id, const std::string& actionName, std::function<void()>& finishedMethod)
    {
        Ptr temp = Ptr(new Action(actionTime, actionName, finishedMethod));

        temp->button = sfg::Button::Create(actionName);
        temp->button->SetId(id);

        return temp;
    }

    void update(sfg::ProgressBar::Ptr progressBar, Player* player);

    sfg::Button::Ptr button;
    sf::Clock actionClock;
    float actionTime;

    bool active;
    std::string actionName;

    std::function<void()> finishedMethod;
};

class ActionManager
{
public:
    void createAction(float actionTime, const std::string& id, const std::string& actionName, std::function<void()> finishedMethod)
    {
        actions[id] = Action::create(actionTime, id, actionName, finishedMethod);
    }

    void resetAllGui()
    {
        for (const auto& iter : actions)
        {
            if (iter.second->button != nullptr)
                iter.second->button = sfg::Button::Create(iter.second->actionName);

            else
                iter.second->button = sfg::Button::Create("Null");
        }
    }

    void setActiveAction(const std::string& id)
    {
        for (auto& iter : actions)
            iter.second->active = false;

        getActionContext(id)->active = true;
    }

    Action::Ptr getActionContext(const std::string& id)
    {
        for (auto& iter : actions)
        {
            if (iter.first == id)
                return iter.second;
        }

        return nullptr;
    }

    void update(sfg::ProgressBar::Ptr progressBar, Player* player)
    {
        for (auto& iter : actions)
        {
            if (iter.second->active)
                iter.second->update(progressBar, player);
        }
    }

private:
    std::map<std::string, Action::Ptr> actions;
};

class ExamineMenu
{
public:
    ExamineMenu(Player* player);

    void init(TileMap::TileEntityRef::Ptr entityRef, Player* player); //Every time the player examines something new, the menu needs to be reinitialized
    void init(Item::Ptr itemRef, Player* player, World& world);

    void handleEvents(const sf::Event& event);
    void update(sf::Time dt, Player* player);

    sfg::Window::Ptr getWindow() { return m_window; }
    ActionManager& getActionManager() { return m_actionManager; }

    const bool getActive() const { return m_active; }

    void setActive(bool active)
    {
        m_active = active;
        m_window->Show(m_active);
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    void initActions(Player* player);

    void reset();

    sfg::Desktop m_desktop;
    std::shared_ptr<sf::Font> m_font;

    sfg::Window::Ptr m_window;

    sfg::Box::Ptr m_buttonBox;

    bool m_active;

    ActionManager m_actionManager;

    sfg::ProgressBar::Ptr m_actionProgressBar;
};

#endif // EXAMINEMENU_H
