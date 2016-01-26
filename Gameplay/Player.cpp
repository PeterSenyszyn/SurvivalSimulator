#include "stdafx.h"
#include "Player.hpp"
#include "Application.hpp"

sf::Sprite Player::m_sprite;

Console Player::m_console(true);

Player::Player(sf::RenderWindow& context) :
	Entity(std::string("player")),
	m_windowContext(&context),
	m_walkSpeed(75.0f),
	m_sprintSpeed(140.0f),
	m_stamina(100.0f),
	m_health(100.f),
	m_thirst(100.f),
	m_encumbrance(0.f),
	m_requiredStaminaToSprint(20.0f),
	m_keepUpdatingCameraX(false),
	m_keepUpdatingCameraY(false),
	runCounter(0),
	m_baseStaminaDegen(9.0f),
	m_baseStaminaRegen(3.5f),
	m_isSprinting(false),
	m_isWalking(false),
	m_isCurrentlyMoving(false),
	m_examineMenu(*this),
	m_camera(sf::FloatRect({ adjustForResX(1500), adjustForResY(750) }, { adjustForResX(Application::getCurrentResolution().x), 
		adjustForResY(Application::getCurrentResolution().y)}), m_sprite)
{
	m_image.loadFromFile("Assets/Player/player_temp.png");
	m_image.createMaskFromColor(sf::Color::White);

	m_animationSteps.loadFromImage(m_image);

	m_sprite.setTexture(m_animationSteps);
	m_sprite.setScale(1920 / Application::getCurrentResolution().x, 1080 / Application::getCurrentResolution().y);

	m_sprite.setPosition(adjustForResX(1500), adjustForResY(750));
}

void Player::init()
{
	m_inventory.init();

	m_camera.getView().setCenter(m_sprite.getPosition());
}

void Player::addItem(ItemManager::Item::Ptr item)
{
	m_inventory.addItem(item);
}

void Player::handleEvents(const sf::Event& event)
{
	if (m_active)
	{
		m_inventory.handleEvents(event);
		m_examineMenu.handleEvents(event);
		m_console.handleEvents(event);
	}
}

bool Player::nextPosValid(const sf::Vector2f& offset, World& world)
{
	sf::Vector2f offsettedPos(m_sprite.getPosition().x + offset.x, m_sprite.getPosition().y + offset.y);

	//The bounding rectangle of the future player
	sf::FloatRect rect(offsettedPos, sf::Vector2f(m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height));

	if (!checkCollisions(rect, world))
		return false;

	return true;
}

bool Player::checkCollisions(sf::FloatRect& rect, World& world)
{
	if (world.getCurrentCell()->getTileMap().collidesWithType(2, rect) ||
		world.getCurrentCell()->getTileMap().collidesWithType(13, rect) ||
		world.getCurrentCell()->collidesWithContainer(rect))
		return false;

	return true;
}

void Player::update(sf::Time dt, thor::ActionMap<Keys::KeyboardInput>& keys, World& world)
{
	if (m_active)
	{
		updateMovement(dt, keys, world);
		updateInput(dt, keys, world);
		m_inventory.update(dt);
		m_inventory.updatePlayerInfo(m_health, m_thirst, m_encumbrance, m_stamina);
		m_examineMenu.update(dt, *this);
		m_camera.update(dt);
		m_console.update(dt);

		if (runCounter == 1)
			m_defaultCameraPos = sf::Vector2f(m_camera.getPlayerMappedCoords().x, m_camera.getPlayerMappedCoords().y);

		runCounter++;
	}
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_active)
		target.draw(m_sprite, states);
}

