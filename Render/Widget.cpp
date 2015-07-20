
#include "Widget.hpp"
#include "SceneManager.hpp"

namespace SE
{
    // Signals.
    Signal::SignalID Widget::OnMouseEnter = 0;
    Signal::SignalID Widget::OnMouseLeave = 0;
    Signal::SignalID Widget::OnMouseMove = 0;
    Signal::SignalID Widget::OnMouseLeftPress = 0;
    Signal::SignalID Widget::OnMouseRightPress = 0;
    Signal::SignalID Widget::OnMouseLeftRelease = 0;
    Signal::SignalID Widget::OnMouseRightRelease = 0;

    Signal::SignalID Widget::OnLeftClick = 0;
    Signal::SignalID Widget::OnRightClick = 0;

    Signal::SignalID Widget::OnKeyPress = 0;
    Signal::SignalID Widget::OnKeyRelease = 0;
    Signal::SignalID Widget::OnText = 0;

	Widget::Widget(const std::string& id) :
		m_id(id),
		m_widgetType(typeid(*this).name()),
		m_state(WidgetState::NORMAL),
		m_visible(true),
		m_inWidget(false),
		m_draggable(false),
		m_holding(false),
		m_attachedToMenu(false),
		m_position(sf::Vector2f(0, 0))
	{

	}

	void Widget::checkHold(sf::Mouse::Button button, bool press, int x, int y)
	{
	    if (!m_draggable || button != sf::Mouse::Middle)
            return;

        if (!press)
        {
            m_holding = false;

            return;
        }

        if (m_bounds.contains(static_cast<float>(x), static_cast<float>(y)))
        {
            if (!m_holding)
            {
                m_holding = true;

                m_dragOffset = sf::Vector2f(static_cast<float>(x) - m_bounds.left, static_cast<float>(y) - m_bounds.top);
            }
        }
	}

	bool Widget::isMouseButtonDown(sf::Mouse::Button button) const
	{
        if (button == sf::Mouse::ButtonCount)
            return m_mouse_button_down != sf::Mouse::ButtonCount;

        return m_mouse_button_down == button;
	}

	void Widget::setMouseButtonDown(sf::Mouse::Button button)
	{
	    m_mouse_button_down = static_cast<unsigned char>(button & 0x3f);
	}

	void Widget::handleEvents(const sf::Event& event)
	{
		if (!m_visible)
			return;

        sf::Vector2f mouseCoords = SceneManager::getGameMouseCoords();

        switch (event.type)
        {
		case sf::Event::MouseLeft:
			if (getInWidget())
            {
				setInWidget(false);

				m_signalQueue.emit(OnMouseLeave);
				handleMouseLeave(std::numeric_limits<int>::min(), std::numeric_limits<int>::min());
			}

			handleMouseMoveEvent(std::numeric_limits<int>::min(), std::numeric_limits<int>::min());

			setMouseButtonDown();
			handleMouseButtonEvent(sf::Mouse::Left, false, std::numeric_limits<int>::min(), std::numeric_limits<int>::min());
			handleMouseButtonEvent(sf::Mouse::Right, false, std::numeric_limits<int>::min(), std::numeric_limits<int>::min());

			break;

		case sf::Event::MouseMoved:
			// Check if pointer inside of widget's allocation.
			if (getBounds().contains(mouseCoords))
            {
				// Check for enter event.
				if(!getInWidget())
                {
					setInWidget(true);

					m_signalQueue.emit(OnMouseEnter);

					handleMouseEnter(mouseCoords.x, mouseCoords.y);
				}

				m_signalQueue.emit(OnMouseMove);
			}
			else if (getInWidget())
            { // Check for leave event.
				setInWidget(false);

				m_signalQueue.emit(OnMouseLeave);
				handleMouseLeave(mouseCoords.x, mouseCoords.y);
			}

			handleMouseMoveEvent(mouseCoords.x, mouseCoords.y);
			break;

		case sf::Event::MouseButtonPressed:
			if (!isMouseButtonDown() && getInWidget())
				setMouseButtonDown(event.mouseButton.button);

			handleMouseButtonEvent(event.mouseButton.button, true, mouseCoords.x, mouseCoords.y);

			if (getInWidget())
            {
				if (event.mouseButton.button == sf::Mouse::Left)
					m_signalQueue.emit(OnMouseLeftPress);

				else if (event.mouseButton.button == sf::Mouse::Right)
					m_signalQueue.emit(OnMouseRightPress);
			}

			break;

		case sf::Event::MouseButtonReleased:
			// Only process as a click when mouse button has been pressed inside the widget before.
			if (isMouseButtonDown(event.mouseButton.button))
            {
				setMouseButtonDown();

				// When released inside the widget, the event can be considered a click.
				if (getInWidget())
                {
					handleMouseClick(event.mouseButton.button, mouseCoords.x, mouseCoords.y);

					if (event.mouseButton.button == sf::Mouse::Left)
						m_signalQueue.emit(OnLeftClick);

					else if (event.mouseButton.button == sf::Mouse::Right)
						m_signalQueue.emit(OnRightClick);
				}
			}

			handleMouseButtonEvent(event.mouseButton.button, false, mouseCoords.x, mouseCoords.y);

			if (getInWidget())
            {
				if (event.mouseButton.button == sf::Mouse::Left)
					m_signalQueue.emit(OnMouseLeftRelease);

				else if (event.mouseButton.button == sf::Mouse::Right)
					m_signalQueue.emit(OnMouseRightRelease);
			}

			break;

		case sf::Event::KeyPressed:
            handleKeyEvent(event.key.code, true);
            m_signalQueue.emit(OnKeyPress);

			break;

		case sf::Event::KeyReleased:
            handleKeyEvent(event.key.code, false);
            m_signalQueue.emit(OnKeyRelease);

			break;

		case sf::Event::TextEntered:
            handleTextEvent(event.text.unicode);
            m_signalQueue.emit(OnText);

			break;

		default:
			break;
        }
	}
}
