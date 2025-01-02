#include "EventCollision.h"

namespace df {

	//default constructor without objects or vector
	df::EventCollision::EventCollision()
	{
		m_pos = df::Vector();
		setType(df::COLLISION_EVENT);
	}

	//constructor with passed in objects and vector
	df::EventCollision::EventCollision(Object* p_o1, Object* p_o2, Vector p)
	{
		m_pos = p;
		m_p_obj1 = p_o1;
		m_p_obj2 = p_o2;
		setType(df::COLLISION_EVENT);
	}

	//getter/setter for first object
	void df::EventCollision::setObject1(Object* p_new_o1)
	{
		m_p_obj1 = p_new_o1;
	}

	Object* df::EventCollision::getObject1() const
	{
		return m_p_obj1;
	}

	//getter/setter for object 2 in collision
	void df::EventCollision::setObject2(Object* p_new_o2)
	{
		m_p_obj2 = p_new_o2;
	}

	Object* EventCollision::getObject2() const
	{
		return m_p_obj2;
	}

	//getter/setter for position of collision
	void EventCollision::setPosition(Vector new_pos)
	{
		m_pos = new_pos;
	}

	Vector EventCollision::getPosition() const
	{
		return m_pos;
	}

}