void Player::updateMovement(sf::Time dt, thor::ActionMap<Keys::KeyboardInput>& keys, World& world)
{
	if (keys.isActive(Keys::LSHIFTHOLD))
	{
		m_isSprinting = true;
		m_isWalking = false;
	}

	else
		m_isSprinting = false;

	//Check if the player is walking
	if (m_isCurrentlyMoving && !keys.isActive(Keys::LSHIFTHOLD))
		m_isWalking = true;

	//Check if any of the keys are down, so we know if the player is currently moving or nah
	if (!keys.isActive(Keys::WHOLD) && !keys.isActive(Keys::AHOLD) && !keys.isActive(Keys::SHOLD) && !keys.isActive(Keys::DHOLD))
	{
		m_isCurrentlyMoving = false;
		m_isWalking = false;
		m_isSprinting = false;
	}

	//Do all the stamina degen/regen calculations here
	if (m_isSprinting)
		m_stamina -= m_baseStaminaDegen * dt.asSeconds();

	else if (m_isWalking && m_stamina < 100.0f)
		m_stamina += m_baseStaminaRegen * dt.asSeconds();

	else if (!m_isCurrentlyMoving && m_stamina < 100.0f)
		m_stamina += m_baseStaminaRegen * 1.75 * dt.asSeconds();

	//If the stamina is ever above 100 for some reason, reset it back to 100
	if (m_stamina > 100.0f)
		m_stamina = 100.0f;

	//Camera center management
	if (m_camera.getPlayerMappedCoords().x != m_defaultCameraPos.x)
		m_keepUpdatingCameraX = false;

	else if (m_camera.getPlayerMappedCoords().x == m_defaultCameraPos.x)
		m_keepUpdatingCameraX = true;

	if (m_camera.getPlayerMappedCoords().y != m_defaultCameraPos.y)
		m_keepUpdatingCameraY = false;

	else if (m_camera.getPlayerMappedCoords().y == m_defaultCameraPos.y)
		m_keepUpdatingCameraY = true;

	if (keys.isActive(Keys::WHOLD) && nextPosValid(sf::Vector2f(0, -(m_sprintSpeed * dt.asSeconds())), world))
	{
		if (m_isSprinting && m_stamina >= m_requiredStaminaToSprint)
		{
			m_sprite.move(0, -(m_sprintSpeed * dt.asSeconds()));

			if (m_camera.topLeft.y > 0.f && m_keepUpdatingCameraY)
				m_camera.getView().move(sf::Vector2f(0, -(m_sprintSpeed * dt.asSeconds())));
		}

		else
		{
			m_sprite.move(0, -(m_walkSpeed * dt.asSeconds()));

			if (m_camera.topLeft.y > 0.f && m_keepUpdatingCameraY)
				m_camera.getView().move(sf::Vector2f(0, -(m_walkSpeed * dt.asSeconds())));
		}
	}

	if (keys.isActive(Keys::AHOLD) && nextPosValid(sf::Vector2f(-(m_sprintSpeed * dt.asSeconds()), 0), world))
	{
		if (m_isSprinting && m_stamina >= m_requiredStaminaToSprint)
		{
			m_sprite.move(-(m_sprintSpeed * dt.asSeconds()), 0);

			if (m_camera.topLeft.x > 0.f && m_keepUpdatingCameraX)
				m_camera.getView().move(sf::Vector2f(-(m_sprintSpeed * dt.asSeconds()), 0));
		}

		else
		{
			m_sprite.move(-(m_walkSpeed * dt.asSeconds()), 0);

			if (m_camera.topLeft.x > 0.f && m_keepUpdatingCameraX)
				m_camera.getView().move(sf::Vector2f(-(m_walkSpeed * dt.asSeconds()), 0));
		}

		m_isCurrentlyMoving = true;
	}

	if (keys.isActive(Keys::SHOLD) && nextPosValid(sf::Vector2f(0, m_sprintSpeed * dt.asSeconds()), world))
	{
		if (m_isSprinting && m_stamina >= m_requiredStaminaToSprint)
		{
			m_sprite.move(0, m_sprintSpeed * dt.asSeconds());

			if (m_camera.bottomRight.y <= TileMap::getSizeY() && m_keepUpdatingCameraY)
				m_camera.getView().move(sf::Vector2f(0, m_sprintSpeed * dt.asSeconds()));
		}

		else
		{
			m_sprite.move(0, m_walkSpeed * dt.asSeconds());

			if (m_camera.bottomRight.y <= TileMap::getSizeY() && m_keepUpdatingCameraY)
				m_camera.getView().move(0, m_walkSpeed * dt.asSeconds());
		}

		m_isCurrentlyMoving = true;
	}

	if (keys.isActive(Keys::DHOLD) && nextPosValid(sf::Vector2f(m_sprintSpeed * dt.asSeconds(), 0), world))
	{
		if (m_isSprinting && m_stamina >= m_requiredStaminaToSprint)
		{
			m_sprite.move(m_sprintSpeed * dt.asSeconds(), 0);

			if (m_camera.bottomRight.x <= TileMap::getSizeX() && m_keepUpdatingCameraX)
				m_camera.getView().move(sf::Vector2f(m_sprintSpeed * dt.asSeconds(), 0));
		}

		else
		{
			m_sprite.move(m_walkSpeed * dt.asSeconds(), 0);

			if (m_camera.bottomRight.x <= TileMap::getSizeX() && m_keepUpdatingCameraX)
				m_camera.getView().move(sf::Vector2f(m_walkSpeed * dt.asSeconds(), 0));
		}

		m_isCurrentlyMoving = true;
	}
}

