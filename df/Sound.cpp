#include "Sound.h"
#include "logManager.h"

namespace df {

	df::Sound::Sound()
	{
	}

	Sound::~Sound()
	{
		m_sound.resetBuffer();
	}

	//loads sound of given file name
	int Sound::loadSound(std::string filename)
	{
		if (m_sound_buffer.loadFromFile(filename) == false)
		{
			LM.writeLog("\nsound.loadsound- load failed!");
			return -1;
		}
		m_sound.setBuffer(m_sound_buffer);
		return 0;
	}

	//sets string label
	void Sound::setLabel(std::string new_label)
	{
		m_label = new_label;
	}

	//returns label
	std::string Sound::getLabel() const
	{
		return m_label;
	}

	//plays sound, loops if true
	void Sound::play(bool loop)
	{
		m_sound.play();
		m_sound.setLoop(loop);
	}

	//stops sound
	void Sound::stop()
	{
		m_sound.stop();
	}

	//pauses sound
	void Sound::pause()
	{
		m_sound.pause();
	}

	//returns sound
	sf::Sound Sound::getSound() const
	{
		return m_sound;
	}
}