#include "EventKeyboard.h"
#include "Event.h"

namespace df {

	using namespace Keyboard;

	//constructor setting all attributes and type
	df::EventKeyboard::EventKeyboard()
	{
		m_key_val = UNDEFINED_KEY;
		m_keyboard_action = UNDEFINED_KEYBOARD_ACTION;
		setType(df::KEYBOARD_EVENT);
	}

	//getters and setters for key
	void df::EventKeyboard::setKey(Keyboard::Key new_key)
	{
		m_key_val = new_key;
	}

	Keyboard::Key df::EventKeyboard::getKey() const
	{
		return m_key_val;
	}

	//getter and setter for action
	void df::EventKeyboard::setKeyboardAction(EventKeyboardAction new_action)
	{
		m_keyboard_action = new_action;
	}

	EventKeyboardAction EventKeyboard::getKeyboardAction() const
	{
		return m_keyboard_action;
	}

}