#include "stdafx.h"
#include "Controller.hpp"

void Controller::requireProperty(const std::string& id)
{
	if (std::find_if(m_requiredProperties.begin(), m_requiredProperties.end(), [&](const std::string& iter) { return id == iter; }) == m_requiredProperties.end())
		m_requiredProperties.push_back(id);
}

void Controller::removeProperty(const std::string& id)
{
	m_requiredProperties.remove_if([&](const std::string& iter) { return id == iter; });
}
