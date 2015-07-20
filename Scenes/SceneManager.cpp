
#include "SceneManager.hpp"
#include "IntroScene.hpp"
//#include "PlayScene.hpp"

namespace SE
{
	sf::RenderWindow SceneManager::m_window;
	std::unique_ptr<Scene> SceneManager::m_current_scene(nullptr);
	std::unique_ptr<Scene> SceneManager::m_last_scene(nullptr);
	AudioManager SceneManager::m_audio_manager;
	EntityManager SceneManager::m_entity_manager;
	BackgroundManager SceneManager::m_background_manager;
	Ataxia::World SceneManager::m_world;
	sf::View SceneManager::m_current_view;
	sf::Vector2f SceneManager::m_gameMouseCoords;

	SceneManager::SceneManager(std::unique_ptr<Scene> startScene) :
		m_fps("Resources/coalition.ttf", 16, sf::Vector2f(0, 0))
	{
	    m_audio_manager.createMusic("Resources/music/mainmenu.ogg", true, "mainmenu");
	    m_audio_manager.getMusic("mainmenu")->setPlay(true);

		pushScene(std::move(startScene));
	}

	void SceneManager::update(sf::Time dt)
	{
		m_current_scene->update(dt);
		m_audio_manager.update(dt);
		m_fps.update(dt);
		m_background_manager.update(dt);
		m_current_scene->processEntities(m_entity_manager, dt);
	}

	void SceneManager::render()
	{
		m_window.clear();

		if (m_current_scene->getSceneId() != Scene_Ids::PLAY_SCENE)
			m_background_manager.render(m_window);

		else
            m_window.setView(m_current_view);

        sf::Vector2i pixelPos = sf::Mouse::getPosition(m_window);
        m_gameMouseCoords = m_window.mapPixelToCoords(pixelPos);

		m_current_scene->render();

		m_window.setView(m_window.getDefaultView());

		m_fps.render(m_window);

		m_window.display();
	}
}
