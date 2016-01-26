#pragma once

#include <iostream>
#include <vector>
#include <cmath>

#include <SFML/Graphics.hpp>

#include <SFGUI/Desktop.hpp>
#include <SFGUI/Window.hpp>
#include <SFGUI/ScrolledWindow.hpp>
#include <SFGUI/Table.hpp>
#include <SFGUI/Box.hpp>
#include <SFGUI/Label.hpp>

class Console
{
public:
	Console(bool devMode);

	const bool getActive() const { return m_active; }
	const void setActive(const bool active) { m_active = active; m_window->Show(active); }

	void handleEvents(const sf::Event& event);
	void update(sf::Time dt);

	void sendMessage(const std::string& message);

private:
	sfg::Desktop m_desktop;
	std::shared_ptr<sf::Font> m_font;

	sfg::Window::Ptr m_window;

	sfg::ScrolledWindow::Ptr m_scrollMenu;

	sfg::Table::Ptr m_table;

	sfg::Box::Ptr m_consoleScrollBin;

	std::vector<std::string> m_messages;
	sfg::Label::Ptr m_guiMessage;
	//std::map<std::string, sfg::Label::Ptr> m_messageMap;

	bool m_active;
	bool m_devMode;
};
