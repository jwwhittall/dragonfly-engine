#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::cout;
using std::endl;

#include "ResourceManager.h"
#include "logManager.h"

namespace df {

	ResourceManager::ResourceManager() {

		setType("ResourceManager");
		m_sprite_count = 0;
	}

	//return only instance of RM
	ResourceManager& df::ResourceManager::getInstance()
	{
		static ResourceManager single;
		return single;
	}

	//initialize sprite count and start up base manager
	int ResourceManager::startUp()
	{
		m_sprite_count = 0;
		music_count = 0;
		sound_count = 0;
		return Manager::startUp();
	}

	void ResourceManager::shutDown()
	{
		//iterate through all sprites
		for (int i = 0; i < m_sprite_count - 1; i++)
		{
			//sprite not null? delete it
			if (m_p_sprite[i] != NULL)
			{
				delete m_p_sprite[i];
			}
		}
		//set sprite count to zero and call base manager shut down
		m_sprite_count = 0;
		Manager::shutDown();
	}

	//Load sprite from file
	//Assign indicated label to sprite
	//Return 0 if ok, else -1
	int ResourceManager::loadSprite(std::string filename, std::string label)
	{
		//Check if room in array
		if (m_sprite_count == MAX_SPRITES) {
			LM.writeLog("\nRM.loadsprite= no room in sprite array!");
			return -1;
		}

		std::string line;
		std::ifstream myfile(filename);
		std::vector<std::string> data;

		//array of ints for frames, width, height, and slowdown
		//0 -> FRAMES
		//1 -> WIDTH
		//2 -> HEIGHT
		//3 -> SLOWDOWN
		int attr[4];
		df::Color c;

		//open sprite file
		if (myfile.is_open()) {

			//loop through four times, for each int attribute
			for (int i = 0; i < 4; i++)
			{
				//check if file can be read
				if (myfile.good()) {
					getline(myfile, line);
					data.push_back(line);
					if (line.length() > 1)
					{
						LM.writeLog("\nRM.loadfile- line length greater than 1! line: %s, sprite: %s", line.c_str(), filename.c_str());
						return -1;
					}
					attr[i] = atoi(line.c_str());
					if (attr[i] < 0) {
						LM.writeLog("\nRM.loadsprite- attribute less than zero!");
						return -1;
					}
				}
			}

			if (myfile.good())
			{
				//read color, check for each string, and save
				getline(myfile, line);
				data.push_back(line);
				if (line == "black") c = df::BLACK;
				else if (line == "red") c = df::RED;
				else if (line == "green") c = df::GREEN;
				else if (line == "yellow") c = df::YELLOW;
				else if (line == "blue") c = df::BLUE;
				else if (line == "magenta") c = df::MAGENTA;
				else if (line == "cyan") c = df::CYAN;
				else if (line == "white") c = df::WHITE;
				else { //color not recognized? set to default and log warning
					c = df::COLOR_DEFAULT;
					LM.writeLog("\nRM.loadsprite - color in sprite file unrecognized!");
				}
			}
		}
		else { //file did not load
			LM.writeLog("\nRM.loadsprite- sprite file not loading!");
			return -1;
		}

		//create sprite with first int in array as max frames
		df::Sprite* sprite = new Sprite(attr[0]);
		//set attributes to saved input from file
		sprite->setWidth(attr[1]);
		sprite->setHeight(attr[2]);
		sprite->setSlowdown(attr[3]);
		sprite->setColor(c);

		//Read and add frames to sprite
		for (int i = 0; i < attr[0]; i++)
		{
			//create new string
			std::string str = "";
			//for each line in the file,
			for (int h = 0; h < attr[2]; h++)
			{
				if (myfile.good())
				{
					//append the line to the static string
					getline(myfile, line);
					data.push_back(line);
					if (line.length() != attr[1])
					{
						LM.writeLog("\nRM.loadsprite- sprite width unequal to given parameter!\n"
							"width: % d, line: %s, filename: %s", attr[1], line.c_str(), filename.c_str());
						return -1;
					}
					str.append(line);
				}
				else {
					LM.writeLog("\nRM.loadsprite- file bad!");
					return -1;
				}
				
			}
			//create a frame with the same width and height as the sprite
			//and string with the new string appended 
			Frame f = Frame(attr[1], attr[2], str);
			sprite->addFrame(f);
		}

		if (myfile.good()) {
			LM.writeLog("\nRM.loadsprite- more lines in sprite file than specified in parameters!");
			return -1;
		}

		//close file
		myfile.close();
	
		//give sprite label
		sprite->setLabel(label);
		//add sprite to array in RM and increment sprite count
		m_p_sprite[m_sprite_count] = sprite;
		m_sprite_count++;
		return 0;
	}

