#ifndef APPLICATION_H
#define APPLICATION_H

#include <ResourceHolder.hpp>
#include <ResourceIdentifiers.hpp>
#include <StateStack.hpp>
#include <MusicPlayer.hpp>
#include <SoundPlayer.hpp>
#include <GuiManager.hpp>

#include <SFML/System/Time.hpp>

class MenuStarManager;

class Application
{
public:
    Application();

    void processInput();
    void update(sf::Time dt);
    void render();

    const bool running() { return m_window.isOpen(); }
    void quit() { m_window.close(); }

    const bool fpsOn() { return m_fpsOn; }
    void setFpsOn(bool fpsOn) { m_fpsOn = fpsOn; }

    static const bool resized() { return m_resized; }
    static void setResized(bool resized) { m_resized = resized; }

    static sf::Vector2u getOptimalResolution() { return m_windowOptimalNativeRes; }
    static sf::Vector2u getCurrentResolution() { return m_windowCurrentRes; }
    static sf::Vector2f getResMultiplier() { return m_resMultiplier; }

    static sf::Vector2i& getMouseCoords() { return m_mouseCoords; }
    static sf::Vector2f& getWorldCoords() { return m_worldCoords; }

    static void setCurrentResolution(const sf::Vector2u& res) { m_windowCurrentRes = res; }

private:
    void updateFps(sf::Time dt);
    void registerStates();

    void initKeys();

private:
    sf::RenderWindow m_window;

    TextureHolder m_textures;
    FontHolder m_fonts;

    MusicPlayer m_musicPlayer;
    SoundPlayer m_soundPlayer;

    StateStack m_stateStack;

    thor::ActionMap<Keys::KeyboardInput> m_keyboardMap;

    SettingsParser m_settingsParser;

    GuiManager m_guiManager;

    Player m_player;

    World m_world;

    static MenuStarManager m_menuStarManager;

    bool m_fpsOn;
    static bool m_resized;

    sf::Text m_fpsText;
    sf::Clock m_clock;
    unsigned int m_lastTime;

    static sf::Vector2u m_windowOptimalNativeRes, m_windowCurrentRes;
    static sf::Vector2f m_resMultiplier;
    static sf::Vector2i m_mouseCoords;
    static sf::Vector2f m_worldCoords;
};

static float adjustForResX(float val)
{
    return val * (static_cast<float>(Application::getCurrentResolution().x) / 1920.f);
}

static float adjustForResY(float val)
{
    return val * (static_cast<float>(Application::getCurrentResolution().y) / 1080.f);
}

#endif // APPLICATION_H
