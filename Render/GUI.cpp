#include "GUI.hpp"

namespace SE
{
    void GUI::removeWidget(const std::string& id)
    {
        auto iter = findObject(id);

        if (iter != m_widgets.end())
            m_widgets.erase(iter);

        /*for (auto iter = m_widgets.begin(); iter != m_widgets.end(); ++iter)
        {
            if ((*iter)->getId() == id)
                m_widgets.erase(iter++);
        }*/
    }

	const void GUI::setAllEnabled(bool enabled)
	{
	    for (const auto& iter : m_widgets)
            iter->setVisible(enabled);
	}

	void GUI::handleEvents(const sf::Event& evt)
	{
		for (const auto& iter : m_widgets)
			iter->handleEvents(evt);
	}

	void GUI::update(sf::Time dt)
	{
		for (const auto& iter : m_widgets)
			iter->update(dt);
	}

	void GUI::render(sf::RenderWindow& window)
	{
        for (const auto& iter : m_widgets)
        {
            if (iter->getWidgetType() == "Menu")
                window.draw(*iter);

            else
            {
                if (iter->getAttachedToMenu())
                {
                    if (checkWidgetMenu(iter->getMenuAttachedId()))
                        window.draw(*iter);
                }

                else
                    window.draw(*iter);
            }
        }
	}
}
