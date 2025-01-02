#include "Animation.h"
#include "logManager.h"

namespace df {


	df::Animation::Animation()
	{
		m_p_sprite = NULL;
		m_name = "";
		m_index = 0;
		m_slowdown_count = 0;
	}

	//set associated sprite to given sprite
	//set index to 0
	//TODO: set bounding box here
	void df::Animation::setSprite(Sprite* p_new_sprite)
	{
		m_p_sprite = p_new_sprite;
		m_index = 0;
	}

	//returns associated sprite
	Sprite* Animation::getSprite() const
	{
		return m_p_sprite;
	}

	//set name of sprite to given value
	void Animation::setName(std::string new_name)
	{
		m_name = new_name;
	}

	//returns name of associated sprite
	std::string Animation::getName() const
	{
		return m_name;
	}

	//sets index to new val
	void Animation::setIndex(int new_index)
	{
		m_index = new_index;
	}

	//returns index of sprite
	int Animation::getIndex() const
	{
		return m_index;
	}

	//sets slowdown to given value
	void Animation::setSlowdownCount(int new_slowdown_count)
	{
		m_slowdown_count = new_slowdown_count;
	}

	//returns slowdown value
	int Animation::getSlowdownCount() const
	{
		return m_slowdown_count;
	}


	//draws single frame centered at position
	int Animation::draw(Vector position)
	{
		//If sprite not defined, don't continue further
		if (m_p_sprite == NULL)
		{
			LM.writeLog("\nAnimation.draw- sprite not defined!");
			return -1;
		}

		//Ask sprite to draw current frame
		m_index = getIndex();
		m_p_sprite->draw(m_index, position);

		//If slowdown count is -1, then animation is frozen
		if (getSlowdownCount() == -1)
		{
			LM.writeLog("\nAnimation.draw- animation is frozen!");
			return -1;
		}

		//Increment counter
		int count = getSlowdownCount();
		count++;
		//LM.writeLog("\ncount = %d, slowdown = %d", count, m_slowdown_count);

		//Advance sprite index, if appropriate
		if (count >= m_p_sprite->getSlowdown())
		{
			count = 0;
			m_index++;
			//LM.writeLog("\ncount = %d, slowdown = %d", count, m_slowdown_count);

			//If at last frame, loop to beginning
			if (m_index >= m_p_sprite->getFrameCount())
			{
				m_index = 0;
			}

			//Set index for next draw()
			setIndex(m_index);
		}
		//set counter for next draw()
		setSlowdownCount(count);
	}

	//get bounding box of associated sprite
	Box Animation::getBox() const
	{
		//If no sprite, return until box centered at (0,0)
		if (m_p_sprite == NULL)
		{
			Box box(Vector(-0.5, -0.5), 0.99, 0.99);
			return box;
		}

		//Create box around centered sprite
		Vector corner(-1 * m_p_sprite->getWidth() / 2.0,
			-1 * m_p_sprite->getHeight() / 2.0);
		Box box(corner, m_p_sprite->getWidth(), m_p_sprite->getHeight());

		return box;
	}

}