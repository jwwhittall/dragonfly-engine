#include "ObjectListIterator.h"
#include "ObjectList.h"
#include "Object.h"

namespace df {

	df::ObjectListIterator::ObjectListIterator(const ObjectList* p_l)
	{
		//sets list for iterator to the one passed into constructor
		m_p_list = p_l;
		//sets index to 0
		first();
	}

	//sets iterator to first item
	void ObjectListIterator::first()
	{
		m_index = 0;
	}

	//iterate to next item
	void ObjectListIterator::next()
	{
		if (this->isDone()) return;
		//is there a next value?
		if (m_index < m_p_list->m_count)
		{
			//increment index
			m_index++;
		}
	}

	//has the iterator reached the end of the list?
	bool ObjectListIterator::isDone() const
	{
		return (m_index == m_p_list->m_count);
	}

	//return current item iterator points to
	//list cannot be empty to call
	df::Object* ObjectListIterator::currentObejct() const
	{
		return m_p_list->m_p_obj[m_index];
	}
}