#include "PlayScene.hpp"
#include "SceneManager.hpp"
#include "Player.hpp"
#include "GUI.hpp"

namespace SE
{
	PlayScene::PlayScene() :
    Scene(Scene_Ids::PLAY_SCENE),
	m_madeMenu(false)
	{
	    SceneManager::getAudioManager().getMusic("mainmenu")->setPlay(false);

		int level[] =
		{
            2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
            2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
            2, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
            2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
            2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
            2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
            2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
            2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
            2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
            2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
            2, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
            2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
            2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
            2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
            2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
            2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
		};

		auto cell = Ataxia::WorldCell::create("main", true);
		cell->getTileMap().load("Resources/spritesheet.png", sf::Vector2u(32, 32), level, 32, 16);
		SceneManager::getWorld().pushWorldCell(cell);
		SceneManager::getWorld().setCurrentCell("main");

		auto chest = Container::create("Resources/chest.png", sf::Vector2f(300, 200), sf::Vector2f(10, 10), true, 15.f, "chest1");
		m_object_manager.pushObject(chest);

		m_entity_manager.pushEntity<Player>(Player::create());
	}

	void PlayScene::processInput(InputManager& manager)
	{
		if (manager.isActive(User_Input::RPRESS))
        {
            SceneManager::getAudioManager().getMusic("mainmenu")->setPlay(true);
            SceneManager::pushScene(Scene::create(Scene_Ids::INTRO_SCENE));
        }

        else if (manager.isActive(User_Input::EPRESS))
        {
            if (m_madeMenu)
                return;

            else
            {
                m_madeMenu = true;

                auto menu = Menu::create("Test Menu", "Resources/caviardreams.ttf", "menu", sf::Vector2f(200, 200), sf::Vector2f(350, 300), sf::Color(112, 138, 144, 150),
                                         sf::Color(112, 138, 144, 150), sf::Color::White);

                auto labelAttached = Label::create("Widget 1", "resources/caviardreams.ttf", "attachedLabel");
                auto labelAttached2 = Label::create("Widget 2", "resources/caviardreams.ttf", "attachedLabel2");
                auto labelAttached3 = Label::create("Widget 3", "resources/caviardreams.ttf", "attachedLabel3");
                labelAttached->getText().setColor(sf::Color::White);
                labelAttached->getText().setCharacterSize(16);
                labelAttached2->getText().setColor(sf::Color::White);
                labelAttached2->getText().setCharacterSize(16);
                labelAttached3->getText().setColor(sf::Color::White);
                labelAttached3->getText().setCharacterSize(16);

                m_gui.pushWidget(menu);
                m_gui.pushWidget(labelAttached);
                m_gui.pushWidget(labelAttached2);
                m_gui.pushWidget(labelAttached3);

                m_gui.getMenu("menu")->attachWidget("attachedLabel", sf::Vector2f(10, 50));
                m_gui.getMenu("menu")->attachWidget("attachedLabel2", sf::Vector2f(10, 70));
                m_gui.getMenu("menu")->attachWidget("attachedLabel3", sf::Vector2f(10, 90));
                m_gui.getMenu("menu")->setDraggable(true);
            }
        }

        else if (manager.isActive(User_Input::LPRESS))
            m_gui.getMenu("menu")->detachWidget("attachedLabel");
	}

	void PlayScene::processEntities(sf::Time dt)
	{

	}

	void PlayScene::update(sf::Time dt)
	{
		sf::Event evt;

		m_input_manager.preUpdate();

		while (SceneManager::getWindow().pollEvent(evt))
        {
            m_input_manager.update(dt, evt);

            m_object_manager.handleEvents(evt);
            m_object_manager.update(dt);
        }

		m_entity_manager.update(dt);

		SceneManager::getWorld().update(dt);
	}

	void PlayScene::processEvents(EventManager& event_manager)
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

	void PlayScene::render()
	{
		SceneManager::getWindow().draw(SceneManager::getWorld());
		m_entity_manager.renderEntities(SceneManager::getWindow());
		m_object_manager.render(SceneManager::getWindow());
		m_gui.render(SceneManager::getWindow());
	}
}
