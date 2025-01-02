#include "Saucer.h"
#include <EventStep.h>
#include "logManager.h"
#include "DisplayManager.h"
#include "EventCollision.h"
#include "EventOut.h"


//object used for testing derived object code
//constructor sets type to 'Saucer'
Saucer::Saucer()
{
	setType("Saucer");
	setAltitude(2);
	count = 0;
	setVelocity(df::Vector(0.25, 0));
	setSolidness(df::HARD);
}

//nothing in constsructor; handled by parent class
Saucer::~Saucer()
{
}

//handles step and undefined events, prints to log to prove
int Saucer::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == df::STEP_EVENT)
	{
		//count++;
		//LM.writeLog("\nStep event %d handled by saucer!", count);
		return 1;
	}
	if (p_e->getType() == df::UNDEFINED_EVENT)
	{
		LM.writeLog("\nUndefined event handled by saucer!");
		return 1;
	}
	if (p_e->getType() == df::COLLISION_EVENT)
	{
		LM.writeLog("\nCOLLISION EVENT HANDLED BY SAUCER! ID: %d", this->getId());
		return 1;
	}
	if (p_e->getType() == df::OUT_EVENT)
	{
		LM.writeLog("\nOUT EVENT HANDLED BY SAUCER! ID: %d", this->getId());
		return 1;
	}
	return 0;
}

int Saucer::draw()
{
	/*
	if (DM.drawCh(this->getPosition(), '%', df::YELLOW) == -1)
	{
		LM.writeLog("\nSacuer.draw- drawch unsuccessful!");
		return 1;
	}
	LM.writeLog("\nSaucer drawn at x: %f, y: %f", this->getPosition().getX(), this->getPosition().getY());
	*/
	Object::draw();
	return 0;
}
