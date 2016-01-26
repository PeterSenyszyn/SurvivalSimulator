#include "stdafx.h"
#include "StorageContainer.hpp"

#include "Application.hpp"
#include "Inventory.hpp"

StorageContainer::StorageContainer(unsigned int storageSpace, const std::string& closedPath, const std::string& openedPath, sf::Vector2f pos, Inventory& context) :
	m_storageSpace(storageSpace),
	m_context(&context),
	m_isClosed(true),
	m_menuOpened(false)
{
	m_closed.loadFromFile(closedPath);
	m_open.loadFromFile(openedPath);

	m_sprite.setTexture(m_closed);

	m_font = std::make_shared<sf::Font>();
	m_font->loadFromFile("Assets/font.ttf");

	m_desktop.GetEngine().GetResourceManager().SetDefaultFont(m_font);
	m_desktop.SetProperty("*", "FontName", "Assets/font.ttf");

	m_window = sfg::Window::Create();
	m_window->SetTitle("Items");
	m_window->SetStyle(sfg::Window::Style::TITLEBAR | sfg::Window::Style::BACKGROUND);
	m_window->SetId("itemmenu");

	m_itemClickMenu = sfg::Window::Create();
	m_itemClickMenu->SetTitle("RightClickMenu");
	m_itemClickMenu->SetStyle(sfg::Window::Style::TITLEBAR | sfg::Window::Style::BACKGROUND);
	m_itemClickMenu->SetId("rightclick");

	m_itemClickBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, adjustForResY(10.f));

	m_itemClickMenu->Add(m_itemClickBox);

	m_storageScrollWindow = sfg::ScrolledWindow::Create();
	m_storageScrollWindow->SetScrollbarPolicy(sfg::ScrolledWindow::HORIZONTAL_NEVER | sfg::ScrolledWindow::VERTICAL_AUTOMATIC);
	m_storageScrollWindow->SetRequisition(sf::Vector2f(adjustForResX(325), adjustForResY(325)));
	m_storageScrollWindow->SetId("storagescrollwindow");

	m_table = sfg::Table::Create();
	m_table->SetRowSpacings(adjustForResX(5.f));
	m_table->SetColumnSpacings(adjustForResY(5.f));
	m_table->SetRequisition(sf::Vector2f(adjustForResX(375), adjustForResX(375)));

	sfg::Context::Get().GetEngine().SetProperty(std::string("#itemmenu"), std::string("BackgroundColor"), sf::Color(85, 87, 82, 200));
	sfg::Context::Get().GetEngine().SetProperty(std::string("#itemmenu"), std::string("TitleBackgroundColor"), sf::Color(90, 106, 80, 220));

	sfg::Context::Get().GetEngine().SetProperty(std::string("#rightclick"), std::string("BackgroundColor"), sf::Color(85, 87, 82, 200));
	sfg::Context::Get().GetEngine().SetProperty(std::string("#rightclick"), std::string("TitleBackgroundColor"), sf::Color(90, 106, 80, 220));

	sfg::Context::Get().GetEngine().SetProperty(std::string("#storagescrollwindow"), std::string("BackgroundColor"), sf::Color(85, 87, 82, 200));
	sfg::Context::Get().GetEngine().SetProperty(std::string("#storagescrollwindow"), std::string("TitleBackgroundColor"), sf::Color(90, 106, 80, 220));

	m_storageBin = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
	m_storageBin->Pack(m_table);
	m_storageBin->SetId("storagebin");

	sfg::Context::Get().GetEngine().SetProperty(std::string("#storagebin"), std::string("BackgroundColor"), sf::Color(85, 87, 82, 200));
	sfg::Context::Get().GetEngine().SetProperty(std::string("#storagebin"), std::string("TitleBackgroundColor"), sf::Color(90, 106, 80, 220));

	m_storageScrollWindow->AddWithViewport(m_storageBin);

	m_window->Add(m_storageScrollWindow);

	m_desktop.Add(m_window);
	m_desktop.Add(m_itemClickMenu);

	m_itemClickMenu->Show(false);
	m_window->Show(false);

	initRightClickActions();
}

