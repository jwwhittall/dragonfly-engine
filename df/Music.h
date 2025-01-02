#pragma once

//System includes
#include <string>
#include <SFML/Audio.hpp>

namespace df {

	class Music {

	private:
		Music(Music const&); //don't allow music copy
		void operator=(Music const&); //no music assignment
		sf::Music m_music; //the SFML music
		std::string m_label; //text label to id


	public:
		Music();

		//Associate music buffer with file
		//Return 0 if ok, else -1
		int loadMusic(std::string filename);

		//Set label associated with music
		void setLabel(std::string new_label);

		//Get label associated
		std::string getLabel() const;

		//Play music, loop if true
		void play(bool loop = true);

		//Stop music
		void stop();

		//Pause music
		void pause();

		//Return pointer to SFML music
		sf::Music* getMusic();

	};

}