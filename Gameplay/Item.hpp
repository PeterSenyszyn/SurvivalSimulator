#pragma once

#include <memory>

#include <SFML/Graphics.hpp>
#include <SFGUI/Image.hpp>

class Item : public sf::Drawable
{
public:
	typedef std::shared_ptr<Item> Ptr;

	enum class Item_Dictionary
	{
		//The int value is the corresponding weight
		UNKNOWN = -1,
		WOOD = 5,
		BERRY = 1,
	};

	Item(Item_Dictionary itemId, const std::string& name, const std::string& groundTexturePath, const std::string& inventoryTexturePath, bool onGround, bool inInventory, bool stackable);

	static Ptr create(Item_Dictionary itemId, const std::string& name, const std::string& groundTexturePath, const std::string& inventoryTexturePath, bool onGround, bool inInventory, bool stackable)
	{
		Ptr temp = Ptr(new Item(itemId, name, groundTexturePath, inventoryTexturePath, onGround, inInventory, stackable));

		temp->getInventoryTexture()->SetId(name);

		return temp;
	}

	void setActive(bool active) { m_active = active; }
	bool getActive() { return m_active; }

	void setOnGround(bool onGround) { m_onGround = onGround; }
	bool getOnGround() { return m_onGround; }

	void setInInventory(bool inInventory) { m_inInventory = inInventory; }
	bool getInInventory() { return m_inInventory; }

	const bool isStackable() const { return m_stackable; }

	const std::string& getName() { return m_name; }
	Item_Dictionary getItemId() { return m_itemId; }

	sf::Image& getInventoryImage() { return m_inventoryImage; }
	sfg::Image::Ptr getInventoryTexture() { return m_inventoryTexture; }
	sf::Sprite& getSprite() { return m_sprite; }

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	Item_Dictionary m_itemId;
	std::string m_name;

	sf::Texture m_groundTexture;

	sf::Image m_inventoryImage;
	sfg::Image::Ptr m_inventoryTexture;

	sf::Sprite m_sprite;

	bool m_onGround;
	bool m_inInventory;
	bool m_stackable;

	bool m_active;
};