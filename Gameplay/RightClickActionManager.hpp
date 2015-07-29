#ifndef RIGHTCLICKACTIONMANAGER_H
#define RIGHTCLICKACTIONMANAGER_H

#include <memory>
#include <map>

#include <SFGUI/Widgets.hpp>

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

#endif // RIGHTCLICKACTIONMANAGER_H
