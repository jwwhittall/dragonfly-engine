#include "Object.h"
#include "WorldManager.h"
#include "logManager.h"
#include "ResourceManager.h"
#include "Box.h"

namespace df {

	static int ID = 0;

	//intializes attributes, sets ID to next available int
	df::Object::Object()
	{
		m_id = ID;
		ID++;

		//type is set empty, position is set 0 (default vector)
		m_type = "";
		m_position = Vector();
		m_speed = 0;
		m_direction = df::Vector();

		//add self to game world
		LM.writeLog("\nObject() added to world ID: %d", m_id);
		WM.insertObject(this);

		m_altitude = MAX_ALTITUDE / 2;

		m_solidness = HARD;

		m_animation = df::Animation();

		m_box = df::Box(df::Vector(), 1, 1);
	}

	//destroy & remove from world manager
	df::Object::~Object()
	{
		LM.writeLog("\n~Object deleted from world ID: %d", m_id);
		WM.removeObject(this);
	}

	//sets ID to given value
	void df::Object::setId(int new_id)
	{
		m_id = new_id;
	}

	//returns ID value
	int df::Object::getId() const
	{
		return m_id;
	}

	//sets type to given string
	void df::Object::setType(std::string new_type)
	{
		m_type = new_type;
	}

	//returns type
	std::string df::Object::getType() const
	{
		return m_type;
	}

	//sets position to given vector
	void df::Object::setPosition(Vector new_pos)
	{
		m_position = new_pos;
		LM.writeLog("\nSET POSITION OBJ ID %d x: %f, y: %f", getId(), new_pos.getX(), new_pos.getY());
	}

	//returns position
	Vector df::Object::getPosition() const
	{
		return m_position;
	}

	//event handler at base class does nothing
	int Object::eventHandler(const Event* p_e)
	{
		return 0;
	}

	//base draw does nothing
	int Object::draw()
	{
		df::Vector pos = getPosition();
		return m_animation.draw(pos);
	}

	//sets altitude to new value, first checks to make sure between 0 and 4
	int Object::setAltitude(int new_altitude)
	{
		if (new_altitude <= 4 && new_altitude >= 0)
		{
			m_altitude = new_altitude;
			return 0;
		}
		return -1;
	}

	//returns value of altitude
	int Object::getAltitude() const
	{
		return m_altitude;
	}

	//sets the speed of the object
	void Object::setSpeed(float speed)
	{
		m_speed = speed;
	}

	//returns the speed of the object
	float Object::getSpeed() const
	{
		return m_speed;
	}

	//sets the direction of the object
	void Object::setDirection(Vector new_direction)
	{
		m_direction = new_direction;
	}

	//returns direction of the object
	Vector Object::getDirection() const
	{
		return m_direction;
	}


	void Object::setVelocity(Vector new_velocity)
	{
		m_speed = new_velocity.getMagnitude();
		new_velocity.normalize();
		m_direction = new_velocity;
	}

	df::Vector Object::getVelocity() const
	{
		df::Vector d = m_direction;
		d.scale(m_speed);
		return d;
	}

	//Predict object position based on speed and direction
	//Return predicted position
	df::Vector Object::predictPosition()
	{
		//Add velocity to position
		Vector new_pos = m_position + getVelocity();

		//Return new position
		return new_pos;
	}

	//returns true if solidness set to hard or soft
	//false if spectral
	bool Object::isSolid() const
	{
		if (m_solidness == HARD || m_solidness == SOFT)
		{
			return true;
		}
		return false;
	}

	//sets the solidness of the object
	int Object::setSolidness(Solidness new_solid)
	{
		m_solidness = new_solid;
		return 0;
	}

	//returns solidness of object
	Solidness Object::getSolidness() const
	{
		return m_solidness;
	}

	//sets the sprite of the object given its label
	int Object::setSprite(std::string sprite_label)
	{
		//get sprite with matching label from RM
		df::Sprite* p_sprite = RM.getSprite(sprite_label);
		if (p_sprite == NULL) //null sprite? throw error
		{
			LM.writeLog("\nObject.setSprite(): sprite %s is null!", sprite_label.c_str());
			return -1;
		}
		//set animation
		m_animation.setSprite(p_sprite);
		//give object box based on sprite size
		setBox(m_animation.getBox());

		return 0;
	}

	//set animation to given val
	void Object::setAnimation(Animation new_animation)
	{
		m_animation = new_animation;
	}

	//returns animation
	Animation Object::getAnimation() const
	{
		return m_animation;
	}

	//set the slowdown count of the attached animation
	void Object::setSlowdownCount(int new_slow)
	{
		m_animation.setSlowdownCount(new_slow);
	}

	//set the box of the object
	void Object::setBox(Box new_box)
	{
		m_box = new_box;
	}
	
	//return the box attached to object
	Box Object::getBox() const
	{
		return m_box;
	}


}
