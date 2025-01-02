#include "CameraObj.h"
#include "DisplayManager.h"
#include "logManager.h"
#include "EventKeyboard.h"
#include "WorldManager.h"

CameraObj::CameraObj()
{
	setType("CameraObj");
	setAltitude(3);
	setSolidness(df::SPECTRAL);
	setPosition(df::Vector(DM.getHorizontal()/2, DM.getVertical()/2));
	//make the camera follow this object
	WM.setViewFollowing(this);
}

CameraObj::~CameraObj()
{
}

int CameraObj::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == df::KEYBOARD_EVENT)
	{
		const df::EventKeyboard* p_keyboard_event =
			dynamic_cast <const df::EventKeyboard*> (p_e);
		LM.writeLog("\nKeyboard event handled by camera object! Key %d, Action %d", p_keyboard_event->getKey(), p_keyboard_event->getKeyboardAction());
		kbd(p_keyboard_event);
		return 1;
	}
}

int CameraObj::draw()
{
	if (DM.drawCh(this->getPosition(), '+', df::RED) == -1)
	{
		LM.writeLog("\nCameraObj.draw- drawch unsuccessful!");
		
		return 1;
	}
	LM.writeLog("\nCAMERAOBJ POSITION %f, %f", this->getPosition().getX(), this->getPosition().getY());
}

void CameraObj::kbd(const df::EventKeyboard* p_keyboard_event)
{
	float x = getPosition().getX();
	float y = getPosition().getY();

	switch (p_keyboard_event->getKey()) {
	case df::Keyboard::W: //up if w pressed
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
			WM.moveObject(this, df::Vector(x, y - 1));
		break;
	case df::Keyboard::S: //down if s pressed
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
			WM.moveObject(this, df::Vector(x, y + 1));
		break;
	case df::Keyboard::A: //left if a pressed
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
			WM.moveObject(this, df::Vector(x - 1, y));
		break;
	case df::Keyboard::D: //right if d pressed
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
			WM.moveObject(this, df::Vector(x + 1, y));
		break;
	}
}
