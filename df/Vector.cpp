#include "Vector.h"
#include <stdlib.h>
#include <corecrt_math.h>

namespace df {

	//constructs vector with given x and y values
	df::Vector::Vector(float init_x, float init_y)
	{
		m_x = init_x;
		m_y = init_y;
	}

	//constructs vector with default 0 values for x and y
	df::Vector::Vector()
	{
		m_x = 0;
		m_y = 0;
	}

	//sets x to given value
	void df::Vector::setX(float new_x)
	{
		m_x = new_x;
	}
	
	//returns x value of vector
	float df::Vector::getX() const
	{
		return m_x;
	}

	//sets y to given value
	void df::Vector::setY(float new_y)
	{
		m_y = new_y;
	}

	//returns y value of vector
	float df::Vector::getY() const
	{
		return m_y;
	}

	//sets x and y values of vector to given values
	void df::Vector::setXY(float new_x, float new_y)
	{
		m_x = new_x;
		m_y = new_y;
	}

	//Return magnitude of vector
	float df::Vector::getMagnitude() const
	{
		float mag = sqrt(m_x * m_x + m_y * m_y);
		return mag;
	}

	//changes the length of any vector to 1
	void df::Vector::normalize()
	{
		float length = getMagnitude();
		//make sure not dividing by zero
		if (length > 0)
		{
			m_x = m_x / length;
			m_y = m_y / length;
		}
	}

	//Scales vector by desired factor s
	void df::Vector::scale(float s)
	{
		m_x = m_x * s;
		m_y = m_y * s;
	}

	//Add two vectors, return new vector
	Vector df::Vector::operator+(const Vector& other) const
	{
		//create new vector
		Vector v;
		//add x components, then y components
		v.m_x = m_x + other.m_x;
		v.m_y = m_y + other.m_y;
		//return new vector with added components
		return v;
	}
}
