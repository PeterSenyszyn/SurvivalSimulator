#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>
#include <Thor/Input.hpp>

#include <Utility.hpp>
#include <WorldCell.hpp>
#include <Item.hpp>

class Player;

class RightClickAction
{
public:
    typedef std::shared_ptr<RightClickAction> Ptr;

    static Ptr create(const std::string& id, const std::string& name, std::function<void()> clickedAction)
    {
        Ptr temp = Ptr(new RightClickAction(clickedAction));
        temp->button = sfg::Button::Create(name);
        temp->button->SetId(id);
        temp->button->GetSignal(sfg::Widget::OnLeftClick).Connect(clickedAction);

        return temp;
    }

    bool active;
    sfg::Button::Ptr button;

private:
    RightClickAction(std::function<void()>& clickedAction) : active(false), clickedAction(clickedAction) {};

    std::function<void()> clickedAction;
};

//*********************************************************************************************************************************

class RightClickActionManager
{
public:
    void createRightClickAction(const std::string& id, const std::string& name, std::function<void()> clickedAction)
    {
        m_rightClickActions[id] = RightClickAction::create(id, name, clickedAction);
    }

    void setActiveRightClickAction(const std::string& id)
    {
        for (auto& iter : m_rightClickActions)
            iter.second->active = false;

        getRightClickActionContext(id)->active = true;
    }

    RightClickAction::Ptr getRightClickActionContext(const std::string& id)
    {
        for (auto& iter : m_rightClickActions)
        {
            if (iter.first == id)
                return iter.second;
        }

        return nullptr;
    }

private:
    std::map<std::string, RightClickAction::Ptr> m_rightClickActions;
};

//*********************************************************************************************************************************

class Inventory : public sf::Drawable
{
public:
    Inventory(Player& playerContext);

    struct Grid
    {
        Grid(int pos, Item::Item_Dictionary type, const std::string& name) : pos(pos), numItemsInStack(1), clickedOn(false), type(type), name(name)
        {
            itemLabel = sfg::Label::Create(name + "x1");
        };

        int pos;
        int numItemsInStack;

        bool clickedOn;

        sfg::Label::Ptr itemLabel;
        Item::Item_Dictionary type;

        std::vector<Item::Ptr> items;

        std::string name;
    };

    void init();

    void addItem(Item::Ptr item);

    void updateInput(thor::ActionMap<Keys::KeyboardInput>& keys);

    void handleEvents(const sf::Event& event);
    void update(sf::Time dt);

    sfg::Window::Ptr getWindow() { return m_window; }

    const bool getActive() const { return m_active; }
    const void setActive(const bool active) { m_active = active; m_window->Show(active); }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void setHealthPercentage(float percent) { m_healthBar->SetFraction(percent); }
    void setHungerPercentage(float percent) { m_hungerBar->SetFraction(percent); }
    void setThirstPercentage(float percent) { m_thirstBar->SetFraction(percent); }

private:
    void onItemClicked(Item::Item_Dictionary type, int index);
    void initRightClickActions();

    void actionDropItem(WorldCell::Ptr worldCell);
    void actionClose();

private:
    RightClickActionManager m_rightClickManager;

    sfg::Desktop m_desktop;
    std::shared_ptr<sf::Font> m_font;

    sfg::Table::Ptr m_table;
    sfg::Table::Ptr m_statusTable;

    sfg::Window::Ptr m_window;

    sfg::ScrolledWindow::Ptr m_inventoryScrollMenu;
    sfg::ScrolledWindow::Ptr m_statusScrollMenu;

    sfg::Notebook::Ptr m_notebook;

    sfg::Box::Ptr m_inventoryScrollBin;
    sfg::Box::Ptr m_statusScrollBin;

    sfg::Box::Ptr m_itemClickBox;
    sfg::Window::Ptr m_itemClickMenu;

    //Status bar stuff
    sfg::Label::Ptr m_healthLabel;
    sfg::ProgressBar::Ptr m_healthBar;

    sfg::Label::Ptr m_hungerLabel;
    sfg::ProgressBar::Ptr m_hungerBar;

    sfg::Label::Ptr m_thirstLabel;
    sfg::ProgressBar::Ptr m_thirstBar;

    sfg::Label::Ptr m_encumbranceLabel;
    sfg::ProgressBar::Ptr m_encumbranceBar;

    sfg::Label::Ptr m_staminaLabel;
    sfg::ProgressBar::Ptr m_staminaBar;

    bool m_active;
    bool m_needsUpdate;

    float m_weight;

    std::vector<std::shared_ptr<Grid> > m_grid;

    Player* playerContext;
};

#endif // INVENTORY_H
