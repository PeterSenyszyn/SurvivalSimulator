#include "System.hpp"

void System::addEntity(Entity::Ptr entity)
{
    if (std::find_if(m_entities.begin(), m_entities.end(), [&] (Entity::Ptr iter) { return entity->getID() == iter->getID(); }) != m_entities.end())
        throw std::runtime_error("Entity with ID: " + entity->getID() + " already exists in the system!");

    m_entities.push_back(entity);
}

void System::addController(Controller::Ptr controller)
{
    if (std::find_if(m_controllers.begin(), m_controllers.end(), [&] (Controller::Ptr iter) { return controller->getID() == iter->getID(); }) != m_controllers.end())
        throw std::runtime_error("Controller with ID: " + controller->getID() + " already exists in the system!");

    m_controllers.push_back(controller);
}

void System::removeEntity(const std::string& id)
{
    m_entities.remove_if([&] (Entity::Ptr iter) { return id == iter->getID(); });
}

void System::removeController(const std::string& id)
{
    m_controllers.remove_if([&] (Controller::Ptr iter) { return id == iter->getID(); });
}

void System::addControllerRequiredProperty(const std::string& controllerID, const std::string& requiredPropertyID)
{
    for (const auto& iter : m_controllers)
    {
        if (iter->getID() == controllerID)
            iter->requireProperty(requiredPropertyID);
    }
}

void System::removeControllerRequiredProperty(const std::string& controllerID, const std::string& requiredPropertyID)
{
    for (const auto& iter : m_controllers)
    {
        if (iter->getID() == controllerID)
            iter->removeProperty(requiredPropertyID);
    }
}

Entity::Ptr System::getEntity(const std::string& id)
{
    for (const auto& iter : m_entities)
    {
        if (iter->getID() == id)
            return iter;
    }

    throw std::runtime_error("Entity retrieval of id: " + id + " failed, it doesn't exist!");

    return nullptr;
}

Controller::Ptr System::getController(const std::string& id)
{
    for (const auto& iter : m_controllers)
    {
        if (iter->getID() == id)
            return iter;
    }

    throw std::runtime_error("Controller retrieval of id: " + id + " failed, it doesn't exist!");

    return nullptr;
}

void System::update(sf::Time dt)
{
    for (const auto& iter : m_controllers)
        iter->update(dt);

    for (const auto& iter : m_entities)
        iter->update(dt);
}

void System::drawEntities(sf::RenderWindow& window) const
{
    for (const auto& iter : m_entities)
        window.draw(*iter);
}
