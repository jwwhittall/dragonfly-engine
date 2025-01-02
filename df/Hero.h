#pragma once

#include "Object.h"
#include "EventKeyboard.h"

class Hero : public df::Object {

public:
	Hero();
	~Hero();

	int count;

	int eventHandler(const df::Event* p_e) override;

	int draw();

	void kbd(const df::EventKeyboard* p_keyboard_event);

};
