
#include "Player.hpp"
#include "Engine.hpp"
#include "TileMap.hpp"

namespace SE
{
	Player::Player(const std::string& id, bool active) :
		m_viewArea(sf::Vector2f(100, 100))
	{
		m_texture.loadFromFile("Resources/player.png");
		m_sprite.setTexture(m_texture);
		m_sprite.setPosition(350, 300);

		registerAttribute("renderable", new bool(true));
		registerAttribute("health", new int(20));

		SceneManager::getView().setCenter(m_sprite.getPosition());
		SceneManager::getView().setSize(m_viewArea);
	}

	bool Player::nextPosValid(const sf::Vector2f& offset)
	{
		sf::Vector2f offsettedPos(m_sprite.getPosition().x + offset.x, m_sprite.getPosition().y + offset.y);

		//The bounding rectangle of the future player
		sf::FloatRect rect(offsettedPos, sf::Vector2f(m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height));

		if (SceneManager::getWorld().getCurrentCell()->getTileMap().collidesWithType(2, rect))
            return false;

		return true;
	}

	void Player::move(const sf::Vector2f& offset)
	{
		m_sprite.move(offset);
		SceneManager::getView().setCenter(sf::Vector2f( std::floor(m_sprite.getPosition().x), std::floor(m_sprite.getPosition().y) ) );
		//SceneManager::getView().setCenter(m_sprite.getPosition());
	}

	void Player::update(sf::Time dt)
	{
		if (InputManager::isActive(User_Input::UPHOLD))
		{
			if (nextPosValid(sf::Vector2f(0, -100 * dt.asSeconds())))
				move(sf::Vector2f(0, -100 * dt.asSeconds()));
		}

		if (InputManager::isActive(User_Input::LEFTHOLD))
		{
			if (nextPosValid(sf::Vector2f(-100 * dt.asSeconds(), 0)))
				move(sf::Vector2f(-100 * dt.asSeconds(), 0));
		}

		if (InputManager::isActive(User_Input::DOWNHOLD))
		{
			if (nextPosValid(sf::Vector2f(0, 100 * dt.asSeconds())))
				move(sf::Vector2f(0, 100 * dt.asSeconds()));
		}

		if (InputManager::isActive(User_Input::RIGHTHOLD))
		{
			if (nextPosValid(sf::Vector2f(100 * dt.asSeconds(), 0)))
				move(sf::Vector2f(100 * dt.asSeconds(), 0));
		}

		if (InputManager::isActive(User_Input::PPRESS))
		{
			getAttribute<int>("health") -= 5;

			std::cout << "Player health is now: " << getAttribute<int>("health") << std::endl;
		}

		if (InputManager::isActive(User_Input::VHOLD))
		{
			if (SceneManager::getView().getSize().x < 300 ||
				SceneManager::getView().getSize().y < 300)
				SceneManager::getView().setSize(sf::Vector2f(SceneManager::getView().getSize().x + 0.5, SceneManager::getView().getSize().y + 0.5));
		}

		else if (InputManager::isActive(User_Input::IHOLD))
		{
			if (SceneManager::getView().getSize().x >= 100 ||
				SceneManager::getView().getSize().y >= 100)
				SceneManager::getView().setSize(sf::Vector2f(SceneManager::getView().getSize().x - 0.5, SceneManager::getView().getSize().y - 0.5));
		}

		if (getAttribute<int>("health") <= 0)
			setAttribute("renderable", new bool(false));

		setPosition(m_sprite.getPosition());
		setBounds(m_sprite.getGlobalBounds());
	}

	void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_sprite, states);
	}
}
