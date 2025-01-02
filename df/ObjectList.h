#pragma once

#include "Object.h"
#include "ObjectListIterator.h"

namespace df {

	const int MAX_OBJECTS = 2000;

	class ObjectListIterator;

	class ObjectList {

	private:
		int m_count;
		Object* m_p_obj[MAX_OBJECTS];

	public:
		friend class ObjectListIterator;

		//default constructor
		ObjectList();

		//Insert object pointer in list
		//return 0 if ok, else -1
		int insert(Object* p_o);

		//Remove object pointer from list.
		//Return 0 if found, else -1
		int remove(Object* p_o);

		//Clear list (setting count to 0)
		void clear();

		//Return true if list is empty, else false
		bool isEmpty() const;

		//Return true if list is full, else false
		bool isFull() const;

		int getCount() const;
	};

}


