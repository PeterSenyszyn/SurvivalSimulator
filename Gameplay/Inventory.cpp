#include "Inventory.hpp"
#include "Application.hpp"
#include "Player.hpp"

#include <cstring>

void Inventory::init()
{
    m_weight = 0.0;

    m_font = std::make_shared<sf::Font>();
    m_font->loadFromFile("Assets/font.ttf");

    m_desktop.GetEngine().GetResourceManager().SetDefaultFont(m_font);
    m_desktop.SetProperty("*", "FontName", "Assets/font.ttf");

    m_window = sfg::Window::Create();
    m_window->SetTitle("Player Menu");
    m_window->SetStyle(sfg::Window::Style::TITLEBAR | sfg::Window::Style::BACKGROUND);
    m_window->SetId("playermenu");

    m_inventoryScrollMenu = sfg::ScrolledWindow::Create();
    m_inventoryScrollMenu->SetScrollbarPolicy(sfg::ScrolledWindow::HORIZONTAL_NEVER | sfg::ScrolledWindow::VERTICAL_AUTOMATIC);
    m_inventoryScrollMenu->SetRequisition(sf::Vector2f(325, 325));
    m_inventoryScrollMenu->SetId("inventoryscroll");

    m_statusScrollMenu = sfg::ScrolledWindow::Create();
    m_statusScrollMenu->SetScrollbarPolicy(sfg::ScrolledWindow::HORIZONTAL_NEVER | sfg::ScrolledWindow::VERTICAL_AUTOMATIC);
    m_statusScrollMenu->SetRequisition(sf::Vector2f(325, 325));
    m_statusScrollMenu->SetId("statusscroll");

    m_itemClickMenu = sfg::Window::Create();
    m_itemClickMenu->SetTitle("RightClickMenu");
    m_itemClickMenu->SetStyle(sfg::Window::Style::TITLEBAR | sfg::Window::Style::BACKGROUND);
    m_itemClickMenu->SetId("rightclick");

    m_itemClickBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 10.f);

    m_itemClickMenu->Add(m_itemClickBox);

    m_table = sfg::Table::Create();
    m_table->SetRowSpacings(5.f);
    m_table->SetColumnSpacings(5.f);
    m_table->SetRequisition(sf::Vector2f(375, 375));

    //status stuff
    m_statusTable = sfg::Table::Create();
    m_statusTable->SetRowSpacings(10.f);
    m_statusTable->SetColumnSpacings(10.f);
    m_statusTable->SetRequisition(sf::Vector2f(375, 375));

    m_healthLabel = sfg::Label::Create("Health");
    m_healthLabel->SetId("healthlabel");

    m_healthBar = sfg::ProgressBar::Create();
    m_healthBar->SetFraction(100.0);
    m_healthBar->SetRequisition(sf::Vector2f(90, 10));
    m_healthBar->SetId("healthbar");

    m_statusTable->Attach(m_healthLabel, sf::Rect<sf::Uint32>(0, 0, 1, 1), sfg::Table::FILL, sfg::Table::FILL, sf::Vector2f(10.f, 10.f));
    m_statusTable->Attach(m_healthBar, sf::Rect<sf::Uint32>(1, 0, 1, 1), sfg::Table::FILL, sfg::Table::FILL, sf::Vector2f(10.f, 10.f));

    m_hungerLabel = sfg::Label::Create("Hunger");
    m_hungerLabel->SetId("hungerlabel");

    m_hungerBar = sfg::ProgressBar::Create();
    m_hungerBar->SetFraction(100.0);
    m_hungerBar->SetRequisition(sf::Vector2f(90, 10));
    m_hungerBar->SetId("hungerbar");

    m_statusTable->Attach(m_hungerLabel, sf::Rect<sf::Uint32>(2, 0, 1, 1), sfg::Table::FILL, sfg::Table::FILL, sf::Vector2f(10.f, 10.f));
    m_statusTable->Attach(m_hungerBar, sf::Rect<sf::Uint32>(3, 0, 1, 1), sfg::Table::FILL, sfg::Table::FILL, sf::Vector2f(10.f, 10.f));

    m_thirstLabel = sfg::Label::Create("Thirst");
    m_thirstLabel->SetId("thirstlabel");

    m_thirstBar = sfg::ProgressBar::Create();
    m_thirstBar->SetFraction(100.0);
    m_thirstBar->SetRequisition(sf::Vector2f(90, 10));
    m_thirstBar->SetId("thirstbar");

    m_statusTable->Attach(m_thirstLabel, sf::Rect<sf::Uint32>(0, 1, 1, 1), sfg::Table::FILL, sfg::Table::FILL, sf::Vector2f(10.f, 10.f));
    m_statusTable->Attach(m_thirstBar, sf::Rect<sf::Uint32>(1, 1, 1, 1), sfg::Table::FILL, sfg::Table::FILL, sf::Vector2f(10.f, 10.f));

    m_encumbranceLabel = sfg::Label::Create("Encumbrance");
    m_encumbranceLabel->SetId("encumbranceLabel");

    m_encumbranceBar = sfg::ProgressBar::Create();
    m_encumbranceBar->SetFraction(0.0);
    m_encumbranceBar->SetRequisition(sf::Vector2f(90, 10));
    m_encumbranceBar->SetId("encumbranceBar");

    m_statusTable->Attach(m_encumbranceLabel, sf::Rect<sf::Uint32>(2, 1, 1, 1), sfg::Table::FILL, sfg::Table::FILL, sf::Vector2f(10.f, 10.f));
    m_statusTable->Attach(m_encumbranceBar, sf::Rect<sf::Uint32>(3, 1, 1, 1), sfg::Table::FILL, sfg::Table::FILL, sf::Vector2f(10.f, 10.f));

    sfg::Context::Get().GetEngine().SetProperty(std::string("#playermenu"), std::string("BackgroundColor"), sf::Color(85, 87, 82, 200));
    sfg::Context::Get().GetEngine().SetProperty(std::string("#playermenu"), std::string("TitleBackgroundColor"), sf::Color(90, 106, 80, 220));

    sfg::Context::Get().GetEngine().SetProperty(std::string("#rightclick"), std::string("BackgroundColor"), sf::Color(85, 87, 82, 200));
    sfg::Context::Get().GetEngine().SetProperty(std::string("#rightclick"), std::string("TitleBackgroundColor"), sf::Color(90, 106, 80, 220));

    sfg::Context::Get().GetEngine().SetProperty(std::string("#inventoryscroll"), std::string("BackgroundColor"), sf::Color(85, 87, 82, 200));
    sfg::Context::Get().GetEngine().SetProperty(std::string("#inventoryscroll"), std::string("TitleBackgroundColor"), sf::Color(90, 106, 80, 220));

    sfg::Context::Get().GetEngine().SetProperty(std::string("#statusscroll"), std::string("BackgroundColor"), sf::Color(85, 87, 82, 200));
    sfg::Context::Get().GetEngine().SetProperty(std::string("#statusscroll"), std::string("TitleBackgroundColor"), sf::Color(90, 106, 80, 220));

    //sfg::Context::Get().GetEngine().SetProperty(std::string("#hungerlabel"), std::string("FontSize"), 18);
    //sfg::Context::Get().GetEngine().SetProperty(std::string("#thirstlabel"), std::string("FontSize"), 18);

    m_inventoryScrollBin = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
    m_inventoryScrollBin->Pack(m_table);
    m_inventoryScrollBin->SetId("inventorybin");

    m_statusScrollBin = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
    m_statusScrollBin->Pack(m_statusTable);
    m_statusScrollBin->SetId("statusbin");

    sfg::Context::Get().GetEngine().SetProperty(std::string("#inventorybin"), std::string("BackgroundColor"), sf::Color(85, 87, 82, 200));
    sfg::Context::Get().GetEngine().SetProperty(std::string("#inventorybin"), std::string("TitleBackgroundColor"), sf::Color(90, 106, 80, 220));

    sfg::Context::Get().GetEngine().SetProperty(std::string("#statusbin"), std::string("BackgroundColor"), sf::Color(85, 87, 82, 200));
    sfg::Context::Get().GetEngine().SetProperty(std::string("#statusbin"), std::string("TitleBackgroundColor"), sf::Color(90, 106, 80, 220));

    m_notebook = sfg::Notebook::Create();
    m_notebook->AppendPage(m_inventoryScrollBin, sfg::Label::Create("Inventory"));
    m_notebook->AppendPage(m_statusScrollBin, sfg::Label::Create("Player Status"));

    m_inventoryScrollMenu->AddWithViewport(m_notebook);

    m_window->Add(m_inventoryScrollMenu);

    m_desktop.Add(m_window);
    m_desktop.Add(m_itemClickMenu);

    m_itemClickMenu->Show(false);
    setActive(false);

    initRightClickActions();
}

