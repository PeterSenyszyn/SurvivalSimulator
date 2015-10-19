#include "stdafx.h"
#include "Item.hpp"

Item::Item(Item_Dictionary itemId, const std::string& name, const std::string& groundTexturePath, const std::string& inventoryTexturePath, bool onGround, bool inInventory, bool stackable) :
	m_itemId(itemId),
	m_name(name),
	m_onGround(onGround),
	m_inInventory(inInventory),
	m_active(false),
	m_stackable(stackable)
{
	m_groundTexture.loadFromFile(groundTexturePath);

	m_inventoryImage.loadFromFile(inventoryTexturePath);

	m_inventoryTexture = sfg::Image::Create(m_inventoryImage);

	m_sprite.setTexture(m_groundTexture);
}

void Item::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_active)
		target.draw(m_sprite, states);
}
