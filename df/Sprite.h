#pragma once

//System includes
#include <string>

//Engine includes
#include "Frame.h"

namespace df {

	class Sprite {

	private:
		//Sprite width
		int m_width;
		//Sprite height
		int m_height;
		//Max num frames sprite can have
		int m_max_frame_count;
		//Actual number frames sprite has
		int m_frame_count;
		//Optional color for entire sprite
		Color m_color;
		//Animation slowdown (1=no slowdown, 0=stop)
		int m_slowdown;
		//Array of frames
		Frame* m_frame;
		//Text label to identify sprite
		std::string m_label;
		//Sprite always has one arg, the frame count
		Sprite();

	public:
		//Destroy sprite, deleting any allocated frames
		~Sprite();

		//Create sprite with indicated max num frames
		Sprite(int max_frames);

		//Set width of sprite
		void setWidth(int new_width);

		//Get width of sprite
		int getWidth() const;

		//Set height of sprite
		void setHeight(int new_height);

		//Get height of sprite
		int getHeight() const;

		//Set sprite color
		void setColor(Color new_color);

		//Get sprite color
		Color getColor() const;

		//Get total count of frames in sprite
		int getFrameCount() const;

		//Add frame to sprite
		//Return -1 if frame array full, else 0
		int addFrame(Frame new_frame);

		//Get next sprite frame indicated by number
		//Return empty frame if out of range[0, m_frame_count-1]
		Frame getFrame(int frame_number) const;

		//set label associated with sprite
		void setLabel(std::string new_label);

		//Get label associated with sprite
		std::string getLabel() const;

		//Set animation slowdown value
		//Value in multiples of GM frame time
		void setSlowdown(int new_sprite_slowdown);

		//Get animation slowdown value
		//Value in multiples of GM frame time
		int getSlowdown() const;

		//Draw indicated frame centered at pos (x,y)
		//Return 0 if ok, else -1
		int draw(int frame_number, Vector position) const;
	};

}