#pragma once

#include <list>
#include <typeindex>

#include "Label.hpp"
#include "EditBox.hpp"
#include "BackgroundManager.hpp"
#include "ButtonLabel.hpp"
#include "Menu.hpp"

namespace SE
{
	class GUI final
	{
	public:
	    template <class T> void pushWidget(std::shared_ptr<T> widget)
        {
            auto iter = findObject(widget->getId());

            if (iter != m_widgets.end())
                return;

            m_widgets.push_back(std::dynamic_pointer_cast<Widget>(widget));
        }

        Widget::Ptr findObjectWithId(const std::string& id)
        {
            for (const auto& iter : m_widgets)
            {
                if (iter->getId() == id)
                    return iter;
            }

            return nullptr;
        }

        Label::Ptr getLabel(const std::string& id) { auto iter = findObject(id); if (iter != m_widgets.end()) return std::dynamic_pointer_cast<Label>(*iter); return nullptr; }
        EditBox::Ptr getEditBox(const std::string& id) { auto iter = findObject(id); if (iter != m_widgets.end()) return std::dynamic_pointer_cast<EditBox>(*iter); return nullptr; }
        ButtonLabel::Ptr getButtonLabel(const std::string& id) { auto iter = findObject(id); if (iter != m_widgets.end()) return std::dynamic_pointer_cast<ButtonLabel>(*iter); return nullptr; }
        Menu::Ptr getMenu(const std::string& id) { auto iter = findObject(id); if (iter != m_widgets.end()) return std::dynamic_pointer_cast<Menu>(*iter); return nullptr;}

        void removeWidget(const std::string& id);

        const void clearEverything() { m_widgets.clear(); }

        const void setAllEnabled(bool enabled);

        void handleEvents(const sf::Event& evt);

		void update(sf::Time dt);

		void render(sf::RenderWindow& window);

	private:
	    std::list<Widget::Ptr> m_widgets;

        std::list<Widget::Ptr>::iterator findObject(const std::string& id)
        {
            for (auto iter = m_widgets.begin(); iter != m_widgets.end(); ++iter)
            {
                if ((*iter)->getId() == id)
                    return iter;
            }

            return m_widgets.end();
        }

		bool checkWidgetMenu(const std::string& menuAttachedId)
		{
		    for (const auto& iter : m_widgets)
            {
                if (iter->getWidgetType() == "Menu")
                {
                    if (iter->getId() == menuAttachedId)
                        return true;
                }
            }

            return false;
		}
	};
}
