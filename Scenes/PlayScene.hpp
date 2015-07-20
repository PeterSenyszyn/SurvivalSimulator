#pragma once

#include "Scene.hpp"

namespace SE
{
	class PlayScene : public Scene
	{
	public:
		//Only SSceneManager can create scenes
		PlayScene();

		virtual void processInput(InputManager& manager);

		virtual void update(sf::Time dt);

		virtual void processEntities(sf::Time dt);

		virtual void processEvents(EventManager& event_manager);

		virtual void render();

	private:
	    bool m_madeMenu;
	};
}
