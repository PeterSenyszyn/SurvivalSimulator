#include <SettingsState.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>
#include <Application.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>

SettingsState::SettingsState(StateStack& stack, Context context) :
State(stack, context)
{
    setStateId(States::Settings);

    initGui();
}

void SettingsState::initGui()
{
    auto& guiManager = *getContext().guiManager;

    auto tempMainWindow = guiManager.createWindow(States::Settings, "mainWindow", sfg::Window::Style::NO_STYLE);
    tempMainWindow->SetPosition(sf::Vector2f(adjustForResX(0), adjustForResY(200)));

    auto generalBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, adjustForResX(40.f));
    generalBox->SetId("generalBox");

    auto resolutionPromptLabel = sfg::Label::Create("Resolution");
    resolutionPromptLabel->SetId("resolutionPromptLabel");
    guiManager.setDesktopProperty(std::string("#resolutionPromptLabel"), std::string("FontSize"), adjustForResX(30.f));

    m_resolutionComboBox = sfg::ComboBox::Create();
    m_resolutionComboBox->SetId("resolutionComboBox");
    guiManager.setDesktopProperty(std::string("#resolutionComboBox"), std::string("FontSize"), adjustForResX(30.f));

    m_resolutionComboBox->AppendItem("1024 x 768");
    m_resolutionComboBox->AppendItem("1280 x 1024");
    m_resolutionComboBox->AppendItem("1600 x 900");
    m_resolutionComboBox->AppendItem("1680 x 1050");
    m_resolutionComboBox->AppendItem("1920 x 1080");

    auto refreshRateLabel = sfg::Label::Create("Max Refresh Rate");
    refreshRateLabel->SetId("refreshRateLabel");
    guiManager.setDesktopProperty(std::string("#refreshRateLabel"), std::string("FontSize"), adjustForResX(20.f));

    m_maxRefreshRate = sfg::ComboBox::Create();
    m_maxRefreshRate->SetId("maxRefreshRateComboBox");
    guiManager.setDesktopProperty(std::string("#maxRefreshRateComboBox"), std::string("FontSize"), adjustForResX(20.f));

    m_maxRefreshRate->AppendItem("30 FPS");
    m_maxRefreshRate->AppendItem("60 FPS");
    m_maxRefreshRate->AppendItem("120 FPS");
    m_maxRefreshRate->AppendItem("144 FPS");
    m_maxRefreshRate->AppendItem("300 FPS");

    m_saveButton = sfg::Button::Create("Save Settings");
    m_saveButton->SetRequisition(sf::Vector2f(adjustForResX(200), adjustForResY(100)));
    m_saveButton->GetSignal(sfg::Button::OnLeftClick).Connect([&] { updateSettings(); } );
    m_saveButton->SetId("saveButton");

    generalBox->Pack(resolutionPromptLabel);
    generalBox->Pack(m_resolutionComboBox);
    generalBox->Pack(refreshRateLabel);
    generalBox->Pack(m_maxRefreshRate);
    generalBox->Pack(m_saveButton);

    auto notebook = sfg::Notebook::Create();
    notebook->SetRequisition(sf::Vector2f(adjustForResX(500), adjustForResY(75)));

    notebook->AppendPage(generalBox, sfg::Label::Create("General Settings"));
    notebook->AppendPage(sfg::Label::Create("Testajs;ldjasd"), sfg::Label::Create("Graphics Settings"));

    tempMainWindow->Add(notebook);
    centerWindowX(tempMainWindow);

    int posRes = 0;
    //m_sceneManager.getSettingsParser().get("posRes", posRes);
    m_resolutionComboBox->SelectItem(posRes);

    int posRefresh = 0;
    //m_sceneManager.getSettingsParser().get("posRefresh", posRefresh);
    m_maxRefreshRate->SelectItem(posRefresh);
}

bool SettingsState::update(sf::Time dt)
{
    return true;
}

bool SettingsState::handleEvent(const sf::Event& event)
{
    if (getContext().keyboardMap->isActive(Keys::ESCAPEPRESS))
        requestStackPush(States::Intro);

    return true;
}

void SettingsState::draw()
{
    sf::RenderWindow& window = *getContext().window;
}

void SettingsState::updateSettings()
{
    sf::Vector2u res = parseResolution(m_resolutionComboBox->GetSelectedText());
    int x = res.x, y = res.y;
    //float fps = parseFps(m_maxRefreshRate->GetSelectedText().toAnsiString());

    //int refreshSelectedItem = m_maxRefreshRate->GetSelectedItem();

    if (res.x != 0.f && res.y != 0.f)
    {
        getContext().window->setSize(res);
        getContext().parser->set("width", x);
        getContext().parser->set("height", y);

        Application::setCurrentResolution(res);
        Application::setResized(true);

        requestGuiScale();

        //requestStackPush(States::Intro);
    }

    /*if (fps > 0.f && fps <= 300.f)
    {
        m_sceneManager.getSettingsParser().set("refreshrate", fps);
        m_sceneManager.getSettingsParser().set("posRefresh", refreshSelectedItem);

        Engine::setMaxFps(fps);
    }*/

    //getContext().parser->saveToFile();
}
