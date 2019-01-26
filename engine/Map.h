
#ifndef MAP_H
#define MAP_H

#include <map>
#include <vector>
#include <set>

#include "Vector.hpp"

#include "Actor.h"

class Map
{
private:
	
	struct Box
	{
		Vector min;
		Vector max;
		Actor * actor;
	};
	
	std::map < loctype, std::map < loctype, std::set<Box*> > > spaceMin;
	
	std::map < Actor*, Box* > actors;
	
	class World * world;
	
public:
	
	class World * GetWorld();
	void SetWorld( class World * world );
	
	void AddActor( Actor * actor );
	void RemoveActor( Actor * actor );
	
	void UpdateActor( Actor * actor );
	
	void GetActors( const Vector & min, const Vector & max, const std::set<Actor*> & ignoreActors, std::set<Actor*> & ret );
	bool IsSpaceWalkable( const Vector & min, const Vector & max, const std::set<Actor*> & ignoreActors = std::set<Actor*>() );
	
	void Clear();
	
	Map();
	~Map();
};

#endif

