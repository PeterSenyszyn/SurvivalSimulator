#include <IntroState.hpp>
#include <SettingsState.hpp>
#include <NewGameState.hpp>
#include <GameState.hpp>
#include <LoadingScreenState.hpp>

#include <Utility.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>

IntroState::IntroState(StateStack& stack, Context context) :
State(stack, context)
{
    setStateId(States::Intro);

    initGui();
}

void IntroState::initGui()
{
    playButton = sfg::Button::Create("Play");

    settingsButton = sfg::Button::Create("Settings");

    creditsButton = sfg::Button::Create("Credits");

    exitButton = sfg::Button::Create("Exit");

    newGameButton = sfg::Button::Create("New Game");

    loadGameButton = sfg::Button::Create("Load Game");

    title = sfg::Label::Create("Spatia");

    auto& guiManager = *getContext().guiManager;

    mainWindow = guiManager.createWindow(States::Intro, "mainWindow", sfg::Window::Style::NO_STYLE);
    loadWindow = guiManager.createWindow(States::Intro, "loadWindow", sfg::Window::Style::NO_STYLE);

    mainBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, adjustForResY(125));
    loadBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, adjustForResY(125));

    playButton->SetId("playButton");
    playButton->SetRequisition(sf::Vector2f(adjustForResX(200), adjustForResY(100)));
    playButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&IntroState::playButtonClicked, this));
    guiManager.setDesktopProperty(std::string("#playButton"), std::string("FontSize"), adjustForResX(25.f));
    guiManager.setDesktopProperty(std::string("#playButton"), std::string("BackgroundColor"), sf::Color(85, 87, 82, 220));

    settingsButton->SetId("settingsButton");
    settingsButton->SetRequisition(sf::Vector2f(adjustForResX(200), adjustForResY(100)));
    settingsButton->GetSignal(sfg::Button::OnLeftClick).Connect([&] { requestStackPush(States::Settings); });
    guiManager.setDesktopProperty(std::string("#settingsButton"), std::string("FontSize"), adjustForResX(25.f));
    guiManager.setDesktopProperty(std::string("#settingsButton"), std::string("BackgroundColor"), sf::Color(85, 87, 82, 220));

    creditsButton->SetId("creditsButton");
    creditsButton->SetRequisition(sf::Vector2f(adjustForResX(200), adjustForResY(100)));
    guiManager.setDesktopProperty(std::string("#creditsButton"), std::string("FontSize"), adjustForResX(25.f));
    guiManager.setDesktopProperty(std::string("#creditsButton"), std::string("BackgroundColor"), sf::Color(85, 87, 82, 220));

    exitButton->SetId("exitButton");
    exitButton->SetRequisition(sf::Vector2f(adjustForResX(200), adjustForResY(100)));
    exitButton->GetSignal(sfg::Button::OnLeftClick).Connect([&] { getContext().window->close(); } );
    guiManager.setDesktopProperty(std::string("#exitButton"), std::string("FontSize"), adjustForResX(25.f));
    guiManager.setDesktopProperty(std::string("#exitButton"), std::string("BackgroundColor"), sf::Color(85, 87, 82, 220));

    newGameButton->SetId("newGameButton");
    newGameButton->SetRequisition(sf::Vector2f(adjustForResX(200), adjustForResY(100)));
    newGameButton->GetSignal(sfg::Button::OnLeftClick).Connect([&] { requestStackPush(States::NewGame); });
    guiManager.setDesktopProperty(std::string("#newGameButton"), std::string("FontSize"), adjustForResX(25.f));
    guiManager.setDesktopProperty(std::string("#newGameButton"), std::string("BackgroundColor"), sf::Color(85, 87, 82, 220));
    newGameButton->Show(false);

    loadGameButton->SetId("loadGameButton");
    loadGameButton->SetRequisition(sf::Vector2f(adjustForResX(200), adjustForResY(100)));
    guiManager.setDesktopProperty(std::string("#loadGameButton"), std::string("FontSize"), adjustForResX(25.f));
    guiManager.setDesktopProperty(std::string("#loadGameButton"), std::string("BackgroundColor"), sf::Color(85, 87, 82, 220));
    loadGameButton->Show(false);

    title->SetId("title");
    guiManager.setDesktopProperty(std::string("#title"), std::string("FontSize"), adjustForResX(70.f));

    mainBox->Pack(title);
    mainBox->Pack(playButton);
    mainBox->Pack(settingsButton);
    mainBox->Pack(creditsButton);
    mainBox->Pack(exitButton);

    loadBox->Pack(newGameButton);
    loadBox->Pack(loadGameButton);

    mainWindow->Add(mainBox);
    loadWindow->Add(loadBox);

    centerWindowX(mainWindow);

    loadWindow->SetPosition({adjustForResX(1200), adjustForResY(191)});
    settingsButton->SetRequisition(sf::Vector2f(adjustForResX(200), adjustForResY(100)));
}

bool IntroState::update(sf::Time dt)
{
    return true;
}

bool IntroState::handleEvent(const sf::Event& event)
{
    auto& guiManager = *getContext().guiManager;

    if (getContext().keyboardMap->isActive(Keys::ESCAPEPRESS))
    {
        guiManager.setDesktopProperty(std::string("#playButton"), std::string("BackgroundColor"), sf::Color(85, 87, 82, 220));
        guiManager.setDesktopProperty(std::string("#settingsButton"), std::string("BackgroundColor"), sf::Color(85, 87, 82, 220));
        guiManager.setDesktopProperty(std::string("#creditsButton"), std::string("BackgroundColor"), sf::Color(85, 87, 82, 220));
        guiManager.setDesktopProperty(std::string("#exitButton"), std::string("BackgroundColor"), sf::Color(85, 87, 82, 220));

        newGameButton->Show(false);
        loadGameButton->Show(false);
    }

    return true;
}

void IntroState::draw()
{
    sf::RenderWindow& window = *getContext().window;
}

void IntroState::playButtonClicked()
{
    auto& guiManager = *getContext().guiManager;

    guiManager.setDesktopProperty(std::string("#playButton"), std::string("BackgroundColor"), sf::Color(85, 87, 82, 150));
    guiManager.setDesktopProperty(std::string("#settingsButton"), std::string("BackgroundColor"), sf::Color(85, 87, 82, 150));
    guiManager.setDesktopProperty(std::string("#creditsButton"), std::string("BackgroundColor"), sf::Color(85, 87, 82, 150));
    guiManager.setDesktopProperty(std::string("#exitButton"), std::string("BackgroundColor"), sf::Color(85, 87, 82, 150));

    newGameButton->Show(true);
    loadGameButton->Show(true);
}

void IntroState::settingsButtonClicked()
{

}
