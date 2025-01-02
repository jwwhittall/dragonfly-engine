#pragma once

#include "Vector.h"
#include "Box.h"
#include "Object.h"

namespace df {

	class Utility {

	public:

		bool positionsIntersect(df::Vector p1, df::Vector p2);

		bool boxIntersectsBox(Box A, Box B);

		Box getWorldBox(const Object* p_o);

		Box getWorldBox(const Object* p_o, df::Vector where);

		Vector worldToView(df::Vector world_pos);

	};

}
