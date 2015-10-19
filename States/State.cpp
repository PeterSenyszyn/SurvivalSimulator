#include "stdafx.h"
#include "State.hpp"

#include "StateStack.hpp"

State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, MusicPlayer& music, SoundPlayer& sounds, thor::ActionMap<Keys::KeyboardInput>& keyboardMap,
	SettingsParser& parser, GuiManager& guiManager, Player& player, World& world) :
	window(&window),
	textures(&textures),
	fonts(&fonts),
	music(&music),
	sounds(&sounds),
	keyboardMap(&keyboardMap),
	parser(&parser),
	guiManager(&guiManager),
	player(&player),
	world(&world)
{

}

State::State(StateStack& stack, Context context) :
	m_stack(&stack),
	m_context(context),
	m_stateId(States::None),
	m_justChangedStates(false)
{

}

void State::requestStackPush(States::ID stateID)
{
	m_stack->pushState(stateID);
}

void State::requestStackPop()
{
	m_stack->popState();
}

void State::requestStackClear()
{
	m_stack->clearStates();
}

void State::requestGuiScale()
{
	m_stack->scaleGui();
}

State::Context State::getContext() const
{
	return this->m_context;
}