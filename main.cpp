#include "Engine.hpp"

int main()
{
	SE::Engine engine(sf::VideoMode(1024, 768), "Ataxia - v0.1");

	//For finding delta time
	sf::Clock deltaClock;

	sf::Time lastUpdate = sf::Time::Zero;

	//300 fps max
	sf::Time timePerFrame = sf::seconds(1.f / 300.f);

	while (engine.running())
	{
		lastUpdate += deltaClock.restart();

		while (lastUpdate > timePerFrame)
		{
			lastUpdate -= timePerFrame;

			engine.update(timePerFrame);
			engine.render();
		}
	}

	return 0;
}
