#pragma once

//system includes
#include <string>

//Engine includes
#include "Vector.h"
#include "Event.h"
#include "Animation.h"

namespace df {

	enum Solidness {
		HARD,     //Object causes collisions and impedes
		SOFT,     //Object causes collisions, but doesn't impede
		SPECTRAL, //Object doesn't cause collisions
	};

	class Object {

	private:
		//Unique game engine defined id
		int m_id; 
		//Game programmer defined type
		std::string m_type; 
		//Position in game world
		Vector m_position;
		//0 to MAX supported (lower drawn first)
		int m_altitude;
		//Direction vector
		Vector m_direction;
		//Object speed in direction
		float m_speed;
		//Solidness of object
		Solidness m_solidness;
		//Animation associated with object
		Animation m_animation;
		//Box for sprite boundary & collisions
		Box m_box;

	public:
		//Construct object. set default parameters and
		//add to game world (world manager)
		Object();

		//Destroy ovject, remove from world manager
		virtual ~Object();

		//set object id
		void setId(int new_id);

		//get object id
		int getId() const;

		//set type identifier of object
		void setType(std::string new_type);

		//get type identifier of object
		std::string getType() const;

		//set position of object
		void setPosition(Vector new_pos);

		//get position of object
		Vector getPosition() const;

		virtual int eventHandler(const Event* p_e);

		//Draw object animation
		//Return 0 if ok, else -1
		virtual int draw();

		//Set altitude of Object, with checks for range [0, MAX_ALTITUDE]
		//Return 0 if ok, else -1
		int setAltitude(int new_altitude);

		//Return altitude of object
		int getAltitude() const;

		//Set speed of object
		void setSpeed(float speed);

		//Get speed of object
		float getSpeed() const;

		//Set direction of object
		void setDirection(Vector new_direction);

		//Get direction of object
		Vector getDirection() const;

		//Set direction and speed of object
		void setVelocity(Vector new_velocity);

		//Get velocity of object based on direction + speed
		Vector getVelocity() const;

		//Predict object position based on speed + direction
		//Return predicted position
		Vector predictPosition();

		//True if HARD or SOFT, else false
		bool isSolid() const;

		//Set object solidness, with checks for consistency
		//Return 0 if ok, else -1
		int setSolidness(Solidness new_solid);

		//Return object solidness
		Solidness getSolidness() const;

		//Set sprite for this object to animate
		//Return 0 if ok, else -1
		int setSprite(std::string sprite_label);

		//Set animation for this object to new one
		//Set bounding box to size of associated sprite
		void setAnimation(Animation new_animation);
		
		//Get animation for this object
		Animation getAnimation() const;

		void setSlowdownCount(int new_slow);

		//Set object's bounding box
		void setBox(Box new_box);

		//Get object's bounding box
		Box getBox() const;
	};

}