#include "Event.h"

namespace df {

	//set type to df::undefined
	Event::Event()
	{
		m_event_type = df::UNDEFINED_EVENT;
	}

	Event::~Event()
	{
	}

	//sets type to given string
	void Event::setType(std::string new_type)
	{
		m_event_type = new_type;
	}

	//returns type of event
	std::string Event::getType() const
	{
		return m_event_type;
	}

}