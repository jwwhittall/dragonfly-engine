#include "WorldManager.h"
#include "Manager.h"
#include "logManager.h"
#include "Utility.h"
#include "EventCollision.h"
#include "DisplayManager.h"
#include "EventOut.h"
#include "Box.h"

namespace df {

	//constructor sets type to "World Manager"
	WorldManager::WorldManager()
	{
		setType("World Manager");
	}

	//returns one and only instance of world manager (singleton)
	WorldManager& df::WorldManager::getInstance()
	{
		static WorldManager single;
		return single;
	}

	//clears all lists of objects, calls base manager startup method
	int WorldManager::startUp()
	{
		LM.writeLog("\WORLD MANAGER STARTED");
		m_updates.clear();
		m_deletions.clear();
		Manager::startUp();
		view = df::Box(df::Vector(), DM.getHorizontal(), DM.getVertical());
		boundary = df::Box(df::Vector(), DM.getHorizontal(), DM.getVertical());
		return 0;
	}

	//iterates through list of all objects in world, and deletes each
	void WorldManager::shutDown()
	{
		LM.writeLog("\WORLD MANAGER STARTED");
		ObjectList ol = m_updates;
		ObjectListIterator li = ObjectListIterator(&ol);

		for (li.first(); !li.isDone(); li.next())
		{
			delete li.currentObejct();
		}
	}

	//adds an object to the world by adding it to list of updates
	int WorldManager::insertObject(Object* p_o)
	{
		return(m_updates.insert(p_o));
	}

	//removes object from world by removing from updates list
	int WorldManager::removeObject(Object* p_o)
	{
		if (m_updates.remove(p_o) == -1) {
			LM.writeLog("\nWM.removeObject: failure to remove object from m_updates");
			return 0;
		}
		return 1;
		
	}

	//returns list of all objects in world
	ObjectList WorldManager::getAllObjects() const
	{
		return m_updates;
	}

	//returns all objects of given type in a list
	ObjectList WorldManager::objectsOfType(std::string type) const
	{
		//create new list to store objects of right type in
		df::ObjectList list = df::ObjectList();
		//create new iterator to go through list of all objects in world
		df::ObjectListIterator li = df::ObjectListIterator(&m_updates);

		//loop through all objects in world until reaching the end of the list
		for (li.first(); !li.isDone(); li.next()) 
		{
			//does the current object have the desired type?
			if (li.currentObejct()->getType() == type)
			{
				//if so, add it to the new list
				list.insert(li.currentObejct());
			}
		}
		//return created list
		return list;
	}

	//deletes all objects marked for deletion by programmer in the current step
	void WorldManager::update()
	{
		//create an iterator that will go through all objects to be deleted
		df::ObjectListIterator li = df::ObjectListIterator(&m_deletions);

		//while the iterator hasn't reached the end of the list, delete the current object and continue iterating
		while (!li.isDone())
		{
			delete li.currentObejct();
			li.next();
		}
		this->m_deletions.clear();

		//iterate through all objects
		df::ObjectListIterator i = df::ObjectListIterator(&m_updates);

		while (!i.isDone())
		{
			df::Object* o = i.currentObejct();
			//add velocity to position
			df::Vector new_pos = o->predictPosition();

			//If object should change position, then move
			if (new_pos.getX() != o->getPosition().getX() || new_pos.getY() != o->getPosition().getY())
			{
				moveObject(o, new_pos);
			}
			i.next();
		}
	}

	//adds given object to list of deletions, to be deleted in update()
	int WorldManager::markForDelete(Object* p_o)
	{
		return(m_deletions.insert(p_o));
	}

	void WorldManager::draw()
	{
		ObjectListIterator li = ObjectListIterator(&m_updates);
		df::Utility u = df::Utility();
		df::Box temp_box;

		for (int i = 0; i <= df::MAX_ALTITUDE; i++)
		{
			while (!li.isDone())
			{
				if (li.currentObejct()->getAltitude() == i)
				{
					Object* p_temp_o = li.currentObejct();
					//Bounding box coordinates are relative to ojbect,
					//So convert to world coordinates
					temp_box = u.getWorldBox(p_temp_o);
					//Only draw if object would be visible on window (intersects view)
					if (u.boxIntersectsBox(temp_box, view))
					{
						LM.writeLog("\nObject ID: %d drawn!", p_temp_o->getId());
						p_temp_o->draw();
					}
				}
				li.next();
			}
			li.first();
		}
	}

	//Return list of objects collided with at position 'where'
		//Collisions only with solid objects
		//Does not consider if p_o is solid or not
	ObjectList WorldManager::getCollisions(const Object* p_o, Vector where) const
	{
		//Make empty list
		df::ObjectList collision_list;

		df::Utility u = df::Utility();

		df::ObjectListIterator i = df::ObjectListIterator(&m_updates);

		//World position bounding box for object at where
		df::Box b = u.getWorldBox(p_o, where);

		int count = 0;
		while (!i.isDone())
		{
			Object* p_temp_o = i.currentObejct();
			//World position bounding box for other object
			Box b_temp = u.getWorldBox(p_temp_o);

			if (p_temp_o != p_o) //Do not consider self
			{
				//Same location and both solid?
				if (u.boxIntersectsBox(b, b_temp) && p_temp_o->isSolid())
				{
					LM.writeLog("\nWM.getCollisions- objects intersect");
					if (p_temp_o->isSolid())
					{
						LM.writeLog("\nWM.getCollisions- other object is solid");
						collision_list.insert(p_temp_o);
						count++;
					}
				} //No solid collision

			} //Not self
			i.next();
		}

		LM.writeLog("\nWM.getCollisions- %d collisions found", count);
		return collision_list;
	}


