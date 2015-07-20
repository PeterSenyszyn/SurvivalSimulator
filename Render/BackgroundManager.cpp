
#include "BackgroundManager.hpp"

namespace SE
{
	BackgroundManager::Background::Ptr
		BackgroundManager::createBackground(const std::string& filepath, const std::string& id)
	{
			Background::Ptr temp(new Background(filepath, id));

			return temp;
		}

	void BackgroundManager::pushBackground(BackgroundManager::Background::Ptr temp)
	{
		//Make sure the background doesn't already exist
		if (m_backgrounds.find(temp->m_id) != m_backgrounds.end())
			return;

		m_backgrounds[temp->m_id] = temp;
	}

	void BackgroundManager::enableBackground(const std::string& id)
	{
		if (m_backgrounds.find(id) == m_backgrounds.end())
			return;

		m_backgrounds[id]->m_visible = true;
	}

	void BackgroundManager::enableEverything()
	{
		for (const auto& iter : m_backgrounds)
			iter.second->m_visible = true;
	}

	void BackgroundManager::disableEverything()
	{
		for (const auto& iter : m_backgrounds)
			iter.second->m_visible = false;
	}

	void BackgroundManager::update(sf::Time dt)
	{

	}

	void BackgroundManager::render(sf::RenderWindow& window)
	{
		for (const auto& iter : m_backgrounds)
		{
			if (iter.second->m_visible)
				window.draw(*iter.second);
		}
	}
}
