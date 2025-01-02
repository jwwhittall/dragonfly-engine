#include "Sprite.h"
#include "logmanager.h"

namespace df {

	//deallocates data
	df::Sprite::~Sprite()
	{
		if (m_frame != NULL)
		{
			delete[] m_frame;
		}
	}

	//constructs sprite with max frame count
	df::Sprite::Sprite(int max_frames)
	{
		m_frame_count = 0;
		m_width = 0;
		m_height = 0;
		m_slowdown = 0;
		m_label = "";
		m_frame = new Frame[max_frames];
		m_max_frame_count = max_frames;
		m_color = df::COLOR_DEFAULT;
	}

	//sets width to given value
	void df::Sprite::setWidth(int new_width)
	{
		m_width = new_width;
	}

	//returns width of sprite
	int df::Sprite::getWidth() const
	{
		return m_width;
	}

	//sets height to given value
	void df::Sprite::setHeight(int new_height)
	{
		m_height = new_height;
	}

	//returns height of sprite
	int df::Sprite::getHeight() const
	{
		return m_height;
	}

	//sets color of sprite
	void df::Sprite::setColor(Color new_color)
	{
		m_color = new_color;
	}

	//returns color of sprite
	Color df::Sprite::getColor() const
	{
		return m_color;
	}

	//returns number of frames in sprite
	int df::Sprite::getFrameCount() const
	{
		return m_frame_count;
	}

	//adds frame to sprite
	int df::Sprite::addFrame(Frame new_frame)
	{
		//is the sprite full?
		if (m_frame_count == m_max_frame_count)
		{
			LM.writeLog("\nsprite.addframe- adding frame to full sprite!");
			return -1;
		}
		//sprite not full! add frame
		m_frame[m_frame_count] = new_frame;
		m_frame_count++; //increment frame count
		return 0;
	}

	//returns sprite frame indicated by number
	//Return empty frame if out of range
	Frame Sprite::getFrame(int frame_number) const
	{
		if ((frame_number < 0) || frame_number >= m_frame_count)
		{
			df::Frame f = Frame();
			return f;
		}
		return m_frame[frame_number];
	}

	//sets label to given string
	void Sprite::setLabel(std::string new_label)
	{
		m_label = new_label;
	}

	//returns label
	std::string Sprite::getLabel() const
	{
		return m_label;
	}

	//sets slowdown to given int
	void Sprite::setSlowdown(int new_sprite_slowdown)
	{
		m_slowdown = new_sprite_slowdown;
	}

	//returns sprite slowdown
	int Sprite::getSlowdown() const
	{
		return m_slowdown;
	}

	//draws given frame of sprite in given location
	int Sprite::draw(int frame_number, Vector position) const
	{
		if (frame_number > m_frame_count)
		{
			LM.writeLog("\nsprite.draw- trying to draw frame out of bounds!");
			return -1;
		}
		m_frame[frame_number].draw(position, m_color);
		return 0;
	}
}