void Inventory::addItem(Item::Ptr item)
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
        m_grid[m_grid.size() - 1]->itemLabel->GetSignal(sfg::Widget::OnRightClick).Connect(std::bind(&Inventory::onItemClicked, this, m_grid[m_grid.size() - 1]->type, m_grid.size() - 1));
        m_grid[m_grid.size() - 1]->itemLabel->SetRequisition(sf::Vector2f(200, 200));
        m_grid[m_grid.size() - 1]->itemLabel->SetId(item->getName());
        m_table->Attach(m_grid[m_grid.size() - 1]->itemLabel, sf::Rect<sf::Uint32>(m_grid.size() - 1, m_grid.size() - 1, 1, 1), sfg::Table::FILL, sfg::Table::FILL, sf::Vector2f(10.f, 10.f));
    }

    m_weight += static_cast<int>(item->getItemId());
}

void Inventory::handleEvents(const sf::Event& event)
{
    m_desktop.HandleEvent(event);
}

void Inventory::update(sf::Time dt)
{
    m_desktop.Update(dt.asSeconds());

    sfg::Context::Get().GetEngine().SetProperty(std::string("#Wood"), std::string("FontSize"), 18);
    sfg::Context::Get().GetEngine().SetProperty(std::string("#Berries", std::string("FontSize"), 18));

    for (const auto& iter : m_grid)
        iter->itemLabel->SetText(iter->name + " x" + std::to_string(iter->numItemsInStack));

    //Over the comfortable amount
    if (m_weight > 90)
}

