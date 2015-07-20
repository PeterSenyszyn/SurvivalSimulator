#pragma once

#include <SFML/Graphics.hpp>
#include <Thor/Math.hpp>

#include "SceneManager.hpp"
#include "EventManager.hpp"

namespace SE
{
	class Engine
	{
	public:
		//Initializes Engine + managers
		Engine(const sf::VideoMode& mode, const std::string& programName);

		//Manager getters
		//Static so that they can be easily accessed from other parts of ShockEngine
		static SceneManager& getSceneManager() { return m_scene_manager; }
		static EventManager& getEventManager() { return m_event_manager; }

		//Getter to see if the engine is running
		static const bool running() { return m_running; }
		static const void quit() { m_running = false; }

		//Updates errrythang
		void update(sf::Time dt);

		void render();

		static const unsigned int getScreenSizeX() { return m_screenSizeX; }
		static const unsigned int getScreenSizeY() { return m_screenSizeY; }

	private:
		//Only one of these managers can ever exist
		static SceneManager m_scene_manager;
		static EventManager m_event_manager;

		static bool m_running;

		sf::Clock m_clock;
		float m_lastTime;

		static unsigned int m_screenSizeX, m_screenSizeY;
	};
}
