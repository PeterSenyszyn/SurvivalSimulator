#pragma once

#include <list>

#include "WorldCell.hpp"

class World : public sf::Drawable
{
public:
	void setCurrentCell(const std::string& id);
	static WorldCell::Ptr getCurrentCell() { return m_currentCell; }

	const bool getActive() const { return m_active; }
	void setActive(const bool active) { m_active = active; }

	void pushWorldCell(WorldCell::Ptr cell);

	void handleEvents(const sf::Event& event);

	void update(sf::Time dt, thor::ActionMap<Keys::KeyboardInput>& keyboardMap);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	bool m_active;

	static WorldCell::Ptr m_currentCell;

	std::list<WorldCell::Ptr> m_worldCells;
};