#pragma once

#include "Object.h"
#include "ObjectList.h"

namespace df {

	class ObjectList;

	class ObjectListIterator {

	private:
		ObjectListIterator();		//Must be give list when created
		int m_index;				//Index into list
		const ObjectList* m_p_list; //List iterating over

	public:
		//Create iterator, over indicated list
		ObjectListIterator(const ObjectList* p_l);

		//Set iterator to first item in list
		void first();
		//Set iterator to next item in list
		void next();
		//Return true if at end of list
		bool isDone() const;

		//Return pointer to current object, NULL if done/empty
		df::Object* currentObejct() const;

	};
}