void StorageContainer::addItem(ItemManager::Item::Ptr item)
{
	bool itemExists = false;

	for (const auto& iter : m_grid)
	{
		if (iter->type == item->getItemId())
			itemExists = true;
	}

	if (itemExists)
	{
		for (const auto& iter : m_grid)
		{
			if (iter->type == item->getItemId() && iter->items[0]->isStackable())
			{
				iter->numItemsInStack++;
				iter->items.push_back(item);
			}
		}
	}

	else if (!itemExists || !item->isStackable())
	{
		m_grid.push_back(std::shared_ptr<Grid>(new Grid(m_grid.size() - 1, item->getItemId(), item->getName())));

		m_grid[m_grid.size() - 1]->items.push_back(item);
		m_grid[m_grid.size() - 1]->itemLabel->GetSignal(sfg::Widget::OnRightClick).Connect(std::bind(&StorageContainer::onItemClicked, this, m_grid[m_grid.size() - 1]->type, m_grid.size() - 1));
		m_grid[m_grid.size() - 1]->itemLabel->SetRequisition(sf::Vector2f(adjustForResX(200), adjustForResY(200)));
		m_grid[m_grid.size() - 1]->itemLabel->SetId(item->getName());
		m_table->Attach(m_grid[m_grid.size() - 1]->itemLabel, sf::Rect<sf::Uint32>(m_grid.size() - 1, m_grid.size() - 1, 1, 1), sfg::Table::FILL, sfg::Table::FILL, sf::Vector2f(adjustForResX(10.f), adjustForResY(10.f)));
	}

	sfg::Context::Get().GetEngine().SetProperty(std::string("#Wood"), std::string("FontSize"), adjustForResX(18));
	sfg::Context::Get().GetEngine().SetProperty(std::string("#Berries"), std::string("FontSize"), adjustForResX(18));
}

void StorageContainer::deleteItem(ItemManager::Item::Ptr item)
{
	for (int index = 0; index < m_grid.size(); ++index)
	{
		if (m_grid[index]->numItemsInStack == 1)
		{
			m_grid[index]->items.pop_back();
			m_table->Remove(m_grid[index]->itemLabel);
			m_grid.erase(m_grid.begin() + index);

			m_itemClickMenu->Show(false);
			m_itemClickBox->RemoveAll();
		}

		else if (m_grid[index]->numItemsInStack > 1)
		{
			m_grid[index]->items.pop_back();
			m_grid[index]->numItemsInStack--;
		}
	}
}

void StorageContainer::takeItem()
{
	for (int index = 0; index < m_grid.size(); ++index)
	{
		if (m_grid[index]->clickedOn)
		{
			m_context->addItem(m_grid[index]->items.back());
			deleteItem(m_grid[index]->items.back());
		}
	}
}

void StorageContainer::onItemClicked(ItemManager::Item::Item_Dictionary type, int index)
{
	m_itemClickMenu->Show(true);

	m_grid[index]->clickedOn = true;

	m_itemClickBox->Pack(m_rightClickManager.getRightClickActionContext("take")->button);

	switch (type)
	{
	case ItemManager::Item::Item_Dictionary::WOOD:
		m_itemClickMenu->SetTitle("Wood");
		m_itemClickMenu->SetPosition(sf::Vector2f(Application::getMouseCoords().x, Application::getMouseCoords().y - (m_itemClickMenu->GetRequisition().y / 2)));
		m_desktop.BringToFront(m_itemClickMenu);

		break;
	}

	m_itemClickBox->Pack(m_rightClickManager.getRightClickActionContext("close")->button);
}

void StorageContainer::initRightClickActions()
{
	m_rightClickManager.createRightClickAction("take", "Take", std::bind(&StorageContainer::takeItem, this));
	m_rightClickManager.createRightClickAction("close", "Close", std::bind(&StorageContainer::close, this));
}

void StorageContainer::close()
{
	m_isClosed = true;

	m_sprite.setTexture(m_closed);

	m_window->Show(false);
	m_itemClickMenu->Show(false);
	m_itemClickBox->RemoveAll();
	m_menuOpened = false;
}

int StorageContainer::checkDist(const sf::Vector2f& vec)
{
	int distanceX = (vec.x - (m_sprite.getPosition().x + (m_sprite.getGlobalBounds().width / 2)));

	int distanceY = (vec.y - (m_sprite.getPosition().y + (m_sprite.getGlobalBounds().height / 2)));

	return sqrt(distanceX * distanceX + distanceY * distanceY);
}

void StorageContainer::handleEvents(const sf::Event& event)
{
	m_desktop.HandleEvent(event);
}

void StorageContainer::update(sf::Time dt, thor::ActionMap<Keys::KeyboardInput>& keyboardMap)
{
	m_desktop.Update(dt.asSeconds());

	for (const auto& iter : m_grid)
		iter->itemLabel->SetText(iter->name + " x" + std::to_string(iter->numItemsInStack));

	if (m_sprite.getGlobalBounds().contains(Application::getWorldCoords()) && keyboardMap.isActive(Keys::RIGHTMOUSEPRESSED))
	{
		if (checkDist(Player::getPos()) >= 90)
			Player::getConsole().sendMessage("You're too far away to interact with that container!");

		else
		{
			if (m_isClosed)
			{
				m_sprite.setTexture(m_open);

				m_window->Show(true);

				m_menuOpened = true;
			}

			else
			{
				m_sprite.setTexture(m_closed);

				m_window->Show(false);

				m_menuOpened = false;
			}

			m_isClosed = !m_isClosed;
		}
	}

	if (checkDist(Player::getPos()) >= 90 && !m_isClosed)
		close();
}

void StorageContainer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}