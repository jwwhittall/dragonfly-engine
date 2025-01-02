#pragma once

//System includes
#include <string>

//Engine includes
#include "Manager.h"
#include "Sprite.h"
#include "Sound.h"
#include "Music.h"

#define RM df::ResourceManager::getInstance()

namespace df {

	//Maximum number of unique assets in game
	const int MAX_SPRITES = 500;
	const int MAX_SOUNDS = 50;
	const int MAX_MUSICS = 50;

	class ResourceManager : public Manager {

	private:
		//singleton private methods
		ResourceManager();
		ResourceManager(ResourceManager const&);
		void operator=(ResourceManager const&);
		//Array of sprites
		Sprite* m_p_sprite[MAX_SPRITES];
		//Count of number of loaded sprites
		int m_sprite_count; 
		//Array of sound buffers
		Sound sound[MAX_SOUNDS];
		//Count of num loaded sounds
		int sound_count;
		//Array of music buffers
		Music music[MAX_MUSICS];
		//count of loaded musics
		int music_count;

	public:
		//Get the one and only instance of the RM
		static ResourceManager& getInstance();

		//Get RM ready to manager for resources
		int startUp();

		//Shut down RM, free up allocated sprites
		void shutDown();

		//Load sprite from file
		//Assign indicated label to sprite
		//Return 0 if ok, else -1
		int loadSprite(std::string filename, std::string label);


		//Unload sprite with indicated label
		//Return 0 if ok, else -1
		int unloadSprite(std::string label);

		//Find sprite with indicated label
		//Return ptr to it if found, else NULL
		Sprite* getSprite(std::string label) const;

		//Load sound from file
		int loadSound(std::string filename, std::string label);

		//Remove sound with indicated label
		int unloadSound(std::string label);

		//Find sound with indicated label
		//Return ptr else null
		Sound* getSound(std::string label);

		//Associate file with music
		int loadMusic(std::string filename, std::string label);

		//Remove label for music with indicated label
		int unloadMusic(std::string label);

		//Find music with indicated lbel
		//Return ptr else null
		Music* getMusic(std::string label);

	};



}