	//Move object
	//If collision with solid, send collision events
	//If no collision with solid, move ok else don't move object
	//If object is spectral, move ok
	//Return 0 if move ok, else -1 if collision with solid
	int WorldManager::moveObject(Object* p_o, Vector where)
	{
		if (p_o->isSolid()) //Need to be solid for collisions
		{
			LM.writeLog("\nWM.moveObject- object %d is solid", p_o->getId());
			//Get collisions
			ObjectList list = getCollisions(p_o, where);

			if (!list.isEmpty())
			{
				//LM.writeLog("\nWM.moveobject - object %d has collisions", p_o->getId());
				bool do_move = true; //assume can move

				//Iterate over list
				df::ObjectListIterator li = df::ObjectListIterator(&list);

				while (!li.isDone())
				{
					Object* p_temp_o = li.currentObejct();

					//Create collision event
					EventCollision c = EventCollision(p_o, p_temp_o, where);
					LM.writeLog("\nWM.moveObject- object %d collided with %d", p_o->getId(), p_temp_o->getId());

					//Send to both objects
					p_o->eventHandler(&c);
					p_temp_o->eventHandler(&c);

					//If both HARD, then cannot move
					if (p_o->getSolidness() == HARD &&
						p_temp_o->getSolidness() == HARD)
					{
						do_move = false;
					}
					li.next();
				}
				if (do_move == false)
				{
					return -1; //Move not allowed
				}
			} //No collision

		} //Object not solid
		df::Utility u = df::Utility();

		//original bounding box
		Box orig_box = u.getWorldBox(p_o);
		//new bounding box
		Box new_box = u.getWorldBox(p_o);


		//If object moved from inside to outside world, generate out of bounds event
		if (u.boxIntersectsBox(orig_box, boundary) && //was in bounds?
			!u.boxIntersectsBox(new_box, boundary)) //now out of bounds?
		{
			EventOut ov;
			p_o->eventHandler(&ov);
		}

		//If here, no collision between two HARD objects so allow move
		p_o->setPosition(where);
		LM.writeLog("\nWM.moveObject- object %d moved to x: %f, y %f", p_o->getId(), where.getX(), where.getY());

		//If view is following this object, adjust view
		if (p_view_following == p_o)
		{
			setViewPosition(p_o->getPosition());
		}
		return 0;
	}

	//set world boundary
	void WorldManager::setBoundary(Box new_boundary)
	{
		boundary = new_boundary;
	}

	//return world boundary
	Box WorldManager::getBoundary() const
	{
		return boundary;
	}

	//set view box
	void WorldManager::setView(Box new_view)
	{
		view = new_view;
	}

	//return view box
	Box WorldManager::getView() const
	{
		return view;
	}

	//Set view to center window on position view_pos
	//View edge will not go beyond world boundary
	void WorldManager::setViewPosition(df::Vector view_pos)
	{
		LM.writeLog("\nWM.setViewPos setting view to %f, %f", view_pos.getX(), view_pos.getY());

		//Make sure horizontal not out of world boundary
		float x = view_pos.getX() - view.getHorizontal() / 2;
		if (x + view.getHorizontal() > boundary.getHorizontal())
		{
			x = boundary.getHorizontal() - view.getHorizontal();
		}
		if (x < 0) x = 0;

		//Make sure vertical not out of world boundary
		float y = view_pos.getY() - view.getVertical() / 2;
		if (y + view.getVertical() > boundary.getVertical())
		{
			y = boundary.getVertical() - view.getVertical();
		}
		if (y < 0) y = 0;

		//Set view
		Vector new_corner(x, y);
		LM.writeLog("\nView corner set to %d, %d", x, y);
		view.setCorner(new_corner);
	}

	//Set view to center window on object
	//Set to NULL to stop following
	//If p_new_view_following not legit, return -1 else return 0
	int WorldManager::setViewFollowing(Object* p_new_view_following)
	{
		//Set to NULL to turn 'off' following
		if (p_new_view_following == NULL)
		{
			p_view_following = NULL;
			return 0;
		}

		//Iterate over all objects. Make sure p_new_view_following
		//is one of the objects, then set found to true
		
		ObjectListIterator li = df::ObjectListIterator(&m_updates);
		bool found = false;

		while (!li.isDone())
		{
			if (li.currentObejct()->getId() == p_new_view_following->getId())
			{
				found = true;
				break;
			}
			li.next();
		}

		//If found, adjust attribute accordingly and set view position
		if (found)
		{
			p_view_following = p_new_view_following;
			setViewPosition(p_view_following->getPosition());
			return 0;
		}

		LM.writeLog("WM.setViewFollowing- object not in world! Illegitimate!");
		return -1;

	}

}