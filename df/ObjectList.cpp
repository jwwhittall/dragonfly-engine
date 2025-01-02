#include "ObjectList.h"

namespace df {


	//set count of items in list to 0
	df::ObjectList::ObjectList()
	{
		m_count = 0;
	}

	//inserts the passed in Object* into the next slot in the list
	//as long as the list is not at max
	int df::ObjectList::insert(Object* p_o)
	{
		//is there room in the list?
		if (m_count == MAX_OBJECTS) return -1;

		//if so, add object* to the next spot in the list
		m_p_obj[m_count] = p_o;

		//increase the count by one to account for added item
		m_count++;
		return 0;
	}

	//removes the given object, swapping the last item in the list with
	int df::ObjectList::remove(Object* p_o)
	{
		for (int i = 0; i < m_count; i++)
		{
			if (m_p_obj[i] == p_o)
			{
				for (int j = i; j < m_count - 1; j++)
				{
					m_p_obj[j] = m_p_obj[j + 1];
				}
				m_count--;
				return 0;
			}
		}
		return -1;
	}

	//sets count of objects to zero
	void df::ObjectList::clear()
	{
		m_count = 0;
	}

	//are there 0 objects in the list?
	bool df::ObjectList::isEmpty() const
	{
		return m_count == 0;
	}

	//are there 2000 objects in the list?
	bool df::ObjectList::isFull() const
	{
		return m_count == MAX_OBJECTS;
	}

	int df::ObjectList::getCount() const
	{
		return m_count;
	}
}
