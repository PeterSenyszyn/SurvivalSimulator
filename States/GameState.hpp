#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <State.hpp>

class GameState : public State
{
public:
    GameState(StateStack& stack, Context context);

    static void setDoneLoading(bool done) { m_doneLoading = done; }
    static bool getDoneLoading() { return m_doneLoading; }

    bool handleEvent(const sf::Event& event);
    bool update(sf::Time dt);
    virtual void draw();

private:
    static bool m_doneLoading;
};

#endif // GAMESTATE_H
