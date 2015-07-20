#ifndef INTROSTATE_H
#define INTROSTATE_H

#include <State.hpp>
#include <Application.hpp>
#include <functional>

class IntroState : public State
{
public:
    IntroState(StateStack& stack, Context context);

    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);
    virtual void draw();

private:
    sfg::Button::Ptr playButton, settingsButton, creditsButton, exitButton, newGameButton, loadGameButton;
    sfg::Label::Ptr title;

    void playButtonClicked();
    void settingsButtonClicked();
};

#endif // INTROSTATE_H
