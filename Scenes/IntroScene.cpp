
#include "IntroScene.hpp"
//#include "PlayScene.hpp"
#include "SceneManager.hpp"
#include "EntityManager.hpp"
#include "FPS.hpp"
#include "Player.hpp"
#include "Engine.hpp"

namespace SE
{
	IntroScene::IntroScene() :
		Scene(Scene_Ids::INTRO_SCENE),
		m_alpha(0)
	{
		m_timeBeforeAmbient = sf::seconds(thor::random(5, 12));
		m_alphaClock.restart();
		m_milliClock.restart();
		m_ambientClock.restart();

		for (int x = 0; x < 10; ++x)
			m_numTimesMilli[x] = 0;

		auto titleLabel = Label::create("Ataxia", "Resources/coalition.ttf", "title", sf::Vector2f(100, 50));
		titleLabel->getText().setColor(sf::Color(125, 128, 117, 0));
		titleLabel->setDraggable(true);
		m_gui.pushWidget(titleLabel);

		auto createdByLabel = Label::create("Created by Peter Senyszyn\nv0.1", "Resources/coalition.ttf", "createdby", sf::Vector2f(800, 0));
		createdByLabel->getText().setColor(sf::Color(125, 128, 117, 255));
		createdByLabel->getText().setCharacterSize(10);
		m_gui.pushWidget(createdByLabel);

		auto alphaWarningLabel = Label::create("This game is in Early Access Alpha;\nBugs and undesired behavior may occur.", "Resources/coalition.ttf",
            "alphaWarning", sf::Vector2f(0, 735));
        alphaWarningLabel->getText().setColor(sf::Color::Green);
        alphaWarningLabel->getText().setCharacterSize(15);
        m_gui.pushWidget(alphaWarningLabel);

		auto playButton = ButtonLabel::create("Play", "Resources/coalition.ttf", "playbutton",
			sf::Color(125, 128, 117, 0), sf::Color(223, 235, 197, 0), sf::Vector2f(800, 100));
		playButton->getText().setCharacterSize(25);
		playButton->bindOnButtonLabelPress([&] { SceneManager::pushScene(Scene::create(Scene_Ids::PLAY_SCENE)); });
		playButton->setDraggable(true);
		m_gui.pushWidget(playButton);

		auto settingsButton = ButtonLabel::create("Settings", "Resources/coalition.ttf", "settingsbutton",
			sf::Color(125, 128, 117, 0), sf::Color(223, 235, 197, 0), sf::Vector2f(800, 300));
		settingsButton->getText().setCharacterSize(25);
		settingsButton->bindOnButtonLabelPress([] { std::cout << "sup" << std::endl; });
		m_gui.pushWidget(settingsButton);

		auto creditsButton = ButtonLabel::create("Credits", "Resources/coalition.ttf", "creditsbutton",
			sf::Color(125, 128, 117, 0), sf::Color(223, 235, 197, 0), sf::Vector2f(800, 500));
		creditsButton->getText().setCharacterSize(25);
		creditsButton->bindOnButtonLabelPress([&] { SceneManager::pushScene(Scene::create(Scene_Ids::CREDIT_SCENE)); });
		creditsButton->setDraggable(true);
		m_gui.pushWidget(creditsButton);

		auto exitButton = ButtonLabel::create("Exit", "Resources/coalition.ttf", "exitbutton",
			sf::Color(125, 128, 117, 0), sf::Color(223, 235, 197, 0), sf::Vector2f(800, 700));
		exitButton->getText().setCharacterSize(25);
		exitButton->bindOnButtonLabelPress([] { Engine::quit(); });
		m_gui.pushWidget(exitButton);
	}

	void IntroScene::processInput(InputManager& manager)
	{
		if (manager.isActive(User_Input::UPRESS))
            SceneManager::pushScene(Scene::create(Scene_Ids::CREDIT_SCENE));

		else if (manager.isActive(User_Input::ESCAPEPRESS))
			Engine::quit();
	}

	void IntroScene::update(sf::Time dt)
	{
		sf::Event evt;

		m_input_manager.preUpdate();

		updateAmbient();
		updateAlphaTitle();

		while (SceneManager::getWindow().pollEvent(evt))
        {
            m_input_manager.update(dt, evt);
            m_object_manager.handleEvents(evt);
            m_object_manager.update(dt);
        }
	}

	void IntroScene::render()
	{
	    m_object_manager.render(SceneManager::getWindow());
		m_gui.render(SceneManager::getWindow());
	}

