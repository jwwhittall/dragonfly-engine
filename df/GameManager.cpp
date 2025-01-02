//engine includes
#include "GameManager.h"
#include "logManager.h"
#include "Clock.h"
#include "Manager.h"
#include "ObjectList.h"
#include "WorldManager.h"
#include "EventStep.h"
#include "DisplayManager.h"
#include "InputManager.h"
#include "ResourceManager.h"

#include <Windows.h>

namespace df {

	//sets type and instantiates attributes
	GameManager::GameManager()
	{
		setType("Game Manager");

		//game is not over
		game_over = false;

		//to run at approx. 30 fps
		frame_time = 33;

		m_step_count = 0;
	}

	//instantiates and starts up all other managers
	//returns 1 if successful, 0 otherwise
	int GameManager::startUp()
	{
		LM.writeLog("\nGAME MANAGER STARTED");
		timeBeginPeriod(1);
		LM.startUp();
		WM.startUp();
		DM.startUp();
		IM.startUp();
		RM.startUp();

		WM.setBoundary(df::Box(df::Vector(), DM.getHorizontal(), DM.getVertical()));
		
		//called once all other managers started up successfully
		df::Manager::startUp();
		return 1;

	}

	//sets gameOver and shuts down all managers
	void GameManager::shutDown()
	{
		LM.writeLog("\nGAME MANAGER SHUT DOWN");
		setGameOver(true);

		//shut down log manager and world manager
		RM.shutDown();
		IM.shutDown();
		DM.shutDown();
		WM.shutDown();
		LM.shutDown();

		//called once shut down successfully
		df::Manager::shutDown();
		timeEndPeriod(1);
	}

	//runs the main game loop
	//currently not fully functional, only has loop with clock methods implemented
	void GameManager::run()
	{
		df::Clock* clk = new df::Clock;
		//testing with 300 iterations of loop
		//30 fps = 10 seconds to run all iterations
		int test_loop = 300;
		while (game_over == false && test_loop > 0)
		{
			clk->delta();
			//Send step event to all objects
			df::EventStep s = df::EventStep(m_step_count);
			onEvent(&s);
			//Get input
			IM.getInput();
			//update game state
			WM.update();
			//Draw current scene to back buffer
			WM.draw();
			//Swap back buffer to current buffer
			DM.swapBuffers();
			
			long int loop_time = clk->split();
			LM.writeLog("\nLOOP TIME: %d", loop_time);
			if (loop_time < frame_time)
			{
				Sleep(frame_time - loop_time);
			}
			//LM.writeLog("\nFINISHED LOOP");
			test_loop--;
		}
		
	}

	//returns the only instance of the game manager
	GameManager& GameManager::getInstance()
	{
		static GameManager single;
		return single;
	}

	//sets variable game_over to inputted value
	void GameManager::setGameOver(bool new_game_over)
	{
		game_over = new_game_over;
	}

	//returns game_over private variable
	bool GameManager::getGameOver() const
	{
		return game_over;
	}

	//returns frame_time private variable
	int GameManager::getFrameTime() const
	{
		return frame_time;
	}
}