#pragma once

#include "Scene.hpp"

namespace SE
{
	class CreditsScene : public Scene
	{
	public:
		//Only SSceneManager can create scenes
		CreditsScene();

		virtual void processInput(InputManager& manager);

		virtual void update(sf::Time dt);

		virtual void processEvents(EventManager& event_manager);

		virtual void render();

	private:
		void handleClock();

		sf::Texture m_thorTexture, m_sfmlTexture;
		sf::Sprite m_thorSprite, m_sfmlSprite;

		sf::Clock m_creditsClock;
		sf::Clock m_milliClock;

		int m_numTimesMilli[10];
		double m_alpha;

		short m_libraryDrawCode;
	};
}