void Player::updateInput(sf::Time dt, thor::ActionMap<Keys::KeyboardInput>& keys, World& world)
{
	if (keys.isActive(Keys::TABPRESS))
		m_inventory.setActive(!m_inventory.getActive());

	bool ignore = false;

	if (keys.isActive(Keys::RIGHTMOUSEPRESSED))
	{
		for (const auto& iter : world.getCurrentCell()->getWorldItems())
		{
			if (iter.second->getSprite().getGlobalBounds().contains(sf::Vector2f(Application::getWorldCoords().x, Application::getWorldCoords().y)))
			{
				m_itemRef = iter.second;
				m_itemRefId = iter.first;
				m_examineMenu.init(iter.second, this, world);
				ignore = true;
			}
		}

		if (!ignore)
		{
			m_entityRef = world.getCurrentCell()->getTileMap().getTileMouseOver(Application::getWorldCoords());

			if (m_entityRef != nullptr)
				m_examineMenu.init(m_entityRef, this);
		}
	}

	else if (keys.isActive(Keys::MPRESS))
		world.getCurrentCell()->addWorldContainer(StorageContainer::create(20, "Assets/topdown_tiles/chest_closed.png", "Assets/topdown_tiles/chest_open.png", sf::Vector2f(200, 1000), m_inventory));

	else if (keys.isActive(Keys::CPRESS))
		m_console.setActive(!m_console.getActive());
}

//Event implementation
void Player::onCollectPress(ActionManager& actionManager, Action::Ptr itemActionContext)
{
	if (m_entityRef != nullptr)
	{
		if (itemActionContext->actionName == "Harvest Wood" || itemActionContext->actionName == "Harvest Berries")
		{
			if (checkDistanceTileRef() < 90)
			{
				actionManager.getActionContext(itemActionContext->name)->actionClock.restart();

				actionManager.setActiveAction(itemActionContext->name);
			}
		}
	}
}

void Player::onPickupPress(World& world)
{
	if (m_itemRef != nullptr)
	{
		for (const auto& iter : world.getCurrentCell()->getWorldItems())
		{
			if (iter.second->getSprite().getGlobalBounds().contains(sf::Vector2f(Application::getMouseCoords().x, Application::getMouseCoords().y)))
			{
				int distanceX = (Application::getMouseCoords().x - (m_sprite.getPosition().x + (m_sprite.getGlobalBounds().width / 2)));
				int distanceY = (Application::getMouseCoords().y - (m_sprite.getPosition().y + (m_sprite.getGlobalBounds().height / 2)));

				if ((sqrt(distanceX * distanceX + distanceY * distanceY)) < 100)
				{
					m_examineMenu.getActionManager().getActionContext("pickup")->active = true;

					m_inventory.addItem(m_itemRef);

					world.getCurrentCell()->getWorldItems().erase(m_itemRefId);

					m_itemRef = nullptr;
				}
			}
		}
	}
}

int Player::checkDistanceTileRef()
{
	if (m_entityRef != nullptr)
	{
		int distanceX = (m_entityRef->pos.x - (m_sprite.getPosition().x + (m_sprite.getGlobalBounds().width / 2)));

		int distanceY = (m_entityRef->pos.y - (m_sprite.getPosition().y + (m_sprite.getGlobalBounds().height / 2)));

		return sqrt(distanceX * distanceX + distanceY * distanceY);
	}
}