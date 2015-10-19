#pragma once

#include "WorldCell.hpp"
#include "RightClickActionManager.hpp"

class Player;

struct Grid
{
	Grid(int pos, Item::Item_Dictionary type, const std::string& name) : pos(pos), numItemsInStack(1), clickedOn(false), type(type), name(name)
	{
		itemLabel = sfg::Label::Create(name + "x1");
	};

	int pos;
	int numItemsInStack;

	bool clickedOn;

	sfg::Label::Ptr itemLabel;
	Item::Item_Dictionary type;

	std::vector<Item::Ptr> items;

	std::string name;
};

//*********************************************************************************************************************************//

class Inventory : public sf::Drawable
{
public:
	Inventory(Player& playerContext);

	void init();

	void addItem(Item::Ptr item);
	void deleteItem(Item::Ptr item);

	void handleEvents(const sf::Event& event);
	void update(sf::Time dt);

	sfg::Window::Ptr getWindow() { return m_window; }

	Player& getPlayerContext() { return *playerContext; }

	const void setWorldCellContext(WorldCell& worldCell) { worldCellContext = &worldCell; }
	WorldCell& getWorldCellContext() { return *worldCellContext; }

	const void setKeyboardMapContext(thor::ActionMap<Keys::KeyboardInput>& context) { keyboardMapContext = &context; }
	thor::ActionMap<Keys::KeyboardInput>& getKeyboardMapContext() { return *keyboardMapContext; }

	const bool getActive() const { return m_active; }
	const void setActive(const bool active) { m_active = active; m_window->Show(active); }

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void setHealthPercentage(float percent) { m_healthBar->SetFraction(percent); }
	void setHungerPercentage(float percent) { m_hungerBar->SetFraction(percent); }
	void setThirstPercentage(float percent) { m_thirstBar->SetFraction(percent); }

private:
	void onItemClicked(Item::Item_Dictionary type, int index);

	inline void initRightClickActions();

	void actionDropItem();
	void actionMoveToContainer();
	void actionClose();

private:
	RightClickActionManager m_rightClickManager;

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

	bool m_active;

	float m_weight;

	std::vector<std::shared_ptr<Grid> > m_grid;

	Player* playerContext;
	WorldCell* worldCellContext;
	thor::ActionMap<Keys::KeyboardInput>* keyboardMapContext;
};