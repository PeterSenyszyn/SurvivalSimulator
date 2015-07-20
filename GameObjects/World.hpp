#pragma once

#include <list>

#include "WorldCell.hpp"
#include "TileMap.hpp"

namespace Ataxia
{
	class World : public sf::Drawable
	{
	public:
		void setCurrentCell(const std::string& id);
		WorldCell::Ptr getCurrentCell() { return m_currentCell; }

		void pushWorldCell(WorldCell::Ptr cell);

		void update(sf::Time dt);

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		WorldCell::Ptr m_currentCell;

		std::list<WorldCell::Ptr> m_worldCells;
	};
}