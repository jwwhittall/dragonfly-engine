#pragma once

namespace df {

	//The clock, for timing (such as in the game loop)


	class Clock {

	private:
		long int m_previous_time;

		long int getTimeNow();

	public:
		//Sets previous_time to current time
		Clock();

		//Return time elapsed since delta() was last called, -1 if error
		//Resets previous time
		//Unites are microseconds
		long int delta();

		//Return time elapsed since delta() was last called, -1 if error

		//Does not reset previous time
		//Units are microseconds
		long int split() const;
	};

}
