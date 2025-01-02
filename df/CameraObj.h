#pragma once

#include "Object.h"
#include "EventKeyboard.h"
#include "Event.h"

//inherits from object class
class CameraObj : public df::Object {

public:
	//Constructor, destructor
	CameraObj();
	~CameraObj();

	int eventHandler(const df::Event* p_e) override;

	int draw();

	void kbd(const df::EventKeyboard* p_keyboard_event);
};