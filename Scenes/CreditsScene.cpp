
#include "CreditsScene.hpp"
#include "SceneManager.hpp"

namespace SE
{
	CreditsScene::CreditsScene() :
		Scene(Scene_Ids::CREDIT_SCENE),
		m_libraryDrawCode(-1),
		m_alpha(0)
	{
		m_creditsClock.restart();
		auto programmingLabel = Label::create("Programming:\n\nPeter Senyszyn - \"The Terminator\"",
			"Resources/coalition.ttf", "programming");
		programmingLabel->setPosition(sf::Vector2f(100, 50));
		programmingLabel->getText().setCharacterSize(20);
		programmingLabel->getText().setColor(sf::Color(125, 128, 117, 0));
		programmingLabel->setVisible(false);
		m_gui.pushWidget(programmingLabel);

		auto artLabel = Label::create("Art:\n\nJose Jaramillo - \"Archangel\"",
			"Resources/coalition.ttf", "art");
		artLabel->setPosition(sf::Vector2f(100, 50));
		artLabel->getText().setColor(sf::Color(125, 128, 117, 0));
		artLabel->getText().setCharacterSize(20);
		artLabel->setVisible(false);
		m_gui.pushWidget(artLabel);

		auto sfmlLabel = Label::create("Created using SFML", "Resources/coalition.ttf", "sfml");
		sfmlLabel->setPosition(sf::Vector2f(350, 100));
		sfmlLabel->getText().setColor(sf::Color(125, 128, 117, 0));
		sfmlLabel->getText().setCharacterSize(20);
		sfmlLabel->setVisible(false);
		m_gui.pushWidget(sfmlLabel);

		auto thorLabel = Label::create("Created using Thor", "Resources/coalition.ttf", "thor");
		thorLabel->setPosition(sf::Vector2f(350, 100));
		thorLabel->getText().setColor(sf::Color(125, 128, 117, 0));
		thorLabel->getText().setCharacterSize(20);
		thorLabel->setVisible(false);
		m_gui.pushWidget(thorLabel);

		m_sfmlTexture.loadFromFile("Resources/sfml.png");
		m_sfmlSprite.setTexture(m_sfmlTexture);
		m_sfmlSprite.setPosition(200, 150);

		m_thorTexture.loadFromFile("Resources/thor.png");
		m_thorSprite.setTexture(m_thorTexture);
		m_thorSprite.setPosition(200, 150);

		for (auto iter = 0; iter < 9; ++iter)
			m_numTimesMilli[iter] = 0;
	}

	void CreditsScene::processInput(InputManager& manager)
	{
		if (manager.isActive(User_Input::ESCAPEPRESS) ||
			m_creditsClock.getElapsedTime().asSeconds() >= 38)
			SceneManager::pushScene(Scene::create(Scene_Ids::INTRO_SCENE));
	}

