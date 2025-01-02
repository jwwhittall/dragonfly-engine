#include "EventMouse.h"

namespace df {

	using namespace Mouse;

	//define attributes and type
	df::EventMouse::EventMouse()
	{
		m_mouse_action = UNDEFINED_MOUSE_ACTION;
		m_mouse_button = UNDEFINED_MOUSE_BUTTON;
		m_mouse_xy = df::Vector();
		setType(df::MSE_EVENT);
	}

	//getter setter for mouse action
	void df::EventMouse::setMouseAction(EventMouseAction new_mouse_action)
	{
		m_mouse_action = new_mouse_action;
	}

	EventMouseAction df::EventMouse::getMouseAction() const
	{
		return m_mouse_action;
	}

	//get and set mouse button
	void df::EventMouse::setMouseButton(Mouse::Button new_mouse_button)
	{
		m_mouse_button = new_mouse_button;
	}

	Mouse::Button EventMouse::getMouseButton() const
	{
		return m_mouse_button;
	}

	//get and set mouse position
	void EventMouse::setMousePosition(df::Vector new_mouse_xy)
	{
		m_mouse_xy = new_mouse_xy;
	}

	df::Vector EventMouse::getMousePosition() const
	{
		return m_mouse_xy;
	}

}
