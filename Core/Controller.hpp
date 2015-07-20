#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <list>

class Controller
{
public:
    virtual ~Controller() {};

    typedef std::shared_ptr<Controller> Ptr;

    const std::string& getID() const { return m_id; }

    virtual void update(sf::Time dt) {};

    void requireProperty(const std::string& id)
    {
        if (std::find_if(m_requiredProperties.begin(), m_requiredProperties.end(), [&] (const std::string& iter) { return id == iter; }) == m_requiredProperties.end())
            m_requiredProperties.push_back(id);
    }

    void removeProperty(const std::string& id)
    {
        m_requiredProperties.remove_if([&] (const std::string& iter) { return id == iter; });
    }

    std::list<std::string>& getRequiredProperties() { return m_requiredProperties; }

private:
    std::string m_id;

    std::list<std::string> m_requiredProperties;
};

#endif // CONTROLLER_H
