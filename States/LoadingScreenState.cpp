#include <LoadingScreenState.hpp>

LoadingScreenState::LoadingScreenState(StateStack& stack, Context context) :
State(stack, context),
m_elapsedTime(0.0)
{
    setStateId(States::Loading);

    //Define the map
    const int level[] =
    {
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 9, 9, 9, 3, 0, 0, 0, 0, 8, 5, 5, 5, 13, 5, 5, 5, 5, 5, 5, 5, 5, 13,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 9, 9, 9, 3, 0, 0, 0, 0, 8, 5, 5, 5, 13, 5, 5, 5, 5, 5, 5, 5, 5, 13,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 9, 9, 9, 3, 0, 0, 0, 0, 8, 5, 5, 5, 13, 5, 5, 5, 5, 5, 5, 5, 5, 13,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 9, 9, 9, 3, 0, 0, 0, 0, 8, 5, 5, 5, 13, 5, 5, 5, 5, 5, 5, 5, 5, 13,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 9, 9, 9, 3, 0, 0, 0, 0, 8, 5, 5, 5, 13, 5, 5, 5, 5, 5, 5, 5, 5, 13,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 9, 9, 9, 3, 0, 0, 0, 0, 8, 5, 5, 5, 13, 5, 5, 5, 5, 5, 5, 5, 5, 13,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 9, 9, 9, 3, 0, 0, 0, 0, 8, 5, 5, 5, 13, 5, 5, 5, 5, 5, 5, 5, 5, 13,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 9, 9, 9, 3, 0, 0, 0, 0, 8, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 13,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 9, 9, 9, 3, 0, 0, 0, 0, 8, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 13,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 9, 9, 9, 3, 0, 0, 0, 0, 8, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 13,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 9, 9, 9, 3, 0, 0, 0, 0, 8, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 13,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 9, 9, 9, 3, 0, 0, 0, 0, 8, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 13,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 9, 9, 9, 3, 0, 0, 0, 0, 8, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 13,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 9, 9, 9, 3, 0, 0, 0, 0, 8, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 13,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 9, 9, 9, 3, 0, 0, 0, 0, 8, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 13,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 9, 9, 9, 3, 0, 0, 0, 0, 8, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 13,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 9, 9, 9, 3, 0, 0, 0, 0, 8, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 13,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 9, 9, 9, 3, 0, 0, 0, 0, 8, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 13,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 9, 9, 9, 3, 0, 0, 0, 0, 8, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 13,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 9, 9, 9, 3, 0, 0, 0, 0, 8, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 13,
    };

    auto mainCell = WorldCell::create("maincell", true);

    mainCell->getTileMap().load("Assets/topdown_tiles/tilesheet.png", sf::Vector2u(64, 64), level, 32, 20);
    context.world->pushWorldCell(mainCell);
    context.world->setCurrentCell("maincell");

    context.player->init();

    m_loadingFont.loadFromFile("Assets/font.ttf");
    m_loadingText.setFont(m_loadingFont);
    m_loadingText.setCharacterSize(50);
    m_loadingText.setColor(sf::Color::White);
    m_loadingText.setPosition(-320, (1080 / 2) - 50);
    m_loadingText.setString("Building World");

    GameState::setDoneLoading(true);
}

bool LoadingScreenState::update(sf::Time dt)
{
    m_elapsedTime += dt.asSeconds();

    if (m_elapsedTime < 4.0)
    {
        m_loadingText.move(90 * dt.asSeconds(), 0);
    }

    else if (m_elapsedTime >= 4.0 && m_elapsedTime < 8.0)
    {
        m_loadingText.setString("Loading Player");

        m_loadingText.move(90 * dt.asSeconds(), 0);
    }

    else if (m_elapsedTime >= 8.0 && m_elapsedTime < 12.0)
    {
        m_loadingText.setString("Initializing GUI");

        m_loadingText.move(90 * dt.asSeconds(), 0);
    }

    else if (m_elapsedTime >= 12.0 && m_elapsedTime < 18.5)
    {
        m_loadingText.setString("Done, good luck!");

        if (m_elapsedTime >= 13.0 && m_elapsedTime < 14.0)
            m_loadingText.move(-(90 * dt.asSeconds()), 0);

        else if (m_elapsedTime >= 14.0 && m_elapsedTime < 15.0)
            m_loadingText.move(250 * dt.asSeconds(), 0);

        else if (m_elapsedTime >= 15.0 && m_elapsedTime < 16.0)
            m_loadingText.move(1200 * dt.asSeconds(), 0);
    }

    //Over 5 secs? Go ahead and load the game state
    else if (m_elapsedTime >= 18.5f && GameState::getDoneLoading())
    {
        getContext().player->setActive(true);

        requestStackChange(States::Game);
    }

    return true;
}

bool LoadingScreenState::handleEvent(const sf::Event& event)
{
    auto& guiManager = *getContext().guiManager;

    if (getContext().keyboardMap->isActive(Keys::UPRESS) && GameState::getDoneLoading())
    {
        getContext().player->setActive(true);

        requestStackChange(States::Game);
    }

    return true;
}

void LoadingScreenState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.draw(m_loadingText);
}
