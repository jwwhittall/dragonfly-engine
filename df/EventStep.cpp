#include "EventStep.h"

namespace df {

	//default constructor: sets type to 'Step', count to 0
	df::EventStep::EventStep()
	{
		setType(df::STEP_EVENT);
		m_step_count = 0;
	}

	//constructor with passed in initial step count
	df::EventStep::EventStep(int init_step_count)
	{
		setType(df::STEP_EVENT);
		m_step_count = init_step_count;
	}

	//sets step count to desired number
	void df::EventStep::setStepCount(int new_step_count)
	{
		m_step_count = new_step_count;
	}

	//returns step count
	int df::EventStep::getStepCount() const
	{
		return m_step_count;
	}

}