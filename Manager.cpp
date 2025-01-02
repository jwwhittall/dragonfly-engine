#include "Manager.h"
#include "WorldManager.h"
#include "ObjectListIterator.h"
#include "ObjectList.h"

namespace df {

	bool m_is_started;
	std::string m_type;

	//constructor initializes m_is_started
	//to be inhereted and built upon
	Manager::Manager()
	{
		m_is_started = false;
		setType("Manager");
	}

	Manager::~Manager()
	{
		shutDown();
	}

	//called to start manager
	int Manager::startUp()
	{
		if (!m_is_started) //not yet started?
		{
			m_is_started = true; //indicate started
			return 1;
		}
		return 0; //if already started, ignore
	}

	//called to shut down manager - sets is_started to false as long as it is already true
	void Manager::shutDown()
	{
		if (m_is_started) m_is_started = false;
	}

	//returns value of private bool is_started
	bool Manager::isStarted() const
	{
		return m_is_started;
	}

	//sets type to given string
	void Manager::setType(std::string type)
	{
		m_type = type;
	}

	//returns type
	std::string Manager::getType() const
	{
		return m_type;
	}

	//Send event to all Objects
	//Return count of number of events sent
	int Manager::onEvent(const Event* p_event) const
	{
		int count = 0;

		ObjectList all_objects = WM.getAllObjects();
		ObjectListIterator li = ObjectListIterator(&all_objects);

		while (!li.isDone())
		{
			li.currentObejct()->eventHandler(p_event);
			li.next();
			count++;
		}

		return count;
	}
}