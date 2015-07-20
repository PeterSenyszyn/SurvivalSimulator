#include "GameObject.hpp"

namespace SE
{
    bool GameObject::intersectsRadius(sf::RectangleShape rectangle)
    {
        double m_interactRadiusDistanceX = abs(m_interactRadius.getPosition().x - rectangle.getPosition().x);
        double m_interactRadiusDistanceY = abs(m_interactRadius.getPosition().y - rectangle.getPosition().y);

        if (m_interactRadiusDistanceX > (rectangle.getSize().x/2 + m_interactRadius.getRadius()))
                return false;

        if (m_interactRadiusDistanceY > (rectangle.getSize().y/2 + m_interactRadius.getRadius()))
                return false;

        if (m_interactRadiusDistanceX <= (rectangle.getSize().x/2))
                return true;

        if (m_interactRadiusDistanceY <= (rectangle.getSize().y/2))
                return true;

        double cornerDistance_sq = pow((m_interactRadiusDistanceX - rectangle.getSize().x/2), 2) + pow((m_interactRadiusDistanceY - rectangle.getSize().y/2),2);

        return (cornerDistance_sq <= pow((m_interactRadius.getRadius()),2));
    }
}
