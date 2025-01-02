#include "Hero.h"
#include "EventStep.h"
#include "logManager.h"
#include "DisplayManager.h"
#include "WorldManager.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "EventOut.h"

Hero::Hero()
{
	setType("Hero");
	setAltitude(df::MAX_ALTITUDE);
	count = 4;
	setSolidness(df::SPECTRAL);
}

Hero::~Hero()
{
}

int Hero::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == df::STEP_EVENT)
	{
		setAltitude(count);
		count--;
		if (count == 0) count = 4;
		//LM.writeLog("\nStep event %d handled by hero!", count);
		return 1;
	}
	if (p_e->getType() == df::UNDEFINED_EVENT)
	{
		LM.writeLog("\nUndefined event handled by hero!");
		return 1;
	}
	if (p_e->getType() == df::OUT_EVENT)
	{
		LM.writeLog("\nOUT event handled by hero! ID: %d", this->getId());
		return 1;
	}
	if (p_e->getType() == df::KEYBOARD_EVENT)
	{
		const df::EventKeyboard* p_keyboard_event =
			dynamic_cast <const df::EventKeyboard*> (p_e);
		LM.writeLog("\nKeyboard event handled by hero! Key %d, Action %d", p_keyboard_event->getKey(), p_keyboard_event->getKeyboardAction());
		kbd(p_keyboard_event);
		return 1;
	}
	if (p_e->getType() == df::MSE_EVENT)
	{
		const df::EventMouse* p_mse_event =
			dynamic_cast <const df::EventMouse*> (p_e);
		if (p_mse_event->getMouseAction() == df::CLICKED)
		{
			LM.writeLog("\nMouse event handled by hero! Button: %d Action: %d", p_mse_event->getMouseButton(), p_mse_event->getMouseAction());
			return 1;
		}
		if (p_mse_event->getMouseAction() == df::MOVED)
		{
			LM.writeLog("\nMouse event handled by hero! Action: %d", p_mse_event->getMouseAction());
			return 1;
		}
		
	}
	return 0;
}

int Hero::draw()
{
	
	switch (this->getAltitude()) {
	default:
		if (DM.drawCh(df::Vector(this->getPosition()), '0', df::MAGENTA) == -1)
		{
			LM.writeLog("\nHero.draw- drawch unsuccessful!");
			return 1;
		}
		break;
	case 1:
		if (DM.drawCh(df::Vector(this->getPosition()), '0', df::YELLOW) == -1)
		{
			LM.writeLog("\nHero.draw- drawch unsuccessful!");
			return 1;
		}
		break;
	case 0:
		if (DM.drawCh(df::Vector(this->getPosition()), '0', df::YELLOW) == -1)
		{
			LM.writeLog("\nHero.draw- drawch unsuccessful!");
			return 1;
		}
		break;
		
	}
	
	//Object::draw();
	return 0;
}

void Hero::kbd(const df::EventKeyboard* p_keyboard_event)
{
	switch (p_keyboard_event->getKey()) {
	case df::Keyboard::W: //up if w pressed
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
			this->setPosition(df::Vector(this->getPosition().getX(), this->getPosition().getY() - 1));
		break;
	case df::Keyboard::S: //down if s pressed
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
			this->setPosition(df::Vector(this->getPosition().getX(), this->getPosition().getY() + 1));
		break;
	case df::Keyboard::A: //left if a pressed
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
			this->setPosition(df::Vector(this->getPosition().getX() - 1, this->getPosition().getY()));
		break;
	case df::Keyboard::D: //right if d pressed
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
			this->setPosition(df::Vector(this->getPosition().getX() + 1, this->getPosition().getY()));
		break;
	case df::Keyboard::SPACE: //left velocity if space pressed
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
			this->setVelocity(df::Vector(-0.3, 0));
		break;
	case df::Keyboard::B: //right velocity if b pressed
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
			this->setVelocity(df::Vector(0.3, 0));
		break;
	}
}
