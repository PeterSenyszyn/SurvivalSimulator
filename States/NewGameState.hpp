#ifndef NEWGAMESTATE_H
#define NEWGAMESTATE_H

#include <State.hpp>

class NewGameState : public State
{
public:
    NewGameState(StateStack& stack, Context context);

    virtual void initGui();

    bool handleEvent(const sf::Event& event);
    bool update(sf::Time dt);
    virtual void draw();

private:
    sfg::Label::Ptr nameLabel;
    sfg::Entry::Ptr nameEntry;

    sfg::ComboBox::Ptr genderBox;

    sfg::Label::Ptr difficultyLabel;
    sfg::ComboBox::Ptr difficultyBox;

    sfg::Button::Ptr goButton;
};

#endif // NEWGAMESTATE_H
