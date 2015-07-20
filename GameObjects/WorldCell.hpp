#pragma once

#include <string>
#include <list>
#include <memory>

#include "TileMap.hpp"

namespace Ataxia
{
	class WorldCell : public sf::Drawable, public sf::Transformable
	{
	public:
		typedef std::shared_ptr<WorldCell> Ptr;

		static Ptr create(const std::string& id, bool current);

		void update(sf::Time dt);

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		const void setId(const std::string& id) { m_id = id; }
		const std::string& getId() const { return m_id; }

		const void setIfCurrentCell(bool current) { m_current = current; }
		const bool getIfCurrentCell() const { return m_current; }

		//Getter and setter for update
		//If true, then this cell will update even if not current
		const void setIfUpdate(bool update) { m_update = update; }
		const bool getIfUpdate() const { return m_update; }

		static TileMap& getTileMap() { return m_tileMap; }

	private:
		WorldCell(const std::string& id, bool current);

		std::string m_id;
		std::string m_world_data;

		static TileMap m_tileMap;

		bool m_current;
		bool m_update;
	};
}