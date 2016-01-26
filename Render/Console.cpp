#include "stdafx.h"
#include "Console.hpp"
#include "Application.hpp"

Console::Console(bool devMode) : 
m_devMode(devMode)
{
	m_font = std::make_shared<sf::Font>();
	m_font->loadFromFile("Assets/font.ttf");

	m_desktop.GetEngine().GetResourceManager().SetDefaultFont(m_font);
	m_desktop.SetProperty("*", "FontName", "Assets/font.ttf");

	m_window = sfg::Window::Create();
	m_window->SetTitle("Console");
	m_window->SetStyle(sfg::Window::Style::TITLEBAR | sfg::Window::Style::BACKGROUND);
	m_window->SetId("consolemenu");

	m_scrollMenu = sfg::ScrolledWindow::Create();
	m_scrollMenu->SetScrollbarPolicy(sfg::ScrolledWindow::HORIZONTAL_NEVER | sfg::ScrolledWindow::VERTICAL_AUTOMATIC);
	m_scrollMenu->SetRequisition(sf::Vector2f(adjustForResX(325), adjustForResY(325)));
	m_scrollMenu->SetId("consolescroll");

	m_table = sfg::Table::Create();
	m_table->SetRowSpacings(adjustForResX(5.f));
	m_table->SetColumnSpacings(adjustForResY(5.f));
	m_table->SetRequisition(sf::Vector2f(adjustForResX(325), adjustForResY(325)));

	sfg::Context::Get().GetEngine().SetProperty(std::string("#consolemenu"), std::string("BackgroundColor"), sf::Color(85, 87, 82, 200));
	sfg::Context::Get().GetEngine().SetProperty(std::string("#consolemenu"), std::string("TitleBackgroundColor"), sf::Color(90, 106, 80, 220));

	sfg::Context::Get().GetEngine().SetProperty(std::string("#consolescroll"), std::string("BackgroundColor"), sf::Color(85, 87, 82, 200));
	sfg::Context::Get().GetEngine().SetProperty(std::string("#consolescroll"), std::string("TitleBackgroundColor"), sf::Color(90, 106, 80, 220));

	m_consoleScrollBin = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
	m_consoleScrollBin->Pack(m_table);
	m_consoleScrollBin->SetId("consolebin");

	sfg::Context::Get().GetEngine().SetProperty(std::string("#consolebin"), std::string("BackgroundColor"), sf::Color(85, 87, 82, 200));
	sfg::Context::Get().GetEngine().SetProperty(std::string("#consolebin"), std::string("TitleBackgroundColor"), sf::Color(90, 106, 80, 220));

	m_guiMessage = sfg::Label::Create("");
	m_guiMessage->SetId("guiMessageLabel");
	sfg::Context::Get().GetEngine().SetProperty("#guiMessageLabel", std::string("FontSize"), adjustForResX(16.f));

	m_table->Attach(m_guiMessage, sf::Rect<sf::Uint32>(0, 0, 1, 1), sfg::Table::FILL, sfg::Table::FILL, sf::Vector2f(10.f, 10.f));

	m_scrollMenu->AddWithViewport(m_consoleScrollBin);

	m_window->Add(m_scrollMenu);

	m_desktop.Add(m_window);

	setActive(false);
}

void Console::update(sf::Time dt)
{
	m_desktop.Update(dt.asSeconds());
}

void Console::handleEvents(const sf::Event& event)
{
	m_desktop.HandleEvent(event);
}

void Console::sendMessage(const std::string& message)
{
	std::string formattedMessage = message;

	formattedMessage.insert(0, "[Game] ");

	int numCharsBeforeSpace = 39;
	int timeSinceLastSpace = 0;

	for (int i = 0; i < formattedMessage.size(); i++)
	{
		if (timeSinceLastSpace == numCharsBeforeSpace)
		{
			formattedMessage.insert(i, "\n");

			timeSinceLastSpace = -1;
		}

		timeSinceLastSpace++;
	}

	formattedMessage += "\n";

	m_guiMessage->SetText(m_guiMessage->GetText() + formattedMessage);
}