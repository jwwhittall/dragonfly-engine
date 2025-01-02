#pragma once
//inheret from manager
#include "Manager.h"

//to support multi-argument methods
#include <stdarg.h>
#include <stdio.h>

#define LM df::logManager::getInstance()

namespace df {

	const std::string LOGFILE_NAME = "dragonfly.log";

	class logManager : public Manager {

	private:
		//Pointer to file to write to
		FILE* logFile;

		bool m_do_flush; //true if fflush after each write

		//Singleton methods
		logManager();
		logManager(logManager const& copy);
		void operator=(logManager const& assign);

	public:
		~logManager();

		//Singleton method 
		static logManager& getInstance();

		//writes logs to file or console 
		//Return number of bytes written, -1 if error
		int writeLog(const char* fmt, ...);

		//Start up the LogManager (open logfile "dragonfly.log")
		int startUp();

		//Shut down the LogManager (close logfile)
		void shutDown();

		//Set flush of logfile after each write
		void setFlush(bool do_flush = true);

	};

}
