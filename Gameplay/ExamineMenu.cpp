#include "ExamineMenu.hpp"
#include "Player.hpp"
#include "Application.hpp"

ExamineMenu::ExamineMenu(Player* player)
{
    m_font = std::make_shared<sf::Font>();
    m_font->loadFromFile("Assets/font.ttf");

    initActions(player);

    m_desktop.GetEngine().GetResourceManager().SetDefaultFont(m_font);
    m_desktop.SetProperty("*", "FontName", "Assets/font.ttf");

    m_buttonBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, adjustForResY(10.f));

    m_actionProgressBar = sfg::ProgressBar::Create();
    m_actionProgressBar->SetRequisition(sf::Vector2f(adjustForResX(100), adjustForResY(20)));

    m_window = sfg::Window::Create();
    m_window->SetTitle("ExamineMenu");
    m_window->SetStyle(sfg::Window::Style::TITLEBAR | sfg::Window::Style::BACKGROUND);
    m_window->SetId("ExamineMenu");

    m_window->Add(m_buttonBox);

    sfg::Context::Get().GetEngine().SetProperty(std::string("#ExamineMenu"), std::string("BackgroundColor"), sf::Color(85, 87, 82, 200));
    sfg::Context::Get().GetEngine().SetProperty(std::string("#ExamineMenu"), std::string("TitleBackgroundColor"), sf::Color(90, 106, 80, 220));

    m_desktop.Add(m_window);

    setActive(false);
}

void ExamineMenu::init(TileMap::TileEntityRef::Ptr entityRef, Player* player)
{
    setActive(true);

    m_buttonBox->RemoveAll();
    m_actionProgressBar = sfg::ProgressBar::Create();
    m_actionProgressBar->SetRequisition(sf::Vector2f(adjustForResX(100), adjustForResY(20)));
    m_actionManager.resetAllGui();

    m_window->SetTitle(entityRef->tileName);

    if (entityRef->collectable)
    {
        m_buttonBox->Pack(m_actionManager.getActionContext("harvestwood")->button);

        m_actionManager.getActionContext("harvestwood")->button->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&Player::onCollectPress, player, m_actionManager));
    }

    m_buttonBox->Pack(m_actionManager.getActionContext("close")->button);

    m_actionManager.getActionContext("close")->button->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&ExamineMenu::setActive, this, false));
    m_actionManager.getActionContext("close")->button->Show(true);

    m_buttonBox->Pack(m_actionProgressBar);

    m_window->SetPosition(sf::Vector2f(Application::getMouseCoords().x, Application::getMouseCoords().y - (m_window->GetRequisition().y / 2)));

    m_window->Add(m_buttonBox);
}

void ExamineMenu::init(Item::Ptr itemRef, Player* player, World& world)
{
    setActive(true);

    m_buttonBox->RemoveAll();
    m_actionProgressBar = sfg::ProgressBar::Create();
    m_actionManager.resetAllGui();

    m_window->SetTitle(itemRef->getName());

    m_buttonBox->Pack(m_actionManager.getActionContext("pickup")->button);
    m_actionManager.getActionContext("pickup")->button->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&Player::onPickupPress, player, world));

    m_actionManager.getActionContext("close")->button->Show(true);

    m_buttonBox->Pack(m_actionManager.getActionContext("close")->button);

    m_actionManager.getActionContext("close")->button->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&ExamineMenu::setActive, this, false));

    m_window->Add(m_buttonBox);

    m_window->SetPosition(sf::Vector2f(Application::getMouseCoords().x, Application::getMouseCoords().y - (m_window->GetRequisition().y / 2)));
}

void ExamineMenu::handleEvents(const sf::Event& event)
{
    if (m_active)
        m_desktop.HandleEvent(event);
}

void ExamineMenu::update(sf::Time dt, Player* player)
{
    if (m_active)
    {
        m_desktop.Update(dt.asSeconds());

        m_actionManager.update(m_actionProgressBar, player);
    }
}

void ExamineMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

}

void ExamineMenu::initActions(Player* player)
{
    //For clicking on tile entities
    m_actionManager.createAction(5.0, "harvestwood", "Harvest Wood", std::bind(&Player::addItem, player, Item::create(Item::Item_Dictionary::WOOD, "Wood", "Assets/logs.png", "Assets/logs.png", false, true, true)));
    m_actionManager.createAction(0.0, "close", "Close", []{});

    //For clicking on items that dropped on the ground
    m_actionManager.createAction(0.0, "pickup", "Pick up", [this] { m_window->Show(false); });
}

void ExamineMenu::Action::update(sfg::ProgressBar::Ptr progressBar, Player* player)
{
    if ((actionClock.getElapsedTime().asSeconds() / actionTime >= 1.0) || (actionTime == 0.0))
    {
        active = false;
        progressBar->SetFraction(0.0);

        finishedMethod();
    }

    else if (player->checkDistanceTileRef() >= 90)
    {
        active = false;
        progressBar->SetFraction(0.0);
    }

    else
        progressBar->SetFraction(actionClock.getElapsedTime().asSeconds() / actionTime);
}
