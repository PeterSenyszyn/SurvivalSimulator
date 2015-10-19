#pragma once

#include "State.hpp"
#include "StateIdentifiers.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

#include <vector>
#include <utility>
#include <functional>
#include <map>

namespace sf
{
	class Event;
	class RenderWindow;
}

class StateStack : private sf::NonCopyable
{
public:
	enum Action
	{
		Push,
		Change,
		Pop,
		Clear,
	};

public:
	explicit StateStack(State::Context context);

	template <typename T> void registerState(States::ID stateID);

	void update(sf::Time dt);
	void handleEvent(const sf::Event& event);
	void draw();

	void pushState(States::ID stateID);
	void popState();
	void clearStates();
	void scaleGui();

	bool isEmpty() const;

	States::ID getCurrentState() { return m_currentStateId; }

private:
	State::Ptr createState(States::ID stateID);
	void applyPendingChanges();

private:
	struct PendingChange
	{
		explicit PendingChange(Action action, States::ID stateID = States::None);

		Action action;
		States::ID stateID;
	};

private:
	std::vector<State::Ptr> m_stack;
	std::vector<PendingChange> m_pendingList;

	State::Context m_context;

	States::ID m_currentStateId;

	std::map<States::ID, std::function<State::Ptr()> > m_factories;
};

template <typename T>
void StateStack::registerState(States::ID stateID)
{
	m_factories[stateID] = [this]()
	{
		return State::Ptr(new T(*this, m_context));
	};
}