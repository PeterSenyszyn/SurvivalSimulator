#pragma once

#include "Utility.hpp"
#include "RightClickActionManager.hpp"
#include "Item.hpp"

class Inventory;
struct Grid;

class StorageContainer : public sf::Drawable
{
public:
	typedef std::shared_ptr<StorageContainer> Ptr;

	static Ptr create(unsigned int storageSpace, const std::string& closedPath, const std::string& openedPath, sf::Vector2f pos, Inventory& context)
	{
		return Ptr(new StorageContainer(storageSpace, closedPath, openedPath, pos, context));
	}

	const bool menuOpened() const { return m_menuOpened; }

	const sf::Sprite& getSprite() { return m_sprite; }

	void addItem(Item::Ptr item);
	void deleteItem(Item::Ptr);
	void takeItem();

	void initRightClickActions();

	void close();

	void handleEvents(const sf::Event& event);

	void update(sf::Time dt, thor::ActionMap<Keys::KeyboardInput>& keyboardMap);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	void onItemClicked(Item::Item_Dictionary type, int index);

	int checkDist(const sf::Vector2f& vec);

private:
	StorageContainer(unsigned int storageSpace, const std::string& closedPath, const std::string& openedPath, sf::Vector2f pos, Inventory& context);

	unsigned int m_storageSpace;

	bool m_isClosed;

	bool m_menuOpened;

	Inventory* m_context;

	RightClickActionManager m_rightClickManager;

	std::vector<std::shared_ptr<Grid> > m_grid;

	sf::Texture m_closed, m_open;
	sf::Sprite m_sprite;

	std::shared_ptr<sf::Font> m_font;
	sfg::Desktop m_desktop;

	sfg::Window::Ptr m_window, m_itemClickMenu;
	sfg::ScrolledWindow::Ptr m_storageScrollWindow;

	sfg::Table::Ptr m_table;

	sfg::Box::Ptr m_itemClickBox, m_storageBin;
};