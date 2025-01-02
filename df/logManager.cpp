#define _CRT_SECURE_NO_WARNINGS

//engine includes
#include "logManager.h"

//to support multi-argument methods
//system includes
#include <stdarg.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

namespace df {

	//pointer to .txt log file
	FILE* logFile;

	//constructor, sets type to log manager and calls startup() to create logfile
	logManager::logManager()
	{
		setType("Log Manager");
	}

	//checks to make sure logfile was created. if so, calls shutdown()
	logManager::~logManager()
	{
		if (logFile != NULL)
		{
			shutDown();
		}
	}

	//called by constructor. opens log file and checks to make sure it was created successfully
	int logManager::startUp()
	{
		logFile = fopen("dragonfly.log", "w");
		if (logFile == NULL) return 0; //was the logfile created? if not, return 0
		else return 1; //logfile successfully created
	}

	//called by destructor. closes logfile
	void logManager::shutDown() {
		LM.writeLog("\LOG MANAGER SHUT DOWN");
		fclose(logFile);
	}

	//sets m_do_flush to the input value, to control whether output immediately gets flushed or not
	void logManager::setFlush(bool do_flush)
	{
		m_do_flush = do_flush;
	}

	//Return the one and only instance of the class
	logManager& logManager::getInstance()
	{
		static logManager single;
		return single;
	}

	//returns number of bytes
	//writes given message (parameters) to file logFile
	int logManager::writeLog(const char* fmt, ...)
	{
		va_list args;
		va_start(args, fmt);
		int numbytes = vfprintf(logFile, fmt, args);
		va_end(args);
		//if flush is set to true, immediately write to disk
		if (m_do_flush) fflush(logFile);

		return numbytes;
	}
}