	void IntroScene::updateAlphaTitle()
	{
		double time = 100;

		sf::Color first = sf::Color(145, 148, 139, 0);
		sf::Color second = sf::Color(223, 235, 197, 0);

		//Fade into title label
		if (m_alphaClock.getElapsedTime().asSeconds() < 1)
		{
			if (m_numTimesMilli[0] < time)
			{
				if (m_milliClock.getElapsedTime().asMilliseconds() >= 1)
				{
					m_milliClock.restart();

					m_alpha += (255 / time);

					m_numTimesMilli[0]++;
				}
			}

			else
				m_alpha = 255;

			m_gui.getLabel("title")->getText().setColor(sf::Color(first.r, first.g, first.b, m_alpha));
		}

		//Fade into playbutton
		if (m_alphaClock.getElapsedTime().asSeconds() >= 1 &&
			m_alphaClock.getElapsedTime().asSeconds() < 2)
		{
			time = 100;

			if (m_numTimesMilli[1] < time)
			{
				if (m_milliClock.getElapsedTime().asMilliseconds() >= 1)
				{
					m_milliClock.restart();

					m_alpha += (255 / time);

					m_numTimesMilli[1]++;
				}
			}

			else
				m_alpha = 255;

			m_gui.getButtonLabel("playbutton")->getText().setColor(sf::Color(first.r, first.g, first.b, m_alpha));
			m_gui.getButtonLabel("playbutton")->setInactiveColor(sf::Color(first.r, first.g, first.b, m_alpha));
			m_gui.getButtonLabel("playbutton")->setActiveColor(sf::Color(second.r, second.g, second.b, m_alpha));
		}

		//Fade into settingsbutton
		if (m_alphaClock.getElapsedTime().asSeconds() >= 2 &&
			m_alphaClock.getElapsedTime().asSeconds() < 3)
		{
			if (m_numTimesMilli[2] < time)
			{
				if (m_milliClock.getElapsedTime().asMilliseconds() >= 1)
				{
					m_milliClock.restart();

					m_alpha += (255 / time);

					m_numTimesMilli[2]++;
				}
			}

			else
				m_alpha = 255;

			m_gui.getButtonLabel("settingsbutton")->getText().setColor(sf::Color(first.r, first.g, first.b, m_alpha));
			m_gui.getButtonLabel("settingsbutton")->setInactiveColor(sf::Color(first.r, first.g, first.b, m_alpha));
			m_gui.getButtonLabel("settingsbutton")->setActiveColor(sf::Color(second.r, second.g, second.b, m_alpha));
		}

		//Fade into creditsbutton
		if (m_alphaClock.getElapsedTime().asSeconds() >= 3 &&
			m_alphaClock.getElapsedTime().asSeconds() < 4)
		{
			if (m_numTimesMilli[3] < time)
			{
				if (m_milliClock.getElapsedTime().asMilliseconds() >= 1)
				{
					m_milliClock.restart();

					m_alpha += (255 / time);

					m_numTimesMilli[3]++;
				}
			}

			else
				m_alpha = 255;

			m_gui.getButtonLabel("creditsbutton")->getText().setColor(sf::Color(first.r, first.g, first.b, m_alpha));
			m_gui.getButtonLabel("creditsbutton")->setInactiveColor(sf::Color(first.r, first.g, first.b, m_alpha));
			m_gui.getButtonLabel("creditsbutton")->setActiveColor(sf::Color(second.r, second.g, second.b, m_alpha));
		}

		//Fade into exitbutton
		if (m_alphaClock.getElapsedTime().asSeconds() >= 4 &&
			m_alphaClock.getElapsedTime().asSeconds() < 5)
		{
			if (m_numTimesMilli[4] < time)
			{
				if (m_milliClock.getElapsedTime().asMilliseconds() >= 1)
				{
					m_milliClock.restart();

					m_alpha += (255 / time);

					m_numTimesMilli[4]++;
				}
			}

			else
				m_alpha = 255;

			m_gui.getButtonLabel("exitbutton")->getText().setColor(sf::Color(first.r, first.g, first.b, m_alpha));
			m_gui.getButtonLabel("exitbutton")->setInactiveColor(sf::Color(first.r, first.g, first.b, m_alpha));
			m_gui.getButtonLabel("exitbutton")->setActiveColor(sf::Color(second.r, second.g, second.b, m_alpha));
		}
	}

	void IntroScene::updateAmbient()
	{
		/*if (m_ambientClock.getElapsedTime().asSeconds() >= m_timeBeforeAmbient.asSeconds())
		{
			m_ambientClock.restart();

			int randAmbient = thor::random(0, 1);
			float randVolume = thor::random(15.f, 100.f);

			switch (randAmbient)
			{
			case 0:
				SceneManager::getAudioManager().getSound("guncock")->getSound().setVolume(randVolume);
				SceneManager::getAudioManager().getSound("guncock")->getSound().play();

				break;

			case 1:
				SceneManager::getAudioManager().getSound("gunshot")->getSound().setVolume(randVolume);
				SceneManager::getAudioManager().getSound("gunshot")->getSound().play();

				break;
			}

			m_timeBeforeAmbient = sf::seconds(thor::random(5, 12));
		}*/
	}
}
