#include <StateStack.hpp>
#include <GuiManager.hpp>

#include <cassert>

StateStack::StateStack(State::Context context) :
m_context(context),
m_currentStateId(States::None)
{

}

void StateStack::update(sf::Time dt)
{
    for (auto iter = m_stack.rbegin(); iter != m_stack.rend(); ++iter)
    {
        if ((*iter)->getStateId() == m_currentStateId)
            (*iter)->update(dt);
    }

    applyPendingChanges();
}

void StateStack::handleEvent(const sf::Event& event)
{
    //Iterate from top to bottom, stop as sooon as handleEvent() returns false
    for (auto iter = m_stack.rbegin(); iter != m_stack.rend(); ++iter)
    {
        if ((*iter)->getStateId() == m_currentStateId)
            (*iter)->handleEvent(event);
    }

    applyPendingChanges();
}

void StateStack::draw()
{
    for (const auto& iter : m_stack)
    {
        if (iter->getStateId() == m_currentStateId)
            iter->draw();
    }
}

void StateStack::pushState(States::ID stateID)
{
    if (m_currentStateId != States::None)
    {
        m_context.guiManager->setStateWindowsShow(m_currentStateId, false);
        m_context.guiManager->setStateWindowsShow(stateID, true);
    }

    m_currentStateId = stateID;

    m_pendingList.push_back(PendingChange(Push, stateID));
}

void StateStack::changeState(States::ID stateID)
{
    if (m_currentStateId != States::None)
    {
        m_context.guiManager->setStateWindowsShow(m_currentStateId, false);
        m_context.guiManager->setStateWindowsShow(stateID, true);
    }

    m_currentStateId = stateID;

    m_pendingList.push_back(PendingChange(Change, stateID));
}

void StateStack::popState()
{
    m_pendingList.push_back(PendingChange(Pop));
}

void StateStack::clearStates()
{
    m_pendingList.push_back(PendingChange(Clear));

    m_currentStateId = States::None;
}

bool StateStack::isEmpty() const
{
    return m_stack.empty();
}

State::Ptr StateStack::createState(States::ID stateID)
{
    auto found = m_factories.find(stateID);

    assert(found != m_factories.end());

    return found->second();
}

void StateStack::applyPendingChanges()
{
    for (const auto& iter : m_pendingList)
    {
        bool found = false;

        switch (iter.action)
        {
        case Push:
            m_stack.push_back(createState(iter.stateID));
            break;

        case Change:
            for (auto iter2 = 0; iter2 <= m_stack.size() - 1; ++iter2)
            {
                if (m_stack[iter2]->getStateId() == iter.stateID)
                {
                    auto it = m_stack.begin() + iter2;

                    std::rotate(it, it + 1, m_stack.end());

                    found = true;
                }
            }

            if (!found)
                m_stack.push_back(createState(iter.stateID));

            break;

        case Pop:
            m_stack.pop_back();
            break;

        case Clear:
            m_stack.clear();
            break;
        }
    }

    m_pendingList.clear();
}

StateStack::PendingChange::PendingChange(Action action, States::ID stateID) :
action(action),
stateID(stateID)
{

}
