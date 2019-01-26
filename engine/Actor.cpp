
#ifndef ACTOR_CPP
#define ACTOR_CPP

#include "Actor.h"
#include "Map.h"

std::string Actor::GetName() const
{
	return this->name;
}

bool Actor::SetPos( const Vector & loc )
{
	if( this->map )
	{
		Vector temp = this->pos;
		this->pos = loc;
		if( this->IsWalkable() || this->map->IsSpaceWalkable( this->GetAABBmin(), this->GetAABBmax(), {this} ) )
		{
			this->map->UpdateActor( this );
			return true;
		}
		this->pos = temp;
	}
	return false;
}

bool Actor::Move( const Vector & move )
{
	return this->SetPos( this->pos + move );
}

Vector Actor::GetPos() const
{
	return this->pos;
}

Vector Actor::GetSize() const
{
	return this->size;
}

Vector Actor::GetAABBmin() const
{
	return this->pos;
}

Vector Actor::GetAABBmax() const
{
	return this->pos + this->size - Vector(1,1);
}

bool Actor::InBounds( const Vector & min, const Vector & max ) const
{
	return Vector::BoundInBound( this->GetAABBmin(), this->GetAABBmax(), min, max );
}

void Actor::Save( std::ofstream & file ) const
{
	if( file.good() )
	{
		file << this->name << " ";
		file << this->pos.x << " ";
		file << this->pos.y << " ";
		file << this->size.x << " ";
		file << this->size.y << " ";
	}
}

void Actor::Load( std::ifstream & file )
{
	if( file.good() )
	{
		file >> this->name;
		file >> this->pos.x;
		file >> this->pos.y;
		file >> this->size.x;
		file >> this->size.y;
	}
}

void Actor::Spawn( const std::string & name, const Vector & pos, const Vector & size )
{
	this->pos = pos;
	this->size = size;
	this->name = name;
}

void Actor::Despawn()
{
	this->name = "";
}

void Actor::Init( Map * map )
{
	this->map = map;
}

void Actor::Deinit()
{
	this->map = nullptr;
}


Actor::Actor() :
	map(nullptr)
{
}

Actor::~Actor()
{
	this->map = nullptr;
}

#endif

