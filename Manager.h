#pragma once

//Engine includes
#include "Event.h"

//System includes
#include <string>

namespace df {

	class Manager {

	private:
		std::string m_type;  //Manager type identifier
		bool m_is_started;   //True when started successfully

	protected:
		//set type identifier of manager
		void setType(std::string type);

	public:
		Manager();
		virtual ~Manager();

		//Get type identifer of manager
		std::string getType() const;

		//Startup manager
		//return 0 if ok, else negative number
		int startUp();

		//shutdown manager
		virtual void shutDown();

		//Return true when startUp() was executed ok, else false
		bool isStarted() const;

		int onEvent(const Event* p_event) const;
	};

} //end of namespace df
