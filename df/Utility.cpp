#include "Utility.h"
#include "WorldManager.h"
#include <corecrt_math.h>
#include <cmath>

namespace df {

	//checks if two vector positions of objects interect with each other
	bool df::Utility::positionsIntersect(df::Vector p1, df::Vector p2)
	{
		if (abs(p1.getX() - p2.getX()) <= 1 &&
			abs(p1.getY() - p2.getY()) <= 1)
		{
			return true;
		}
		else return false;
	}

	bool Utility::boxIntersectsBox(Box A, Box B)
	{
		//Test horizontal overlap (x_overlap)

		//Left side of A in B?
		bool x_overlap1 = (B.getCorner().getX() <= A.getCorner().getX()
			&& A.getCorner().getX() <= B.getCorner().getX() + B.getHorizontal());

		//left side of B in A?
		bool x_overlap2 = (A.getCorner().getX() <= B.getCorner().getX()
			&& B.getCorner().getX() <= A.getCorner().getX() + A.getHorizontal());

		//combine in or statement for all x overlap
		bool x_overlap = x_overlap1 || x_overlap2;

		//Test vertical overlap

		//top side of A in B?
		bool y_overlap1 = B.getCorner().getY() <= A.getCorner().getY()
			&& A.getCorner().getY() <= B.getCorner().getY() + B.getVertical();

		//ttop side of B in A?
		bool y_overlap2 = A.getCorner().getY() <= B.getCorner().getY()
			&& B.getCorner().getY() <= A.getCorner().getY() + A.getVertical();

		bool y_overlap = y_overlap1 || y_overlap2;

		if (x_overlap && y_overlap)
		{
			return true; //boxes intersect
		}
		else return false; //boxes do not intersect
	}

	//convert relative bounding box for object to absolute world box
	Box Utility::getWorldBox(const Object* p_o)
	{
		return getWorldBox(p_o, p_o->getPosition());
	}

	Box Utility::getWorldBox(const Object* p_o, df::Vector where)
	{
		Box box = p_o->getBox();
		Vector corner = box.getCorner();
		corner.setX(corner.getX() + where.getX());
		corner.setY(corner.getY() + where.getY());
		box.setCorner(corner);
		return box;
	}

	Vector Utility::worldToView(df::Vector world_pos)
	{
		df::Vector view_origin = WM.getView().getCorner();
		int view_x = view_origin.getX();
		int view_y = view_origin.getY();
		df::Vector view_pos(world_pos.getX() - view_x, world_pos.getY() - view_y);
		return view_pos;
	}





}




