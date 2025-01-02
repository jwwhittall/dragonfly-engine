#pragma once

#include "Manager.h"
#include "ObjectList.h"

namespace df {

	const int MAX_ALTITUDE = 4;

	#define WM df::WorldManager::getInstance()

	class WorldManager : public Manager {

	private:
		WorldManager(); // singleton
		//don't allow copy
		WorldManager(WorldManager const&);
		//don't allow assignment
		void operator = (WorldManager const&);

		//all objects in world to update
		ObjectList m_updates;
		//all objects in world to delete
		ObjectList m_deletions;

		//World boundary
		Box boundary;
		//Player view of game world
		Box view;

		//Object view is following
		Object* p_view_following;

	public:
		//Get the one and only instance of the WorldManager
		static WorldManager& getInstance();

		//Startup game world(initialize everything to empty)
		//Return 0
		int startUp();

		//Shutdown game world (delete all game world objects)
		void shutDown();

		//Insert object into world, return 0 if ok, else -1
		int insertObject(Object* p_o);

		//remove object from world. return 0 if ok, else -1
		int removeObject(Object* p_o);

		//Return list of all objects in world
		ObjectList getAllObjects() const;

		//Return list of all objects in world matching type
		ObjectList objectsOfType(std::string type) const;

		//Update world
		//Delete objects marked for deletion
		void update();

		//Indicate object is to be deleted at end of current game loop
		//Return 0 if ok, else -1
		int markForDelete(Object* p_o);

		void draw();

		//Return list of objects collided with at position 'where'
		//Collisions only with solid objects
		//Does not consider if p_o is solid or not
		ObjectList getCollisions(const Object* p_o, Vector where) const;

		//Move object
		//If collision with solid, send collision events
		//If no collision with solid, move ok else don't move object
		//If object is spectral, move ok
		//Return 0 if move ok, else -1 if collision with solid
		int moveObject(Object* p_o, Vector where);

		//Set game world boundary
		void setBoundary(Box new_boundary);

		//Get game world boundary
		Box getBoundary() const;

		//Set player view of game world
		void setView(Box new_view);

		//Get player view of game world
		Box getView() const;

		//Set view to center window on position view_pos
		//View edge will not go beyond world boundary
		void setViewPosition(df::Vector view_pos);

		//Set view to center window on object
		//Set to NULL to stop following
		//If p_new_view_following not legit, return -1 else return 0
		int setViewFollowing(Object* p_new_view_following);

	};

}
