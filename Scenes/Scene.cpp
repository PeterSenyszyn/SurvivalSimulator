
#include "Scene.hpp"
#include "IntroScene.hpp"
#include "PlayScene.hpp"
#include "CreditsScene.hpp"

namespace SE
{
	Scene::Scene(Scene_Ids id) :
		m_scene_id(id) {};

	std::unique_ptr<Scene> Scene::create(Scene_Ids id)
	{
		switch (id)
		{
		case Scene_Ids::INTRO_SCENE:
			return std::move(std::unique_ptr<IntroScene>(new IntroScene()));
			break;

		case Scene_Ids::PLAY_SCENE:
			return std::move(std::unique_ptr<PlayScene>(new PlayScene()));
			break;

		case Scene_Ids::CREDIT_SCENE:
			return std::move(std::unique_ptr<CreditsScene>(new CreditsScene()));
			break;
		}
	}
}
