#pragma once

#include "Manager.h"
namespace df {

#define IM df::InputManager::getInstance()

	class InputManager : public Manager {

	private:
		InputManager();
		InputManager(InputManager const&);
		void operator = (InputManager const&);

	public:
		//get the one and only instance
		static InputManager& getInstance();

		//Get window ready to capture input
		//Return 0 if ok, else return -1
		int startUp();

		//Revert back to normal window mode
		void shutDown();

		//Get input from the keyboard and mouse
		//Pass event along to all objects
		void getInput() const;
	};
}