	void CreditsScene::handleClock()
	{
		double time = 150;
		sf::Time elapsed;

		sf::Color first = sf::Color(145, 148, 139, 0);

		//Fade into programming label
		if (m_creditsClock.getElapsedTime().asSeconds() >= 2 &&
			m_creditsClock.getElapsedTime().asSeconds() < 6)
		{
			m_gui.getLabel("programming")->setVisible(true);

			if (m_numTimesMilli[0] < time)
			{
				elapsed = m_milliClock.restart();

				if (elapsed.asMilliseconds() >= 1)
				{
					m_alpha += (255 / time);
					m_numTimesMilli[0]++;
				}
			}

			else
				m_alpha = 255;

			m_gui.getLabel("programming")->getText().setColor(sf::Color(first.r, first.g, first.b, m_alpha));
		}

		//Fade out of programming label
		else if (m_creditsClock.getElapsedTime().asSeconds() >= 6 &&
			m_creditsClock.getElapsedTime().asSeconds() < 10)
		{
			if (m_numTimesMilli[1] < time)
			{
				elapsed = m_milliClock.restart();

				if (elapsed.asMilliseconds() >= 1)
				{
					m_alpha -= (255 / time);
					m_numTimesMilli[1]++;
				}
			}

			else
			{
				m_alpha = 0;
				m_gui.getLabel("programming")->setVisible(false);
			}

			m_gui.getLabel("programming")->getText().setColor(sf::Color(first.r, first.g, first.b, m_alpha));
		}

		//Fade into art label
		else if (m_creditsClock.getElapsedTime().asSeconds() >= 10 &&
			m_creditsClock.getElapsedTime().asSeconds() < 14)
		{
			m_gui.getLabel("art")->setVisible(true);

			if (m_numTimesMilli[2] < time)
			{
				elapsed = m_milliClock.restart();

				if (elapsed.asMilliseconds() >= 1)
				{
					m_alpha += (255 / time);
					m_numTimesMilli[2]++;
				}
			}

			else
				m_alpha = 255;

			m_gui.getLabel("art")->getText().setColor(sf::Color(first.r, first.g, first.b, m_alpha));
		}

		//Fade out of art label
		else if (m_creditsClock.getElapsedTime().asSeconds() >= 14 &&
			m_creditsClock.getElapsedTime().asSeconds() < 18)
		{
			if (m_numTimesMilli[3] < time)
			{
				elapsed = m_milliClock.restart();

				if (elapsed.asMilliseconds() >= 1)
				{
					m_alpha -= (255 / time);
					m_numTimesMilli[3]++;
				}
			}

			else
			{
				m_alpha = 0;
				m_gui.getLabel("art")->setVisible(false);
			}

			m_gui.getLabel("art")->getText().setColor(sf::Color(first.r, first.g, first.b, m_alpha));
		}

		//Fade into sfml label
		else if (m_creditsClock.getElapsedTime().asSeconds() >= 18 &&
			m_creditsClock.getElapsedTime().asSeconds() < 20)
		{
			time = 100;
			m_gui.getLabel("sfml")->setVisible(true);

			if (m_numTimesMilli[4] < time)
			{
				elapsed = m_milliClock.restart();

				if (elapsed.asMilliseconds() >= 1)
				{
					m_alpha += (255 / time);
					m_numTimesMilli[4]++;
				}
			}

			else
				m_alpha = 255;

			m_gui.getLabel("sfml")->getText().setColor(sf::Color(first.r, first.g, first.b, m_alpha));
		}

		//Fade into sfml image
		else if (m_creditsClock.getElapsedTime().asSeconds() >= 20 &&
			m_creditsClock.getElapsedTime().asSeconds() < 24)
		{
			time = 150;
			m_libraryDrawCode = 0;

			if (m_numTimesMilli[5] < time)
			{
				elapsed = m_milliClock.restart();

				if (elapsed.asMilliseconds() >= 1)
				{
					m_alpha += (255 / time);
					m_numTimesMilli[5]++;
				}
			}

			else
				m_alpha = 255;

			m_sfmlSprite.setColor(sf::Color(255, 255, 255, m_alpha));
		}

		//Fade out sfml image and sfml label
		else if (m_creditsClock.getElapsedTime().asSeconds() >= 24 &&
			m_creditsClock.getElapsedTime().asSeconds() < 28)
		{
			if (m_numTimesMilli[6] < time)
			{
				elapsed = m_milliClock.restart();

				if (elapsed.asMilliseconds() >= 1)
				{
					m_alpha -= (255 / time);
					m_numTimesMilli[6]++;
				}
			}

			else
			{
				m_alpha = 0;
				m_gui.getLabel("sfml")->setVisible(false);
				m_libraryDrawCode = -1;
			}

			m_gui.getLabel("sfml")->getText().setColor(sf::Color(first.r, first.g, first.b, m_alpha));
			m_sfmlSprite.setColor(sf::Color(255, 255, 255, m_alpha));
		}

		//Fade in thor label
		else if (m_creditsClock.getElapsedTime().asSeconds() >= 28 &&
			m_creditsClock.getElapsedTime().asSeconds() < 30)
		{
			time = 100;
			m_gui.getLabel("thor")->setVisible(true);

			if (m_numTimesMilli[7] < time)
			{
				elapsed = m_milliClock.restart();

				if (elapsed.asMilliseconds() >= 1)
				{
					m_alpha += (255 / time);
					m_numTimesMilli[7]++;
				}
			}

			else
				m_alpha = 255;

			m_gui.getLabel("thor")->getText().setColor(sf::Color(first.r, first.g, first.b, m_alpha));
		}

		//Fade in thor image
		else if (m_creditsClock.getElapsedTime().asSeconds() >= 30 &&
			m_creditsClock.getElapsedTime().asSeconds() < 34)
		{
			time = 150;
			m_libraryDrawCode = 1;

			if (m_numTimesMilli[8] < time)
			{
				elapsed = m_milliClock.restart();

				if (elapsed.asMilliseconds() >= 1)
				{
					m_alpha += (255 / time);
					m_numTimesMilli[8]++;
				}
			}

			else
				m_alpha = 255;

			m_thorSprite.setColor(sf::Color(255, 255, 255, m_alpha));
		}

		//Fade out thor label and image
		else if (m_creditsClock.getElapsedTime().asSeconds() >= 34 &&
			m_creditsClock.getElapsedTime().asSeconds() < 36)
		{
			if (m_numTimesMilli[9] < time)
			{
				elapsed = m_milliClock.restart();

				if (elapsed.asMilliseconds() >= 1)
				{
					m_alpha -= (255 / time);
					m_numTimesMilli[9]++;
				}
			}

			else
			{
				m_alpha = 0;
				m_gui.getLabel("thor")->setVisible(false);
				m_libraryDrawCode = -1;
			}

			m_gui.getLabel("thor")->getText().setColor(sf::Color(first.r, first.g, first.b, m_alpha));
			m_thorSprite.setColor(sf::Color(255, 255, 255, m_alpha));
		}
	}

	void CreditsScene::update(sf::Time dt)
	{
		sf::Event evt;

		m_input_manager.preUpdate();

		handleClock();

		while (SceneManager::getWindow().pollEvent(evt))
        {
            m_input_manager.update(dt, evt);

            m_object_manager.handleEvents(evt);
            m_object_manager.update(dt);
        }
	}

	void CreditsScene::processEvents(EventManager& event_manager)
	{
		while (!event_manager.queueEmpty())
		{
			switch (event_manager.getFrontId())
			{
			case EVENT_ENTITY_CREATED:

				break;
			}

			event_manager.popFront();
		}
	}

	void CreditsScene::render()
	{
	    m_object_manager.render(SceneManager::getWindow());
		m_gui.render(SceneManager::getWindow());

		if (m_libraryDrawCode == 0)
			SceneManager::getWindow().draw(m_sfmlSprite);

		else if (m_libraryDrawCode == 1)
			SceneManager::getWindow().draw(m_thorSprite);
	}
}
