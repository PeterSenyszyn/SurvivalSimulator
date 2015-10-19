#pragma once

#include "StateIdentifiers.hpp"
#include "ResourceIdentifiers.hpp"
#include "Utility.hpp"
#include "SettingsParser.hpp"
#include <map>
#include "Player.hpp"
#include "World.hpp"

#include <Thor/Input.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Thread.hpp>

#include <SFGUI/SFGUI.hpp>

#include <memory>

namespace sf
{
	class RenderWindow;
}

class StateStack;
class Player;
class MusicPlayer;
class SoundPlayer;
class GuiManager;

class State
{
public:
	typedef std::unique_ptr<State> Ptr;

	struct Context
	{
		Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, MusicPlayer& music, SoundPlayer& sounds, thor::ActionMap<Keys::KeyboardInput>& keyboardMap,
			SettingsParser& parser, GuiManager& guiManager, Player& player, World& world);

		sf::RenderWindow* window;
		TextureHolder* textures;
		FontHolder* fonts;
		MusicPlayer* music;
		SoundPlayer* sounds;
		thor::ActionMap<Keys::KeyboardInput>* keyboardMap;
		SettingsParser* parser;
		GuiManager* guiManager;
		Player* player;
		World* world;
	};

public:
	State(StateStack& stack, Context context);
	virtual ~State() {};

	virtual void initGui() = 0;

	virtual void draw() = 0;
	virtual bool update(sf::Time dt) = 0;
	virtual bool handleEvent(const sf::Event& event) = 0;

	void setStateId(States::ID stateId) { m_stateId = stateId; }
	States::ID getStateId() { return m_stateId; }

	StateStack& getStack() { return *m_stack; }

protected:
	void requestStackPush(States::ID stateID);
	void requestStackPop();
	void requestStackClear();
	void requestGuiScale();

	Context getContext() const;

private:
	StateStack* m_stack;
	Context m_context;

	States::ID m_stateId;

	bool m_justChangedStates;
};