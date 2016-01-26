#pragma once

#include "RightClickActionManager.hpp"
#include "ItemManager.hpp"

struct Grid
{
	Grid(int pos, ItemManager::Item::Item_Dictionary type, const std::string& name) : pos(pos), numItemsInStack(1), clickedOn(false), type(type), name(name)
	{
		itemLabel = sfg::Label::Create(name + "x1");
	};

	int pos;
	int numItemsInStack;

	bool clickedOn;

	sfg::Label::Ptr itemLabel;
	ItemManager::Item::Item_Dictionary type;

	std::vector<ItemManager::Item::Ptr> items;

	std::string name; //Example: Wood, Berry
};

class Inventory
{
public:
	void init();

	void addItem(ItemManager::Item::Ptr item);
	void deleteItem(ItemManager::Item::Ptr item);

	void handleEvents(const sf::Event& event);
	void update(sf::Time dt);

	void updatePlayerInfo(float health, float thirst, float encumbrance, float stamina);

	sfg::Window::Ptr getWindow() { return m_window; }

	const bool getActive() const { return m_active; }
	const void setActive(const bool active) { m_active = active; m_window->Show(active); }

private:
	void onItemClicked(const std::string& itemName, int index);

	inline void initRightClickActions();

	void actionDropItem();
	void actionMoveToContainer();
	void actionClose();

private:
	sfg::Desktop m_desktop;
	std::shared_ptr<sf::Font> m_font;

	sfg::Table::Ptr m_table;
	sfg::Table::Ptr m_statusTable;

	sfg::Window::Ptr m_window;

	sfg::ScrolledWindow::Ptr m_inventoryScrollMenu;
	sfg::ScrolledWindow::Ptr m_statusScrollMenu;

	sfg::Notebook::Ptr m_notebook;

	sfg::Box::Ptr m_inventoryScrollBin;
	sfg::Box::Ptr m_statusScrollBin;

	sfg::Box::Ptr m_itemClickBox;
	sfg::Window::Ptr m_itemClickMenu;

	//Status bar stuff
	sfg::Label::Ptr m_healthLabel;
	sfg::ProgressBar::Ptr m_healthBar;

	sfg::Label::Ptr m_hungerLabel;
	sfg::ProgressBar::Ptr m_hungerBar;

	sfg::Label::Ptr m_thirstLabel;
	sfg::ProgressBar::Ptr m_thirstBar;

	sfg::Label::Ptr m_encumbranceLabel;
	sfg::ProgressBar::Ptr m_encumbranceBar;

	sfg::Label::Ptr m_staminaLabel;
	sfg::ProgressBar::Ptr m_staminaBar;

private:
	RightClickActionManager m_rightClickManager;

	bool m_active;

	std::vector<std::shared_ptr<Grid> > m_grid;
};