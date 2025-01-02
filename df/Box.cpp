#include "Box.h"

namespace df {

	//Create box with (0,0) for the corner, and 0 for horiz and vert
	df::Box::Box()
	{
		m_corner = df::Vector(0,0);
		m_vertical = 0;
		m_horizontal = 0;
	}

	//Create box with an upper-left corner, horiz and vert sizes
	Box::Box(Vector init_corner, float init_horizontal, float init_vertical)
	{
		m_corner = init_corner;
		m_vertical = init_vertical;
		m_horizontal = init_horizontal;
	}

	//Set upper left corner of box
	void Box::setCorner(Vector new_corner)
	{
		m_corner = new_corner;
	}

	//Get upper left corner of box
	Vector Box::getCorner() const
	{
		return m_corner;
	}

	//set horizontal dimension
	void Box::setHorizontal(float new_horizontal)
	{
		m_horizontal = new_horizontal;
	}

	//get horizontal dimension
	float Box::getHorizontal() const
	{
		return m_horizontal;
	}

	//set vertical dimension
	void Box::setVertical(float new_vertical)
	{
		m_vertical = new_vertical;
	}

	//get vertical dimension
	float df::Box::getVertical() const
	{
		return m_vertical;
	}

}