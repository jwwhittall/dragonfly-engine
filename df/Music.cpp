#include "Music.h"
#include "logManager.h"

namespace df {

	df::Music::Music()
	{

	}

	int df::Music::loadMusic(std::string filename)
	{
		if (m_music.openFromFile(filename) == false)
		{
			LM.writeLog("\nsound.loadsound- load failed!");
			return -1;
		}
		return 0;
	}

	void df::Music::setLabel(std::string new_label)
	{
		m_label = new_label;
	}

	std::string df::Music::getLabel() const
	{
		return m_label;
	}

	void df::Music::play(bool loop)
	{
		m_music.play();
		m_music.setLoop(loop);
	}

	void df::Music::stop()
	{
		m_music.stop();
	}

	void df::Music::pause()
	{
		m_music.pause();
	}


}