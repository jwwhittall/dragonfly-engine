#pragma once

namespace df {

	class Vector {

	private:
		float m_x; //horizontal component
		float m_y; //vertical component

	public:

		//create vector with (x,y)
		Vector(float init_x, float init_y);

		//Default 2d (x,y) is (0,0)
		Vector();

		//Get/set horizontal component
		void setX(float new_x);
		float getX() const;

		//Get/set vertical component
		void setY(float new_y);
		float getY() const;

		//Set horizontal & vertical components
		void setXY(float new_x, float new_y);

		//Return magnitude of vector
		float getMagnitude() const;

		//Normalize vector
		void normalize();

		//Scale vector
		void scale(float s);

		//Add two Vectors, return new vector
		Vector operator+(const Vector& other) const;
	};

}
