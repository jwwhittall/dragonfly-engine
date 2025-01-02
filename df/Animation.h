#pragma once

//System includes
#include <string>

//Engine includes
#include "Sprite.h"
#include "Box.h"

namespace df {

	class Animation {

	private:
		//Sprite associated with animation
		Sprite* m_p_sprite;
		//Sprite name in RM
		std::string m_name;
		//Current index frame for sprite
		int m_index;
		//Slowdown counter
		int m_slowdown_count;

	public:
		//Animation constructor
		Animation();

		//Set associated sprite to new one
		//Note, sprite is managed by RM
		//Set sprite index to 0 (first frame)
		void setSprite(Sprite* p_new_sprite);

		//Return pointer to associated sprite
		Sprite* getSprite() const;

		//Set sprite name (in RM)
		void setName(std::string new_name);

		//Get sprite name (in RM)
		std::string getName() const;

		//Set index of current sprite frame to be displayed
		void setIndex(int new_index);

		//Get index of current sprite frame to be displayed
		int getIndex() const;

		//Set animation slowdown count (-1 means stop animation)
		void setSlowdownCount(int new_slowdown_count);

		//Set animation slowdown count (-1 means stop animation)
		int getSlowdownCount() const;

		//Draw single frame centered at position (x,y)
		//Drawing accounts for slowdown, and advances sprite frame
		//Return 0 if ok, else -1
		int draw(Vector position);

		Box getBox() const;
	};


}