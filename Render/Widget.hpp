#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <typeinfo>

#include <SFML/Graphics.hpp>

#include "InputManager.hpp"
#include "Signal.hpp"

namespace SE
{
	class Widget : public sf::Drawable
	{
	public:
		//Because we're lazy
		typedef std::shared_ptr<Widget> Ptr;

		//The possible states of the widget
		//Defaults to normal
		enum class WidgetState : uint8_t
		{
			NORMAL = 0,
	        ACTIVE, //When a button is pressed
	        PRELIGHT, //when something is hovered over
	        SELECTED, //When something is selected (like an editbox)
            DISABLED //Widget is disabled
		};

		virtual ~Widget() {};

		virtual void handleEvents(const sf::Event& event);

		//Setters
		const void setState(WidgetState state) { m_state = state; }

		const void setId(const std::string& id) { m_id = id; }

		const void setVisible(bool visible) { m_visible = visible; }
		const void setInWidget(bool inWidget) { m_inWidget = inWidget; }
		const void setDraggable(bool draggable) { m_draggable = draggable; }
		const void setHolding(bool holding) { m_holding = holding; }

		const void attachToMenu(const std::string& menuId)
        {
            m_menuAttachedId = menuId;
            m_attachedToMenu = true;
        }

		const void detachFromMenu() { m_menuAttachedId = ""; m_attachedToMenu = false; }

		virtual const void setBounds(const sf::FloatRect& bounds) { m_bounds = bounds; }
		virtual const void setPosition(const sf::Vector2f& pos) { m_position = pos; }
		const void setDragOffset(const sf::Vector2f& offset) { m_dragOffset = offset; }

		//Getters
		const WidgetState getState() const { return m_state; }

		const std::string& getId() const { return m_id; }

		const bool getVisible() const { return m_visible; }
		const bool getInWidget() const { return m_inWidget; }
		const bool getDraggable() const { return m_draggable; }
		const bool getHolding() const { return m_holding; }
		const bool getAttachedToMenu() const { return m_attachedToMenu; }
		const std::string& getMenuAttachedId() const { return m_menuAttachedId; }
		const std::string& getWidgetType() const { return m_widgetType; }

		const sf::FloatRect& getBounds() const { return m_bounds; }
		const sf::Vector2f& getPosition() const { return m_position; }
		const sf::Vector2f& getDragOffset() const { return m_dragOffset; }

		virtual void checkHold(sf::Mouse::Button button, bool press, int x, int y);

        virtual void update(sf::Time dt) = 0;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

        //Different types of signals
        static Signal::SignalID OnMouseEnter; //!< Fired when mouse entered widget.
		static Signal::SignalID OnMouseLeave; //!< Fired when mouse left widget.
		static Signal::SignalID OnMouseMove; //!< Fired when mouse moved over widget.
		static Signal::SignalID OnMouseLeftPress; //!< Fired when left button pressed.
		static Signal::SignalID OnMouseRightPress; //!< Fired when right button pressed.
		static Signal::SignalID OnMouseLeftRelease; //!< Fired when left button released.
		static Signal::SignalID OnMouseRightRelease; //!< Fired when right button released.

		static Signal::SignalID OnLeftClick; //!< Fired when left button clicked.
		static Signal::SignalID OnRightClick; //!< Fired when right button clicked.

		static Signal::SignalID OnKeyPress; //!< Fired when a key is pressed while State == Active.
		static Signal::SignalID OnKeyRelease; //!< Fired when a key is released while State == Active.
		static Signal::SignalID OnText; //!< Fired when text is entered while State == Active.

	protected:
		Widget(const std::string& id);

        bool isMouseButtonDown(sf::Mouse::Button button = sf::Mouse::ButtonCount) const;

        void setMouseInWidget(bool inWidget) { m_inWidget = inWidget; }
        void setMouseButtonDown(sf::Mouse::Button button = sf::Mouse::ButtonCount);

        virtual void handleMouseMoveEvent(int x, int y)
        {
            if (m_holding)
                setPosition(sf::Vector2f(static_cast<float>(x) - m_dragOffset.x, static_cast<float>(y) - m_dragOffset.y));
        };

        virtual void handleMouseButtonEvent(sf::Mouse::Button button, bool press, int x, int y) { checkHold(button, press, x, y); };

		//Handling methods
		virtual void handleMouseEnter(int x, int y) {};
		virtual void handleMouseLeave(int x, int y) {};

		//Handle user pressing (or releasing) a button
		virtual void handleKeyEvent(sf::Keyboard::Key, bool pressed) {};

		//Handle user inputing text
		virtual void handleTextEvent(sf::Uint32 character) {};

		virtual void handleMouseClick(sf::Mouse::Button button, int x, int y) {};

		sf::Vector2f m_position;

        SignalQueue m_signalQueue;

	private:
		WidgetState m_state;

		std::string m_id;
		std::string m_menuAttachedId;
		std::string m_widgetType;

		bool m_visible;
		bool m_inWidget;
		bool m_draggable;
		bool m_holding;
		bool m_attachedToMenu;

		sf::FloatRect m_bounds;

		sf::Vector2f m_dragOffset;

		unsigned char m_mouse_button_down : 6;
	};
}
