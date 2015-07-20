#pragma once

#include "InputManager.hpp"
#include "EntityManager.hpp"
#include "ObjectManager.hpp"
#include "GUI.hpp"

namespace SE
{
	enum class Scene_Ids
	{
		INTRO_SCENE,
		PLAY_SCENE,
		CREDIT_SCENE
	};

	//Interface for different scenes
	class Scene
	{
	public:
		virtual ~Scene() {};

		//factory
		static std::unique_ptr<Scene> create(Scene_Ids id);

		virtual void processInput(InputManager& manager) {};

		virtual void update(sf::Time dt) {};

		//Process entities in the scene
		//Logic
		virtual void processEntities(EntityManager& entity_manager, sf::Time dt) { /*entity_manager.processEntities(dt, m_input_manager);*/ }

		//Render everything
		virtual void render() {};

		InputManager& getInputManager() { return m_input_manager; }
		ObjectManager& getObjectManager() { return m_object_manager; }

		GUI m_gui;

		Scene_Ids getSceneId() { return m_scene_id; }

	protected:
		Scene(Scene_Ids id);

		//Each scene has its own SInputManager
		InputManager m_input_manager;

		//Each scene also has its own SEntityManager
		EntityManager m_entity_manager;

		ObjectManager m_object_manager;

		Scene_Ids m_scene_id;
	};
}
