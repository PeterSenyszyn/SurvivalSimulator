#pragma once

#include <typeinfo>
#include <memory>

#include "Scene.hpp"
#include "EntityManager.hpp"
#include "AudioManager.hpp"
#include "FPS.hpp"
#include "GUI.hpp"
#include "World.hpp"

namespace SE
{
	class SEngine;

	//Controls the creation of scenes and holds the current scene
	class SceneManager
	{
	public:
		friend class SEngine;

		SceneManager(std::unique_ptr<Scene> startScene);

		static const void pushScene(std::unique_ptr<Scene> scene)
		{
			m_last_scene = std::move(m_current_scene);
			m_current_scene = std::move(scene);
		}

		void update(sf::Time dt);

		void render();

		static sf::RenderWindow& getWindow() { return m_window; }

		static AudioManager& getAudioManager() { return m_audio_manager; }
		static EntityManager& getEntityManager() { return m_entity_manager; }
		static BackgroundManager& getBackgroundManager() { return m_background_manager; }

		static Scene& getCurrentScene() { return *m_current_scene; }

		static Ataxia::World& getWorld() { return m_world; }

		static sf::View& getView() { return m_current_view; }

		static void setGameMouseCoords(const sf::Vector2f& coords) { m_gameMouseCoords = coords; }
		static sf::Vector2f& getGameMouseCoords() { return m_gameMouseCoords; }

	private:
		//Entity manager
		static EntityManager m_entity_manager;

		//Audio manager
		static AudioManager m_audio_manager;

		//FPS object
		FPS m_fps;

		//Pointer to the current scene
		static std::unique_ptr<Scene> m_current_scene;

		//Pointer to the last scene
		static std::unique_ptr<Scene> m_last_scene;

		static sf::RenderWindow m_window;

		static sf::View m_current_view;

		static BackgroundManager m_background_manager;

		static Ataxia::World m_world;

		static sf::Vector2f m_gameMouseCoords;
	};
}

