#pragma once

#include "Object.h"

//inherits from object class
class Saucer : public df::Object {

public:
	//constructor, destructor
	Saucer();
	~Saucer();

	int count;

	//handles step and default events for testing purposes
	int eventHandler(const df::Event* p_e) override;

	int draw();

};