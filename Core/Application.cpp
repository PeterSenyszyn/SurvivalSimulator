#include <Application.hpp>
#include <MenuStarManager.hpp>

#include <IntroState.hpp>
#include <SettingsState.hpp>
#include <NewGameState.hpp>
#include <GameState.hpp>
#include <LoadingScreenState.hpp>

#include <iostream>

sf::Vector2u Application::m_windowOptimalNativeRes = sf::Vector2u(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
sf::Vector2u Application::m_windowCurrentRes = sf::Vector2u(1920, 1080);
sf::Vector2f Application::m_resMultiplier = sf::Vector2f(1, 1);
sf::Vector2i Application::m_mouseCoords;
sf::Vector2f Application::m_worldCoords;

MenuStarManager Application::m_menuStarManager(200);

bool Application::m_resized = false;

Application::Application() :
//m_window(sf::VideoMode(1024, 768), "Spatia - v0.1", !sf::Style::Resize | sf::Style::Titlebar | sf::Style::Close),
m_stateStack(State::Context(m_window, m_textures, m_fonts, m_musicPlayer, m_soundPlayer, m_keyboardMap, m_settingsParser, m_guiManager, m_player, m_world)),
m_fpsOn(false)
{
    initKeys();

    sf::ContextSettings contextSettings;
    contextSettings.antialiasingLevel = 16;
    m_window.create(sf::VideoMode(1920, 1080), "Survival Simulator - v0.11", !sf::Style::Resize | sf::Style::Titlebar | sf::Style::Close, contextSettings);

    /*if (!m_settingsParser.loadFromFile("Assets/settings.dat"))
        std::cout << "wtfbbq" << std::endl;

    int x, y;

    m_settingsParser.get("width", x);
    m_settingsParser.get("height", y);

    m_windowCurrentRes = sf::Vector2u(x, y);

    m_window.setSize(m_windowCurrentRes);*/

    m_window.resetGLStates();

    m_window.setKeyRepeatEnabled(false);

    m_fonts.load(Fonts::Main, "Assets/font.ttf");

    m_textures.load(Textures::Particle, "Assets/Particle.png");

    m_fpsText.setFont(m_fonts.get(Fonts::Main));
    m_fpsText.setCharacterSize(16u);

    registerStates();
    m_stateStack.pushState(States::Intro);

    m_musicPlayer.setVolume(50.f);
}

void Application::processInput()
{
    if (m_keyboardMap.isActive(Keys::FPRESS))
        setFpsOn(!fpsOn());

    sf::Event event;

    m_keyboardMap.clearEvents();

    while (m_window.pollEvent(event))
    {
        m_keyboardMap.pushEvent(event);

        m_stateStack.handleEvent(event);

        m_guiManager.handleEvents(event);

        if (event.type == sf::Event::Closed)
            m_window.close();
    }
}

void Application::update(sf::Time dt)
{
    if (fpsOn())
        updateFps(dt);

    m_stateStack.update(dt);

    m_guiManager.update(dt);

    auto currentState = m_stateStack.getCurrentState();

    if (currentState == States::Intro || currentState == States::NewGame || currentState == States::Settings || currentState == States::Loading)
        m_menuStarManager.update(dt);

    m_mouseCoords = sf::Mouse::getPosition(m_window);

    m_worldCoords = m_window.mapPixelToCoords(m_mouseCoords, m_player.getCamera().getView());
}

void Application::render()
{
    m_window.clear();

    auto currentState = m_stateStack.getCurrentState();

    if (currentState == States::Game)
        m_window.setView(m_player.getCamera().getView());

    if (currentState == States::Intro || currentState == States::NewGame || currentState == States::Settings || currentState == States::Loading)
        m_menuStarManager.render(m_window);

    m_stateStack.draw();

    m_window.setView(m_window.getDefaultView());

    m_guiManager.draw(m_window);

    if (fpsOn())
        m_window.draw(m_fpsText);

    m_window.display();
}

void Application::updateFps(sf::Time dt)
{
    float currentTime = m_clock.restart().asSeconds();
    int fps = 1 / (currentTime - m_lastTime);
    m_lastTime = currentTime;

    currentTime = 0;

    m_fpsText.setString(std::to_string(fps));

    if (fps >= 60)
        m_fpsText.setColor(sf::Color::Green);

    else if (fps >= 30 && fps < 60)
        m_fpsText.setColor(sf::Color::Yellow);

    else
        m_fpsText.setColor(sf::Color::Red);
}

void Application::registerStates()
{
    m_stateStack.registerState<IntroState>(States::Intro);
    m_stateStack.registerState<SettingsState>(States::Settings);
    m_stateStack.registerState<NewGameState>(States::NewGame);
    m_stateStack.registerState<GameState>(States::Game);
    m_stateStack.registerState<LoadingScreenState>(States::Loading);
}

void Application::initKeys()
{
    /*********************************************************************************************
    *****************************************PRESS***********************************************/

    //Alphabet (press)
    m_keyboardMap[Keys::KeyboardInput::APRESS] = thor::Action(sf::Keyboard::A, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::BPRESS] = thor::Action(sf::Keyboard::B, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::CPRESS] = thor::Action(sf::Keyboard::C, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::DPRESS] = thor::Action(sf::Keyboard::D, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::EPRESS] = thor::Action(sf::Keyboard::E, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::FPRESS] = thor::Action(sf::Keyboard::F, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::GPRESS] = thor::Action(sf::Keyboard::G, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::HPRESS] = thor::Action(sf::Keyboard::H, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::IPRESS] = thor::Action(sf::Keyboard::I, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::JPRESS] = thor::Action(sf::Keyboard::J, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::KPRESS] = thor::Action(sf::Keyboard::K, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::LPRESS] = thor::Action(sf::Keyboard::L, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::MPRESS] = thor::Action(sf::Keyboard::M, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::NPRESS] = thor::Action(sf::Keyboard::N, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::OPRESS] = thor::Action(sf::Keyboard::O, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::PPRESS] = thor::Action(sf::Keyboard::P, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::QPRESS] = thor::Action(sf::Keyboard::Q, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::RPRESS] = thor::Action(sf::Keyboard::R, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::SPRESS] = thor::Action(sf::Keyboard::S, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::TPRESS] = thor::Action(sf::Keyboard::T, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::UPRESS] = thor::Action(sf::Keyboard::U, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::VPRESS] = thor::Action(sf::Keyboard::V, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::WPRESS] = thor::Action(sf::Keyboard::W, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::XPRESS] = thor::Action(sf::Keyboard::X, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::YPRESS] = thor::Action(sf::Keyboard::Y, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::ZPRESS] = thor::Action(sf::Keyboard::Z, thor::Action::PressOnce);

    //Numbers (press)
    m_keyboardMap[Keys::KeyboardInput::NUM0PRESS] = thor::Action(sf::Keyboard::Num0, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::NUM1PRESS] = thor::Action(sf::Keyboard::Num1, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::NUM2PRESS] = thor::Action(sf::Keyboard::Num2, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::NUM3PRESS] = thor::Action(sf::Keyboard::Num3, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::NUM4PRESS] = thor::Action(sf::Keyboard::Num4, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::NUM5PRESS] = thor::Action(sf::Keyboard::Num5, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::NUM6PRESS] = thor::Action(sf::Keyboard::Num6, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::NUM7PRESS] = thor::Action(sf::Keyboard::Num7, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::NUM8PRESS] = thor::Action(sf::Keyboard::Num8, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::NUM9PRESS] = thor::Action(sf::Keyboard::Num9, thor::Action::PressOnce);

    //Other function keys (press)
    m_keyboardMap[Keys::KeyboardInput::ESCAPEPRESS] = thor::Action(sf::Keyboard::Escape, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::LCONTROLPRESS] = thor::Action(sf::Keyboard::LControl, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::LSHIFTPRESS] = thor::Action(sf::Keyboard::LShift, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::LALTPRESS] = thor::Action(sf::Keyboard::LAlt, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::LSYSTEMPRESS] = thor::Action(sf::Keyboard::LSystem, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::RCONTROLPRESS] = thor::Action(sf::Keyboard::RControl, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::RSHIFTPRESS] = thor::Action(sf::Keyboard::RShift, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::RSYSTEMPRESS] = thor::Action(sf::Keyboard::RSystem, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::MENUPRESS] = thor::Action(sf::Keyboard::Menu, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::LBRACKETPRESS] = thor::Action(sf::Keyboard::LBracket, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::RBRACKETPRESS] = thor::Action(sf::Keyboard::RBracket, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::SEMICOLONPRESS] = thor::Action(sf::Keyboard::SemiColon, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::COMMAPRESS] = thor::Action(sf::Keyboard::Comma, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::PERIODPRESS] = thor::Action(sf::Keyboard::Period, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::QUOTEPRESS] = thor::Action(sf::Keyboard::Quote, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::SLASHPRESS] = thor::Action(sf::Keyboard::Slash, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::BACKSLASHPRESS] = thor::Action(sf::Keyboard::BackSlash, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::TILDEPRESS] = thor::Action(sf::Keyboard::Tilde, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::EQUALPRESS] = thor::Action(sf::Keyboard::Equal, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::DASHPRESS] = thor::Action(sf::Keyboard::Dash, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::SPACEPRESS] = thor::Action(sf::Keyboard::Space, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::RETURNPRESS] = thor::Action(sf::Keyboard::Return, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::BACKSPACEPRESS] = thor::Action(sf::Keyboard::BackSpace, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::TABPRESS] = thor::Action(sf::Keyboard::Tab, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::PAGEUPPRESS] = thor::Action(sf::Keyboard::PageUp, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::PAGEDOWNPRESS] = thor::Action(sf::Keyboard::PageDown, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::ENDPRESS] = thor::Action(sf::Keyboard::End, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::HOMEPRESS] = thor::Action(sf::Keyboard::Home, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::INSERTPRESS] = thor::Action(sf::Keyboard::Insert, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::DELETEPRESS] = thor::Action(sf::Keyboard::Delete, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::ADDPRESS] = thor::Action(sf::Keyboard::Add, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::SUBTRACTPRESS] = thor::Action(sf::Keyboard::Subtract, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::MULTIPLYPRESS] = thor::Action(sf::Keyboard::Multiply, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::DIVIDEPRESS] = thor::Action(sf::Keyboard::Divide, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::LEFTPRESS] = thor::Action(sf::Keyboard::Left, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::RIGHTPRESS] = thor::Action(sf::Keyboard::Right, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::UPPRESS] = thor::Action(sf::Keyboard::Up, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::DOWNPRESS] = thor::Action(sf::Keyboard::Down, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::PAUSEPRESS] = thor::Action(sf::Keyboard::Pause, thor::Action::PressOnce);

    //Numpad (press)
    m_keyboardMap[Keys::KeyboardInput::NUMPAD0PRESS] = thor::Action(sf::Keyboard::Numpad0, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::NUMPAD1PRESS] = thor::Action(sf::Keyboard::Numpad1, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::NUMPAD2PRESS] = thor::Action(sf::Keyboard::Numpad2, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::NUMPAD3PRESS] = thor::Action(sf::Keyboard::Numpad3, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::NUMPAD4PRESS] = thor::Action(sf::Keyboard::Numpad4, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::NUMPAD5PRESS] = thor::Action(sf::Keyboard::Numpad5, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::NUMPAD6PRESS] = thor::Action(sf::Keyboard::Numpad6, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::NUMPAD7PRESS] = thor::Action(sf::Keyboard::Numpad7, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::NUMPAD8PRESS] = thor::Action(sf::Keyboard::Numpad8, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::NUMPAD9PRESS] = thor::Action(sf::Keyboard::Numpad9, thor::Action::PressOnce);

    //Function keys (press)
    m_keyboardMap[Keys::KeyboardInput::F1PRESS] = thor::Action(sf::Keyboard::F1, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::F2PRESS] = thor::Action(sf::Keyboard::F2, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::F3PRESS] = thor::Action(sf::Keyboard::F3, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::F4PRESS] = thor::Action(sf::Keyboard::F4, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::F5PRESS] = thor::Action(sf::Keyboard::F5, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::F6PRESS] = thor::Action(sf::Keyboard::F6, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::F7PRESS] = thor::Action(sf::Keyboard::F7, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::F8PRESS] = thor::Action(sf::Keyboard::F8, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::F9PRESS] = thor::Action(sf::Keyboard::F9, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::F10PRESS] = thor::Action(sf::Keyboard::F10, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::F11PRESS] = thor::Action(sf::Keyboard::F11, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::F12PRESS] = thor::Action(sf::Keyboard::F12, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::F13PRESS] = thor::Action(sf::Keyboard::F13, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::F14PRESS] = thor::Action(sf::Keyboard::F14, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::F15PRESS] = thor::Action(sf::Keyboard::F15, thor::Action::PressOnce);


    /*********************************************************************************************
    *****************************************HOLD************************************************/


    //Alphabet (hold)
    m_keyboardMap[Keys::KeyboardInput::AHOLD] = thor::Action(sf::Keyboard::A, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::BHOLD] = thor::Action(sf::Keyboard::B, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::CHOLD] = thor::Action(sf::Keyboard::C, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::DHOLD] = thor::Action(sf::Keyboard::D, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::EHOLD] = thor::Action(sf::Keyboard::E, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::FHOLD] = thor::Action(sf::Keyboard::F, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::GHOLD] = thor::Action(sf::Keyboard::G, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::HHOLD] = thor::Action(sf::Keyboard::H, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::IHOLD] = thor::Action(sf::Keyboard::I, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::JHOLD] = thor::Action(sf::Keyboard::J, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::KHOLD] = thor::Action(sf::Keyboard::K, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::LHOLD] = thor::Action(sf::Keyboard::L, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::MHOLD] = thor::Action(sf::Keyboard::M, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::NHOLD] = thor::Action(sf::Keyboard::N, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::OHOLD] = thor::Action(sf::Keyboard::O, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::PHOLD] = thor::Action(sf::Keyboard::P, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::QHOLD] = thor::Action(sf::Keyboard::Q, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::RHOLD] = thor::Action(sf::Keyboard::R, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::SHOLD] = thor::Action(sf::Keyboard::S, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::THOLD] = thor::Action(sf::Keyboard::T, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::UHOLD] = thor::Action(sf::Keyboard::U, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::VHOLD] = thor::Action(sf::Keyboard::V, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::WHOLD] = thor::Action(sf::Keyboard::W, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::XHOLD] = thor::Action(sf::Keyboard::X, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::YHOLD] = thor::Action(sf::Keyboard::Y, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::ZHOLD] = thor::Action(sf::Keyboard::Z, thor::Action::Hold);

    //Numbers (hold)
    m_keyboardMap[Keys::KeyboardInput::NUM0HOLD] = thor::Action(sf::Keyboard::Num0, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::NUM1HOLD] = thor::Action(sf::Keyboard::Num1, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::NUM2HOLD] = thor::Action(sf::Keyboard::Num2, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::NUM3HOLD] = thor::Action(sf::Keyboard::Num3, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::NUM4HOLD] = thor::Action(sf::Keyboard::Num4, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::NUM5HOLD] = thor::Action(sf::Keyboard::Num5, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::NUM6HOLD] = thor::Action(sf::Keyboard::Num6, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::NUM7HOLD] = thor::Action(sf::Keyboard::Num7, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::NUM8HOLD] = thor::Action(sf::Keyboard::Num8, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::NUM9HOLD] = thor::Action(sf::Keyboard::Num9, thor::Action::Hold);

    //Other function keys (hold)
    m_keyboardMap[Keys::KeyboardInput::ESCAPEHOLD] = thor::Action(sf::Keyboard::Escape, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::LCONTROLHOLD] = thor::Action(sf::Keyboard::LControl, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::LSHIFTHOLD] = thor::Action(sf::Keyboard::LShift, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::LALTHOLD] = thor::Action(sf::Keyboard::LAlt, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::LSYSTEMHOLD] = thor::Action(sf::Keyboard::LSystem, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::RCONTROLHOLD] = thor::Action(sf::Keyboard::RControl, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::RSHIFTHOLD] = thor::Action(sf::Keyboard::RShift, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::RSYSTEMHOLD] = thor::Action(sf::Keyboard::RSystem, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::MENUHOLD] = thor::Action(sf::Keyboard::Menu, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::LBRACKETHOLD] = thor::Action(sf::Keyboard::LBracket, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::RBRACKETHOLD] = thor::Action(sf::Keyboard::RBracket, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::SEMICOLONHOLD] = thor::Action(sf::Keyboard::SemiColon, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::COMMAHOLD] = thor::Action(sf::Keyboard::Comma, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::PERIODHOLD] = thor::Action(sf::Keyboard::Period, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::QUOTEHOLD] = thor::Action(sf::Keyboard::Quote, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::SLASHHOLD] = thor::Action(sf::Keyboard::Slash, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::BACKSLASHHOLD] = thor::Action(sf::Keyboard::BackSlash, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::TILDEHOLD] = thor::Action(sf::Keyboard::Tilde, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::EQUALHOLD] = thor::Action(sf::Keyboard::Equal, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::DASHHOLD] = thor::Action(sf::Keyboard::Dash, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::SPACEHOLD] = thor::Action(sf::Keyboard::Space, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::RETURNHOLD] = thor::Action(sf::Keyboard::Return, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::BACKSPACEHOLD] = thor::Action(sf::Keyboard::BackSpace, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::TABHOLD] = thor::Action(sf::Keyboard::Tab, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::PAGEUPHOLD] = thor::Action(sf::Keyboard::PageUp, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::PAGEDOWNHOLD] = thor::Action(sf::Keyboard::PageDown, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::ENDHOLD] = thor::Action(sf::Keyboard::End, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::HOMEHOLD] = thor::Action(sf::Keyboard::Home, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::INSERTHOLD] = thor::Action(sf::Keyboard::Insert, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::DELETEHOLD] = thor::Action(sf::Keyboard::Delete, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::ADDHOLD] = thor::Action(sf::Keyboard::Add, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::SUBTRACTHOLD] = thor::Action(sf::Keyboard::Subtract, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::MULTIPLYHOLD] = thor::Action(sf::Keyboard::Multiply, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::DIVIDEHOLD] = thor::Action(sf::Keyboard::Divide, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::LEFTHOLD] = thor::Action(sf::Keyboard::Left, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::RIGHTHOLD] = thor::Action(sf::Keyboard::Right, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::UPHOLD] = thor::Action(sf::Keyboard::Up, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::DOWNHOLD] = thor::Action(sf::Keyboard::Down, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::PAUSEHOLD] = thor::Action(sf::Keyboard::Pause, thor::Action::Hold);

    //Numpad (hold)
    m_keyboardMap[Keys::KeyboardInput::NUMPAD0HOLD] = thor::Action(sf::Keyboard::Numpad0, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::NUMPAD1HOLD] = thor::Action(sf::Keyboard::Numpad1, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::NUMPAD2HOLD] = thor::Action(sf::Keyboard::Numpad2, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::NUMPAD3HOLD] = thor::Action(sf::Keyboard::Numpad3, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::NUMPAD4HOLD] = thor::Action(sf::Keyboard::Numpad4, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::NUMPAD5HOLD] = thor::Action(sf::Keyboard::Numpad5, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::NUMPAD6HOLD] = thor::Action(sf::Keyboard::Numpad6, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::NUMPAD7HOLD] = thor::Action(sf::Keyboard::Numpad7, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::NUMPAD8HOLD] = thor::Action(sf::Keyboard::Numpad8, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::NUMPAD9HOLD] = thor::Action(sf::Keyboard::Numpad9, thor::Action::Hold);

    //Function keys (hold)
    m_keyboardMap[Keys::KeyboardInput::F1HOLD] = thor::Action(sf::Keyboard::F1, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::F2HOLD] = thor::Action(sf::Keyboard::F2, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::F3HOLD] = thor::Action(sf::Keyboard::F3, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::F4HOLD] = thor::Action(sf::Keyboard::F4, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::F5HOLD] = thor::Action(sf::Keyboard::F5, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::F6HOLD] = thor::Action(sf::Keyboard::F6, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::F7HOLD] = thor::Action(sf::Keyboard::F7, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::F8HOLD] = thor::Action(sf::Keyboard::F8, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::F9HOLD] = thor::Action(sf::Keyboard::F9, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::F10HOLD] = thor::Action(sf::Keyboard::F10, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::F11HOLD] = thor::Action(sf::Keyboard::F11, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::F12HOLD] = thor::Action(sf::Keyboard::F12, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::F13HOLD] = thor::Action(sf::Keyboard::F13, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::F14HOLD] = thor::Action(sf::Keyboard::F14, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::F15HOLD] = thor::Action(sf::Keyboard::F15, thor::Action::Hold);

    //Mouse user input
    m_keyboardMap[Keys::KeyboardInput::LEFTMOUSEPRESSED] = thor::Action(sf::Mouse::Left, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::LEFTMOUSEHOLD] = thor::Action(sf::Mouse::Left, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::RIGHTMOUSEPRESSED] = thor::Action(sf::Mouse::Right, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::RIGHTMOUSEHOLD] = thor::Action(sf::Mouse::Right, thor::Action::Hold);
    m_keyboardMap[Keys::KeyboardInput::MIDDLEPRESS] = thor::Action(sf::Mouse::Middle, thor::Action::PressOnce);
    m_keyboardMap[Keys::KeyboardInput::MIDDLEHOLD] = thor::Action(sf::Mouse::Middle, thor::Action::Hold);

    //sf::Event user input
    m_keyboardMap[Keys::KeyboardInput::CLOSED] = thor::Action(sf::Event::Closed);
    m_keyboardMap[Keys::KeyboardInput::TEXTENTERED] = thor::Action(sf::Event::TextEntered);
    m_keyboardMap[Keys::KeyboardInput::MOUSELEFT] = thor::Action(sf::Event::MouseLeft);
    m_keyboardMap[Keys::KeyboardInput::MOUSEENTERED] = thor::Action(sf::Event::MouseEntered);
}
