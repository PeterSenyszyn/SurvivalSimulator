#pragma once

#include <iostream>
#include <memory>

#include "Scene.hpp"
#include "InputManager.hpp"
#include "Engine.hpp"

namespace SE
{
	class IntroScene : public Scene
	{
	public:
		//Only SSceneManager can create scenes
		IntroScene();

		virtual void processInput(InputManager& manager);

		virtual void update(sf::Time dt);

		virtual void render();

	private:
		void updateAmbient();
		void updateAlphaTitle();

		sf::Clock m_alphaClock;
		sf::Clock m_milliClock;

		sf::Clock m_ambientClock;
		sf::Time m_timeBeforeAmbient;

		int m_numTimesMilli[10];
		double m_alpha;
	};
}