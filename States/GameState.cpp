#include <GameState.hpp>
#include <ResourceHolder.hpp>
#include <Application.hpp>

bool GameState::m_doneLoading = false;

GameState::GameState(StateStack& stack, Context context) :
State(stack, context)
{
    setStateId(States::Game);

    context.player->setActive(true);
    context.world->setActive(true);

    initGui();
}

void GameState::initGui()
{

}

bool GameState::handleEvent(const sf::Event& event)
{
    getContext().player->handleEvents(event);

    if (getContext().keyboardMap->isActive(Keys::ESCAPEPRESS))
    {
        getContext().player->setActive(false);
        getContext().world->setActive(false);

        m_doneLoading = false;

        requestStackPush(States::Intro);
    }

    return true;
}

bool GameState::update(sf::Time dt)
{
    getContext().world->update(dt);
    getContext().player->update(dt, *getContext().keyboardMap, *getContext().world);

    return true;
}

void GameState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.draw(*getContext().world);
    window.draw(*getContext().player);
}