	//Unload sprite with indicated label
	//Return 0 if ok, else -1
	int ResourceManager::unloadSprite(std::string label)
	{
		//iterate through all sprites
		for (int i = 0; i < m_sprite_count; i++)
		{
			//does label match?
			if (label == m_p_sprite[i]->getLabel())
			{
				//delete the current sprite
				delete m_p_sprite[i];

				//scoot others over
				for (int j = i; j < m_sprite_count - 1; j++) {
					m_p_sprite[j] = m_p_sprite[j + 1];
				}

				m_sprite_count--;
				return 0;

			}
		}
		LM.writeLog("\nRM.unloadSprite- sprite not found!");
		return -1;
	}

	//Find sprite with indicated label
	//Return ptr if found, else NULL
	Sprite* ResourceManager::getSprite(std::string label) const
	{
		for (int i = 0; i < m_sprite_count; i++)
		{
			if (label == m_p_sprite[i]->getLabel())
			{
				return m_p_sprite[i];
			}
		}
		LM.writeLog("\nRM.getsprite- sprite not found, returning null");
		return NULL;

	}

	//load sound from file
	int ResourceManager::loadSound(std::string filename, std::string label)
	{
		if (sound_count == MAX_SOUNDS)
		{
			LM.writeLog("\nSound array full)");
			return -1;
		}
		if (sound[sound_count].loadSound(filename) == -1)
		{
			LM.writeLog("Unable to load from file");
			return -1;
		}

		sound[sound_count].setLabel(label);
		sound_count++;
		return 0;
	}

	//removes sound with given label from array
	int ResourceManager::unloadSound(std::string label)
	{
		for (int i = 0; i < sound_count - 1; i++)
		{
			if (label == sound[i].getLabel())
			{
				//scoot over remaining
				for (int j = i; j < sound_count - 2; j++)
				{
					sound[j] = sound[j + 1];
				}
				sound_count--;
				return 0;
			}
		}
		return -1; // not found
	}

	//returns sound with given label
	Sound* ResourceManager::getSound(std::string label)
	{
		for (int i = 0; i < sound_count; i++)
		{
			if (sound[i].getLabel() == label)
			{
				return &sound[i];
			}
		}
		return nullptr;
	}

	//load music with given label and filename into array
	int ResourceManager::loadMusic(std::string filename, std::string label)
	{
		if (music_count == MAX_MUSICS)
		{
			LM.writeLog("\nSound array full)");
			return -1;
		}
		if (music[music_count].loadMusic(filename) == -1)
		{
			LM.writeLog("Unable to load from file");
			return -1;
		}

		music[music_count].setLabel(label);
		music_count++;
		return 0;
	}

	//remove music with given label from array
	int ResourceManager::unloadMusic(std::string label)
	{
		for (int i = 0; i < sound_count - 1; i++)
		{
			if (label == sound[i].getLabel())
			{
				sound[i].setLabel("");
				sound_count--;
				return 0;
			}
		}
		return -1; // not found
	}

	//return music with given label
	Music* ResourceManager::getMusic(std::string label)
	{
		for (int i = 0; i < music_count; i++)
		{
			if (music[i].getLabel() == label)
			{
				return &music[i];
			}
		}
		return nullptr;
	}

}