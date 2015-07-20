#include "Engine.hpp"
#include "IntroScene.hpp"
#include "Icon.hpp"

namespace SE
{
	SceneManager Engine::m_scene_manager(IntroScene::create(Scene_Ids::INTRO_SCENE));
	EventManager Engine::m_event_manager;

	bool Engine::m_running = true;

	unsigned int Engine::m_screenSizeX = 1024;
	unsigned int Engine::m_screenSizeY = 768;

	Engine::Engine(const sf::VideoMode& mode, const std::string& programName)
	{
		sf::ContextSettings context;
		contex.antialiasingLevel = 8;

		m_scene_manager.getWindow().create(mode, programName, !sf::Style::Resize | sf::Style::Titlebar | sf::Style::Close, context);
		m_scene_manager.getWindow().setKeyRepeatEnabled(false);
		m_scene_manager.getWindow().setIcon(shock_icon.width, shock_icon.height, shock_icon.pixel_data);

		m_screenSizeX = mode.width;
		m_screenSizeY = mode.height;

		m_scene_manager.getBackgroundManager().pushBackground(m_scene_manager.getBackgroundManager().createBackground("Resources/background.png", "b1"));
	}

	void Engine::update(sf::Time dt)
	{
		m_scene_manager.update(dt);
	}

	void Engine::render()
	{
		m_scene_manager.render();
	}
}
