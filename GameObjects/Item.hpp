#ifndef ITEM_H
#define ITEM_H

#include <memory>

#include <SFML/Graphics.hpp>

namespace SE
{
    class Item : public sf::Drawable
    {
    public:
        virtual ~Item() {};

        typedef std::shared_ptr<Item> Ptr;

    private:
        Item();

        std::string m_id;
    };
}

#endif // ITEM_H
