#ifndef UTILITY_H
#define UTILITY_H

//#include <Application.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>

#include <Thor/Input.hpp>

#include <SFGUI/Widgets.hpp>

#include <sstream>

namespace sf
{
    class Sprite;
    class Text;
}

namespace Keys
{
    enum KeyboardInput
	{
		//Keyboard user input
		UNKNOWN,
		APRESS, AHOLD,
		BPRESS, BHOLD,
		CPRESS, CHOLD,
		DPRESS, DHOLD,
		EPRESS, EHOLD,
		FPRESS, FHOLD,
		GPRESS, GHOLD,
		HPRESS, HHOLD,
		IPRESS, IHOLD,
		JPRESS, JHOLD,
		KPRESS, KHOLD,
		LPRESS, LHOLD,
		MPRESS, MHOLD,
		NPRESS, NHOLD,
		OPRESS, OHOLD,
		PPRESS, PHOLD,
		QPRESS, QHOLD,
		RPRESS, RHOLD,
		SPRESS, SHOLD,
		TPRESS, THOLD,
		UPRESS, UHOLD,
		VPRESS, VHOLD,
		WPRESS, WHOLD,
		XPRESS, XHOLD,
		YPRESS, YHOLD,
		ZPRESS, ZHOLD,
		NUM0PRESS, NUM0HOLD,
		NUM1PRESS, NUM1HOLD,
		NUM2PRESS, NUM2HOLD,
		NUM3PRESS, NUM3HOLD,
		NUM4PRESS, NUM4HOLD,
		NUM5PRESS, NUM5HOLD,
		NUM6PRESS, NUM6HOLD,
		NUM7PRESS, NUM7HOLD,
		NUM8PRESS, NUM8HOLD,
		NUM9PRESS, NUM9HOLD,
		ESCAPEPRESS, ESCAPEHOLD,
		LCONTROLPRESS, LCONTROLHOLD,
		LSHIFTPRESS, LSHIFTHOLD,
		LALTPRESS, LALTHOLD,
		LSYSTEMPRESS, LSYSTEMHOLD,
		RCONTROLPRESS, RCONTROLHOLD,
		RSHIFTPRESS, RSHIFTHOLD,
		RALTPRESS, RALTHOLD,
		RSYSTEMPRESS, RSYSTEMHOLD,
		MENUPRESS, MENUHOLD,
		LBRACKETPRESS, LBRACKETHOLD,
		RBRACKETPRESS, RBRACKETHOLD,
		SEMICOLONPRESS, SEMICOLONHOLD,
		COMMAPRESS, COMMAHOLD,
		PERIODPRESS, PERIODHOLD,
		QUOTEPRESS, QUOTEHOLD,
		SLASHPRESS, SLASHHOLD,
		BACKSLASHPRESS, BACKSLASHHOLD,
		TILDEPRESS, TILDEHOLD,
		EQUALPRESS, EQUALHOLD,
		DASHPRESS, DASHHOLD,
		SPACEPRESS, SPACEHOLD,
		RETURNPRESS, RETURNHOLD,
		BACKSPACEPRESS, BACKSPACEHOLD,
		TABPRESS, TABHOLD,
		PAGEUPPRESS, PAGEUPHOLD,
		PAGEDOWNPRESS, PAGEDOWNHOLD,
		ENDPRESS, ENDHOLD,
		HOMEPRESS, HOMEHOLD,
		INSERTPRESS, INSERTHOLD,
		DELETEPRESS, DELETEHOLD,
		ADDPRESS, ADDHOLD,
		SUBTRACTPRESS, SUBTRACTHOLD,
		MULTIPLYPRESS, MULTIPLYHOLD,
		DIVIDEPRESS, DIVIDEHOLD,
		LEFTPRESS, LEFTHOLD,
		RIGHTPRESS, RIGHTHOLD,
		UPPRESS, UPHOLD,
		DOWNPRESS, DOWNHOLD,
		NUMPAD0PRESS, NUMPAD0HOLD,
		NUMPAD1PRESS, NUMPAD1HOLD,
		NUMPAD2PRESS, NUMPAD2HOLD,
		NUMPAD3PRESS, NUMPAD3HOLD,
		NUMPAD4PRESS, NUMPAD4HOLD,
		NUMPAD5PRESS, NUMPAD5HOLD,
		NUMPAD6PRESS, NUMPAD6HOLD,
		NUMPAD7PRESS, NUMPAD7HOLD,
		NUMPAD8PRESS, NUMPAD8HOLD,
		NUMPAD9PRESS, NUMPAD9HOLD,
		F1PRESS, F1HOLD,
		F2PRESS, F2HOLD,
		F3PRESS, F3HOLD,
		F4PRESS, F4HOLD,
		F5PRESS, F5HOLD,
		F6PRESS, F6HOLD,
		F7PRESS, F7HOLD,
		F8PRESS, F8HOLD,
		F9PRESS, F9HOLD,
		F10PRESS, F10HOLD,
		F11PRESS, F11HOLD,
		F12PRESS, F12HOLD,
		F13PRESS, F13HOLD,
		F14PRESS, F14HOLD,
		F15PRESS, F15HOLD,
		PAUSEPRESS, PAUSEHOLD,

		//Mouse user input
		LEFTMOUSEPRESSED, LEFTMOUSEHOLD,
		RIGHTMOUSEPRESSED, RIGHTMOUSEHOLD,
		MIDDLEPRESS, MIDDLEHOLD,

		//sf::Event user input
		CLOSED,
		TEXTENTERED,
		MOUSELEFT,
		MOUSEENTERED
	};
}

void initKeys(thor::ActionMap<Keys::KeyboardInput>& keyboardMap);

std::string toString(sf::Keyboard::Key key);

void centerWindowX(sfg::Window::Ptr window);

void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);

float toDegree(float radian);
float toRadian(float degree);

//Random number generator
int randomInt(int exclusiveMax);
int randomInt(int minNum, int maxNum);

//Vector operations
float length(sf::Vector2f vector);
sf::Vector2f unitVector(sf::Vector2f vector);

#endif // UTILITY_H
