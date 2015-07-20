
#include "InputManager.hpp"
#include "Engine.hpp"
#include "SceneManager.hpp"

namespace SE
{
	thor::ActionMap<User_Input> InputManager::m_user_map;

	InputManager::InputManager() :
		m_activatedKeys(false) {};

	void InputManager::initKeys()
	{
		/*********************************************************************************************
		*****************************************PRESS***********************************************/

		//Alphabet (press)
		m_user_map[User_Input::APRESS] = thor::Action(sf::Keyboard::A, thor::Action::PressOnce);
		m_user_map[User_Input::BPRESS] = thor::Action(sf::Keyboard::B, thor::Action::PressOnce);
		m_user_map[User_Input::CPRESS] = thor::Action(sf::Keyboard::C, thor::Action::PressOnce);
		m_user_map[User_Input::DPRESS] = thor::Action(sf::Keyboard::D, thor::Action::PressOnce);
		m_user_map[User_Input::EPRESS] = thor::Action(sf::Keyboard::E, thor::Action::PressOnce);
		m_user_map[User_Input::FPRESS] = thor::Action(sf::Keyboard::F, thor::Action::PressOnce);
		m_user_map[User_Input::GPRESS] = thor::Action(sf::Keyboard::G, thor::Action::PressOnce);
		m_user_map[User_Input::HPRESS] = thor::Action(sf::Keyboard::H, thor::Action::PressOnce);
		m_user_map[User_Input::IPRESS] = thor::Action(sf::Keyboard::I, thor::Action::PressOnce);
		m_user_map[User_Input::JPRESS] = thor::Action(sf::Keyboard::J, thor::Action::PressOnce);
		m_user_map[User_Input::KPRESS] = thor::Action(sf::Keyboard::K, thor::Action::PressOnce);
		m_user_map[User_Input::LPRESS] = thor::Action(sf::Keyboard::L, thor::Action::PressOnce);
		m_user_map[User_Input::MPRESS] = thor::Action(sf::Keyboard::M, thor::Action::PressOnce);
		m_user_map[User_Input::NPRESS] = thor::Action(sf::Keyboard::N, thor::Action::PressOnce);
		m_user_map[User_Input::OPRESS] = thor::Action(sf::Keyboard::O, thor::Action::PressOnce);
		m_user_map[User_Input::PPRESS] = thor::Action(sf::Keyboard::P, thor::Action::PressOnce);
		m_user_map[User_Input::QPRESS] = thor::Action(sf::Keyboard::Q, thor::Action::PressOnce);
		m_user_map[User_Input::RPRESS] = thor::Action(sf::Keyboard::R, thor::Action::PressOnce);
		m_user_map[User_Input::SPRESS] = thor::Action(sf::Keyboard::S, thor::Action::PressOnce);
		m_user_map[User_Input::TPRESS] = thor::Action(sf::Keyboard::T, thor::Action::PressOnce);
		m_user_map[User_Input::UPRESS] = thor::Action(sf::Keyboard::U, thor::Action::PressOnce);
		m_user_map[User_Input::VPRESS] = thor::Action(sf::Keyboard::V, thor::Action::PressOnce);
		m_user_map[User_Input::WPRESS] = thor::Action(sf::Keyboard::W, thor::Action::PressOnce);
		m_user_map[User_Input::XPRESS] = thor::Action(sf::Keyboard::X, thor::Action::PressOnce);
		m_user_map[User_Input::YPRESS] = thor::Action(sf::Keyboard::Y, thor::Action::PressOnce);
		m_user_map[User_Input::ZPRESS] = thor::Action(sf::Keyboard::Z, thor::Action::PressOnce);

		//Numbers (press)
		m_user_map[User_Input::NUM0PRESS] = thor::Action(sf::Keyboard::Num0, thor::Action::PressOnce);
		m_user_map[User_Input::NUM1PRESS] = thor::Action(sf::Keyboard::Num1, thor::Action::PressOnce);
		m_user_map[User_Input::NUM2PRESS] = thor::Action(sf::Keyboard::Num2, thor::Action::PressOnce);
		m_user_map[User_Input::NUM3PRESS] = thor::Action(sf::Keyboard::Num3, thor::Action::PressOnce);
		m_user_map[User_Input::NUM4PRESS] = thor::Action(sf::Keyboard::Num4, thor::Action::PressOnce);
		m_user_map[User_Input::NUM5PRESS] = thor::Action(sf::Keyboard::Num5, thor::Action::PressOnce);
		m_user_map[User_Input::NUM6PRESS] = thor::Action(sf::Keyboard::Num6, thor::Action::PressOnce);
		m_user_map[User_Input::NUM7PRESS] = thor::Action(sf::Keyboard::Num7, thor::Action::PressOnce);
		m_user_map[User_Input::NUM8PRESS] = thor::Action(sf::Keyboard::Num8, thor::Action::PressOnce);
		m_user_map[User_Input::NUM9PRESS] = thor::Action(sf::Keyboard::Num9, thor::Action::PressOnce);

		//Other function keys (press)
		m_user_map[User_Input::ESCAPEPRESS] = thor::Action(sf::Keyboard::Escape, thor::Action::PressOnce);
		m_user_map[User_Input::LCONTROLPRESS] = thor::Action(sf::Keyboard::LControl, thor::Action::PressOnce);
		m_user_map[User_Input::LSHIFTPRESS] = thor::Action(sf::Keyboard::LShift, thor::Action::PressOnce);
		m_user_map[User_Input::LALTPRESS] = thor::Action(sf::Keyboard::LAlt, thor::Action::PressOnce);
		m_user_map[User_Input::LSYSTEMPRESS] = thor::Action(sf::Keyboard::LSystem, thor::Action::PressOnce);
		m_user_map[User_Input::RCONTROLPRESS] = thor::Action(sf::Keyboard::RControl, thor::Action::PressOnce);
		m_user_map[User_Input::RSHIFTPRESS] = thor::Action(sf::Keyboard::RShift, thor::Action::PressOnce);
		m_user_map[User_Input::RSYSTEMPRESS] = thor::Action(sf::Keyboard::RSystem, thor::Action::PressOnce);
		m_user_map[User_Input::MENUPRESS] = thor::Action(sf::Keyboard::Menu, thor::Action::PressOnce);
		m_user_map[User_Input::LBRACKETPRESS] = thor::Action(sf::Keyboard::LBracket, thor::Action::PressOnce);
		m_user_map[User_Input::RBRACKETPRESS] = thor::Action(sf::Keyboard::RBracket, thor::Action::PressOnce);
		m_user_map[User_Input::SEMICOLONPRESS] = thor::Action(sf::Keyboard::SemiColon, thor::Action::PressOnce);
		m_user_map[User_Input::COMMAPRESS] = thor::Action(sf::Keyboard::Comma, thor::Action::PressOnce);
		m_user_map[User_Input::PERIODPRESS] = thor::Action(sf::Keyboard::Period, thor::Action::PressOnce);
		m_user_map[User_Input::QUOTEPRESS] = thor::Action(sf::Keyboard::Quote, thor::Action::PressOnce);
		m_user_map[User_Input::SLASHPRESS] = thor::Action(sf::Keyboard::Slash, thor::Action::PressOnce);
		m_user_map[User_Input::BACKSLASHPRESS] = thor::Action(sf::Keyboard::BackSlash, thor::Action::PressOnce);
		m_user_map[User_Input::TILDEPRESS] = thor::Action(sf::Keyboard::Tilde, thor::Action::PressOnce);
		m_user_map[User_Input::EQUALPRESS] = thor::Action(sf::Keyboard::Equal, thor::Action::PressOnce);
		m_user_map[User_Input::DASHPRESS] = thor::Action(sf::Keyboard::Dash, thor::Action::PressOnce);
		m_user_map[User_Input::SPACEPRESS] = thor::Action(sf::Keyboard::Space, thor::Action::PressOnce);
		m_user_map[User_Input::RETURNPRESS] = thor::Action(sf::Keyboard::Return, thor::Action::PressOnce);
		m_user_map[User_Input::BACKSPACEPRESS] = thor::Action(sf::Keyboard::BackSpace, thor::Action::PressOnce);
		m_user_map[User_Input::TABPRESS] = thor::Action(sf::Keyboard::Tab, thor::Action::PressOnce);
		m_user_map[User_Input::PAGEUPPRESS] = thor::Action(sf::Keyboard::PageUp, thor::Action::PressOnce);
		m_user_map[User_Input::PAGEDOWNPRESS] = thor::Action(sf::Keyboard::PageDown, thor::Action::PressOnce);
		m_user_map[User_Input::ENDPRESS] = thor::Action(sf::Keyboard::End, thor::Action::PressOnce);
		m_user_map[User_Input::HOMEPRESS] = thor::Action(sf::Keyboard::Home, thor::Action::PressOnce);
		m_user_map[User_Input::INSERTPRESS] = thor::Action(sf::Keyboard::Insert, thor::Action::PressOnce);
		m_user_map[User_Input::DELETEPRESS] = thor::Action(sf::Keyboard::Delete, thor::Action::PressOnce);
		m_user_map[User_Input::ADDPRESS] = thor::Action(sf::Keyboard::Add, thor::Action::PressOnce);
		m_user_map[User_Input::SUBTRACTPRESS] = thor::Action(sf::Keyboard::Subtract, thor::Action::PressOnce);
		m_user_map[User_Input::MULTIPLYPRESS] = thor::Action(sf::Keyboard::Multiply, thor::Action::PressOnce);
		m_user_map[User_Input::DIVIDEPRESS] = thor::Action(sf::Keyboard::Divide, thor::Action::PressOnce);
		m_user_map[User_Input::LEFTPRESS] = thor::Action(sf::Keyboard::Left, thor::Action::PressOnce);
		m_user_map[User_Input::RIGHTPRESS] = thor::Action(sf::Keyboard::Right, thor::Action::PressOnce);
		m_user_map[User_Input::UPPRESS] = thor::Action(sf::Keyboard::Up, thor::Action::PressOnce);
		m_user_map[User_Input::DOWNPRESS] = thor::Action(sf::Keyboard::Down, thor::Action::PressOnce);
		m_user_map[User_Input::PAUSEPRESS] = thor::Action(sf::Keyboard::Pause, thor::Action::PressOnce);

		//Numpad (press)
		m_user_map[User_Input::NUMPAD0PRESS] = thor::Action(sf::Keyboard::Numpad0, thor::Action::PressOnce);
		m_user_map[User_Input::NUMPAD1PRESS] = thor::Action(sf::Keyboard::Numpad1, thor::Action::PressOnce);
		m_user_map[User_Input::NUMPAD2PRESS] = thor::Action(sf::Keyboard::Numpad2, thor::Action::PressOnce);
		m_user_map[User_Input::NUMPAD3PRESS] = thor::Action(sf::Keyboard::Numpad3, thor::Action::PressOnce);
		m_user_map[User_Input::NUMPAD4PRESS] = thor::Action(sf::Keyboard::Numpad4, thor::Action::PressOnce);
		m_user_map[User_Input::NUMPAD5PRESS] = thor::Action(sf::Keyboard::Numpad5, thor::Action::PressOnce);
		m_user_map[User_Input::NUMPAD6PRESS] = thor::Action(sf::Keyboard::Numpad6, thor::Action::PressOnce);
		m_user_map[User_Input::NUMPAD7PRESS] = thor::Action(sf::Keyboard::Numpad7, thor::Action::PressOnce);
		m_user_map[User_Input::NUMPAD8PRESS] = thor::Action(sf::Keyboard::Numpad8, thor::Action::PressOnce);
		m_user_map[User_Input::NUMPAD9PRESS] = thor::Action(sf::Keyboard::Numpad9, thor::Action::PressOnce);

		//Function keys (press)
		m_user_map[User_Input::F1PRESS] = thor::Action(sf::Keyboard::F1, thor::Action::PressOnce);
		m_user_map[User_Input::F2PRESS] = thor::Action(sf::Keyboard::F2, thor::Action::PressOnce);
		m_user_map[User_Input::F3PRESS] = thor::Action(sf::Keyboard::F3, thor::Action::PressOnce);
		m_user_map[User_Input::F4PRESS] = thor::Action(sf::Keyboard::F4, thor::Action::PressOnce);
		m_user_map[User_Input::F5PRESS] = thor::Action(sf::Keyboard::F5, thor::Action::PressOnce);
		m_user_map[User_Input::F6PRESS] = thor::Action(sf::Keyboard::F6, thor::Action::PressOnce);
		m_user_map[User_Input::F7PRESS] = thor::Action(sf::Keyboard::F7, thor::Action::PressOnce);
		m_user_map[User_Input::F8PRESS] = thor::Action(sf::Keyboard::F8, thor::Action::PressOnce);
		m_user_map[User_Input::F9PRESS] = thor::Action(sf::Keyboard::F9, thor::Action::PressOnce);
		m_user_map[User_Input::F10PRESS] = thor::Action(sf::Keyboard::F10, thor::Action::PressOnce);
		m_user_map[User_Input::F11PRESS] = thor::Action(sf::Keyboard::F11, thor::Action::PressOnce);
		m_user_map[User_Input::F12PRESS] = thor::Action(sf::Keyboard::F12, thor::Action::PressOnce);
		m_user_map[User_Input::F13PRESS] = thor::Action(sf::Keyboard::F13, thor::Action::PressOnce);
		m_user_map[User_Input::F14PRESS] = thor::Action(sf::Keyboard::F14, thor::Action::PressOnce);
		m_user_map[User_Input::F15PRESS] = thor::Action(sf::Keyboard::F15, thor::Action::PressOnce);


		/*********************************************************************************************
		*****************************************HOLD************************************************/


		//Alphabet (hold)
		m_user_map[User_Input::AHOLD] = thor::Action(sf::Keyboard::A, thor::Action::Hold);
		m_user_map[User_Input::BHOLD] = thor::Action(sf::Keyboard::B, thor::Action::Hold);
		m_user_map[User_Input::CHOLD] = thor::Action(sf::Keyboard::C, thor::Action::Hold);
		m_user_map[User_Input::DHOLD] = thor::Action(sf::Keyboard::D, thor::Action::Hold);
		m_user_map[User_Input::EHOLD] = thor::Action(sf::Keyboard::E, thor::Action::Hold);
		m_user_map[User_Input::FHOLD] = thor::Action(sf::Keyboard::F, thor::Action::Hold);
		m_user_map[User_Input::GHOLD] = thor::Action(sf::Keyboard::G, thor::Action::Hold);
		m_user_map[User_Input::HHOLD] = thor::Action(sf::Keyboard::H, thor::Action::Hold);
		m_user_map[User_Input::IHOLD] = thor::Action(sf::Keyboard::I, thor::Action::Hold);
		m_user_map[User_Input::JHOLD] = thor::Action(sf::Keyboard::J, thor::Action::Hold);
		m_user_map[User_Input::KHOLD] = thor::Action(sf::Keyboard::K, thor::Action::Hold);
		m_user_map[User_Input::LHOLD] = thor::Action(sf::Keyboard::L, thor::Action::Hold);
		m_user_map[User_Input::MHOLD] = thor::Action(sf::Keyboard::M, thor::Action::Hold);
		m_user_map[User_Input::NHOLD] = thor::Action(sf::Keyboard::N, thor::Action::Hold);
		m_user_map[User_Input::OHOLD] = thor::Action(sf::Keyboard::O, thor::Action::Hold);
		m_user_map[User_Input::PHOLD] = thor::Action(sf::Keyboard::P, thor::Action::Hold);
		m_user_map[User_Input::QHOLD] = thor::Action(sf::Keyboard::Q, thor::Action::Hold);
		m_user_map[User_Input::RHOLD] = thor::Action(sf::Keyboard::R, thor::Action::Hold);
		m_user_map[User_Input::SHOLD] = thor::Action(sf::Keyboard::S, thor::Action::Hold);
		m_user_map[User_Input::THOLD] = thor::Action(sf::Keyboard::T, thor::Action::Hold);
		m_user_map[User_Input::UHOLD] = thor::Action(sf::Keyboard::U, thor::Action::Hold);
		m_user_map[User_Input::VHOLD] = thor::Action(sf::Keyboard::V, thor::Action::Hold);
		m_user_map[User_Input::WHOLD] = thor::Action(sf::Keyboard::W, thor::Action::Hold);
		m_user_map[User_Input::XHOLD] = thor::Action(sf::Keyboard::X, thor::Action::Hold);
		m_user_map[User_Input::YHOLD] = thor::Action(sf::Keyboard::Y, thor::Action::Hold);
		m_user_map[User_Input::ZHOLD] = thor::Action(sf::Keyboard::Z, thor::Action::Hold);

		//Numbers (hold)
		m_user_map[User_Input::NUM0HOLD] = thor::Action(sf::Keyboard::Num0, thor::Action::Hold);
		m_user_map[User_Input::NUM1HOLD] = thor::Action(sf::Keyboard::Num1, thor::Action::Hold);
		m_user_map[User_Input::NUM2HOLD] = thor::Action(sf::Keyboard::Num2, thor::Action::Hold);
		m_user_map[User_Input::NUM3HOLD] = thor::Action(sf::Keyboard::Num3, thor::Action::Hold);
		m_user_map[User_Input::NUM4HOLD] = thor::Action(sf::Keyboard::Num4, thor::Action::Hold);
		m_user_map[User_Input::NUM5HOLD] = thor::Action(sf::Keyboard::Num5, thor::Action::Hold);
		m_user_map[User_Input::NUM6HOLD] = thor::Action(sf::Keyboard::Num6, thor::Action::Hold);
		m_user_map[User_Input::NUM7HOLD] = thor::Action(sf::Keyboard::Num7, thor::Action::Hold);
		m_user_map[User_Input::NUM8HOLD] = thor::Action(sf::Keyboard::Num8, thor::Action::Hold);
		m_user_map[User_Input::NUM9HOLD] = thor::Action(sf::Keyboard::Num9, thor::Action::Hold);

		//Other function keys (hold)
		m_user_map[User_Input::ESCAPEHOLD] = thor::Action(sf::Keyboard::Escape, thor::Action::Hold);
		m_user_map[User_Input::LCONTROLHOLD] = thor::Action(sf::Keyboard::LControl, thor::Action::Hold);
		m_user_map[User_Input::LSHIFTHOLD] = thor::Action(sf::Keyboard::LShift, thor::Action::Hold);
		m_user_map[User_Input::LALTHOLD] = thor::Action(sf::Keyboard::LAlt, thor::Action::Hold);
		m_user_map[User_Input::LSYSTEMHOLD] = thor::Action(sf::Keyboard::LSystem, thor::Action::Hold);
		m_user_map[User_Input::RCONTROLHOLD] = thor::Action(sf::Keyboard::RControl, thor::Action::Hold);
		m_user_map[User_Input::RSHIFTHOLD] = thor::Action(sf::Keyboard::RShift, thor::Action::Hold);
		m_user_map[User_Input::RSYSTEMHOLD] = thor::Action(sf::Keyboard::RSystem, thor::Action::Hold);
		m_user_map[User_Input::MENUHOLD] = thor::Action(sf::Keyboard::Menu, thor::Action::Hold);
		m_user_map[User_Input::LBRACKETHOLD] = thor::Action(sf::Keyboard::LBracket, thor::Action::Hold);
		m_user_map[User_Input::RBRACKETHOLD] = thor::Action(sf::Keyboard::RBracket, thor::Action::Hold);
		m_user_map[User_Input::SEMICOLONHOLD] = thor::Action(sf::Keyboard::SemiColon, thor::Action::Hold);
		m_user_map[User_Input::COMMAHOLD] = thor::Action(sf::Keyboard::Comma, thor::Action::Hold);
		m_user_map[User_Input::PERIODHOLD] = thor::Action(sf::Keyboard::Period, thor::Action::Hold);
		m_user_map[User_Input::QUOTEHOLD] = thor::Action(sf::Keyboard::Quote, thor::Action::Hold);
		m_user_map[User_Input::SLASHHOLD] = thor::Action(sf::Keyboard::Slash, thor::Action::Hold);
		m_user_map[User_Input::BACKSLASHHOLD] = thor::Action(sf::Keyboard::BackSlash, thor::Action::Hold);
		m_user_map[User_Input::TILDEHOLD] = thor::Action(sf::Keyboard::Tilde, thor::Action::Hold);
		m_user_map[User_Input::EQUALHOLD] = thor::Action(sf::Keyboard::Equal, thor::Action::Hold);
		m_user_map[User_Input::DASHHOLD] = thor::Action(sf::Keyboard::Dash, thor::Action::Hold);
		m_user_map[User_Input::SPACEHOLD] = thor::Action(sf::Keyboard::Space, thor::Action::Hold);
		m_user_map[User_Input::RETURNHOLD] = thor::Action(sf::Keyboard::Return, thor::Action::Hold);
		m_user_map[User_Input::BACKSPACEHOLD] = thor::Action(sf::Keyboard::BackSpace, thor::Action::Hold);
		m_user_map[User_Input::TABHOLD] = thor::Action(sf::Keyboard::Tab, thor::Action::Hold);
		m_user_map[User_Input::PAGEUPHOLD] = thor::Action(sf::Keyboard::PageUp, thor::Action::Hold);
		m_user_map[User_Input::PAGEDOWNHOLD] = thor::Action(sf::Keyboard::PageDown, thor::Action::Hold);
		m_user_map[User_Input::ENDHOLD] = thor::Action(sf::Keyboard::End, thor::Action::Hold);
		m_user_map[User_Input::HOMEHOLD] = thor::Action(sf::Keyboard::Home, thor::Action::Hold);
		m_user_map[User_Input::INSERTHOLD] = thor::Action(sf::Keyboard::Insert, thor::Action::Hold);
		m_user_map[User_Input::DELETEHOLD] = thor::Action(sf::Keyboard::Delete, thor::Action::Hold);
		m_user_map[User_Input::ADDHOLD] = thor::Action(sf::Keyboard::Add, thor::Action::Hold);
		m_user_map[User_Input::SUBTRACTHOLD] = thor::Action(sf::Keyboard::Subtract, thor::Action::Hold);
		m_user_map[User_Input::MULTIPLYHOLD] = thor::Action(sf::Keyboard::Multiply, thor::Action::Hold);
		m_user_map[User_Input::DIVIDEHOLD] = thor::Action(sf::Keyboard::Divide, thor::Action::Hold);
		m_user_map[User_Input::LEFTHOLD] = thor::Action(sf::Keyboard::Left, thor::Action::Hold);
		m_user_map[User_Input::RIGHTHOLD] = thor::Action(sf::Keyboard::Right, thor::Action::Hold);
		m_user_map[User_Input::UPHOLD] = thor::Action(sf::Keyboard::Up, thor::Action::Hold);
		m_user_map[User_Input::DOWNHOLD] = thor::Action(sf::Keyboard::Down, thor::Action::Hold);
		m_user_map[User_Input::PAUSEHOLD] = thor::Action(sf::Keyboard::Pause, thor::Action::Hold);

		//Numpad (hold)
		m_user_map[User_Input::NUMPAD0HOLD] = thor::Action(sf::Keyboard::Numpad0, thor::Action::Hold);
		m_user_map[User_Input::NUMPAD1HOLD] = thor::Action(sf::Keyboard::Numpad1, thor::Action::Hold);
		m_user_map[User_Input::NUMPAD2HOLD] = thor::Action(sf::Keyboard::Numpad2, thor::Action::Hold);
		m_user_map[User_Input::NUMPAD3HOLD] = thor::Action(sf::Keyboard::Numpad3, thor::Action::Hold);
		m_user_map[User_Input::NUMPAD4HOLD] = thor::Action(sf::Keyboard::Numpad4, thor::Action::Hold);
		m_user_map[User_Input::NUMPAD5HOLD] = thor::Action(sf::Keyboard::Numpad5, thor::Action::Hold);
		m_user_map[User_Input::NUMPAD6HOLD] = thor::Action(sf::Keyboard::Numpad6, thor::Action::Hold);
		m_user_map[User_Input::NUMPAD7HOLD] = thor::Action(sf::Keyboard::Numpad7, thor::Action::Hold);
		m_user_map[User_Input::NUMPAD8HOLD] = thor::Action(sf::Keyboard::Numpad8, thor::Action::Hold);
		m_user_map[User_Input::NUMPAD9HOLD] = thor::Action(sf::Keyboard::Numpad9, thor::Action::Hold);

		//Function keys (hold)
		m_user_map[User_Input::F1HOLD] = thor::Action(sf::Keyboard::F1, thor::Action::Hold);
		m_user_map[User_Input::F2HOLD] = thor::Action(sf::Keyboard::F2, thor::Action::Hold);
		m_user_map[User_Input::F3HOLD] = thor::Action(sf::Keyboard::F3, thor::Action::Hold);
		m_user_map[User_Input::F4HOLD] = thor::Action(sf::Keyboard::F4, thor::Action::Hold);
		m_user_map[User_Input::F5HOLD] = thor::Action(sf::Keyboard::F5, thor::Action::Hold);
		m_user_map[User_Input::F6HOLD] = thor::Action(sf::Keyboard::F6, thor::Action::Hold);
		m_user_map[User_Input::F7HOLD] = thor::Action(sf::Keyboard::F7, thor::Action::Hold);
		m_user_map[User_Input::F8HOLD] = thor::Action(sf::Keyboard::F8, thor::Action::Hold);
		m_user_map[User_Input::F9HOLD] = thor::Action(sf::Keyboard::F9, thor::Action::Hold);
		m_user_map[User_Input::F10HOLD] = thor::Action(sf::Keyboard::F10, thor::Action::Hold);
		m_user_map[User_Input::F11HOLD] = thor::Action(sf::Keyboard::F11, thor::Action::Hold);
		m_user_map[User_Input::F12HOLD] = thor::Action(sf::Keyboard::F12, thor::Action::Hold);
		m_user_map[User_Input::F13HOLD] = thor::Action(sf::Keyboard::F13, thor::Action::Hold);
		m_user_map[User_Input::F14HOLD] = thor::Action(sf::Keyboard::F14, thor::Action::Hold);
		m_user_map[User_Input::F15HOLD] = thor::Action(sf::Keyboard::F15, thor::Action::Hold);

		//Mouse user input
		m_user_map[User_Input::LEFTMOUSEPRESSED] = thor::Action(sf::Mouse::Left, thor::Action::PressOnce);
		m_user_map[User_Input::LEFTMOUSEHOLD] = thor::Action(sf::Mouse::Left, thor::Action::Hold);
		m_user_map[User_Input::RIGHTMOUSEPRESSED] = thor::Action(sf::Mouse::Right, thor::Action::PressOnce);
		m_user_map[User_Input::RIGHTMOUSEHOLD] = thor::Action(sf::Mouse::Right, thor::Action::Hold);
		m_user_map[User_Input::MIDDLEPRESS] = thor::Action(sf::Mouse::Middle, thor::Action::PressOnce);
		m_user_map[User_Input::MIDDLEHOLD] = thor::Action(sf::Mouse::Middle, thor::Action::Hold);

		//sf::Event user input
		m_user_map[User_Input::CLOSED] = thor::Action(sf::Event::Closed);
		m_user_map[User_Input::TEXTENTERED] = thor::Action(sf::Event::TextEntered);
		m_user_map[User_Input::MOUSELEFT] = thor::Action(sf::Event::MouseLeft);
		m_user_map[User_Input::MOUSEENTERED] = thor::Action(sf::Event::MouseEntered);
	}

	void InputManager::preUpdate()
	{
		if (!m_activatedKeys)
		{
			initKeys();
			m_activatedKeys = true;
		}

		//So this doesn't have to be put in every single scene
		if (m_user_map.isActive(User_Input::CLOSED))
			Engine::quit();

		else if (m_user_map.isActive(User_Input::FPRESS))
			FPS::setEnabled(!FPS::enabled());

		SceneManager::getCurrentScene().processInput(*this);

		m_user_map.clearEvents();
	}

	void InputManager::update(sf::Time dt, const sf::Event& evt)
	{
		m_user_map.pushEvent(evt);

		Engine::getSceneManager().getCurrentScene().m_gui.handleEvents(evt);
		Engine::getSceneManager().getCurrentScene().m_gui.update(dt);
	}
}