void Inventory::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

}

void Inventory::onItemClicked(Item::Item_Dictionary type, int index)
{
    m_itemClickMenu->Show(true);

    m_grid[index]->clickedOn = true;

    switch (type)
    {
    case Item::Item_Dictionary::WOOD:
        m_itemClickBox->Pack(m_rightClickManager.getRightClickActionContext("drop")->button);
        m_itemClickMenu->SetTitle("Wood");
        m_itemClickMenu->SetPosition(sf::Vector2f(Application::getMouseCoords().x, Application::getMouseCoords().y - (m_itemClickMenu->GetRequisition().y / 2)));
        m_desktop.BringToFront(m_itemClickMenu);

        break;
    }

    m_itemClickBox->Pack(m_rightClickManager.getRightClickActionContext("close")->button);
}

void Inventory::initRightClickActions()
{
    m_rightClickManager.createRightClickAction("drop", "Drop Item", std::bind(&Inventory::actionDropItem, this, World::getCurrentCell()));
    m_rightClickManager.createRightClickAction("close", "Close", std::bind(&Inventory::actionClose, this));
}

void Inventory::actionDropItem(WorldCell::Ptr worldCell)
{
    for (int index = 0; index < m_grid.size(); ++index)
    {
        if (m_grid[index]->clickedOn)
        {
            m_grid[index]->items.back()->getSprite().setPosition(Player::getPos());

            if (m_grid[index]->numItemsInStack == 1)
            {
                worldCell->addWorldItem(m_grid[index]->items.back());
                m_grid[index]->items.pop_back();
                m_table->Remove(m_grid[index]->itemLabel);
                m_grid.erase(m_grid.begin() + index);

            }

            else if (m_grid[index]->numItemsInStack > 1)
            {
                worldCell->addWorldItem(m_grid[index]->items.back());
                m_grid[index]->items.pop_back();

                m_grid[index]->numItemsInStack--;
            }
        }
    }
}

void Inventory::actionClose()
{
    m_itemClickMenu->Show(false);
    m_itemClickBox->RemoveAll();
}
