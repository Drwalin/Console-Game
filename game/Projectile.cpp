
#ifndef PROJECTILE_CPP
#define PROJECTILE_CPP

#include "Projectile.h"
#include "Character.hpp"

void Projectile::SetVelocity( Vector direction, unsigned velocity, int timeToDespawn )
{
	this->direction = direction;
	this->velocity = velocity;
	this->timeToDespawn = clock() + timeToDespawn;
}

bool Projectile::IsWalkable() const
{
	return true;
}

bool Projectile::NeedTick() const
{
	return true;
}

void Projectile::Draw( unsigned currentSecond, class Drawer * drawer )
{
	Vector delta( 0, 0 );
	if( this->changedPositionBy.x != 0 )
		delta.x = this->changedPositionBy.x < 0 ? 1 : -1;
	else if( this->changedPositionBy.y != 0 )
		delta.y = this->changedPositionBy.y < 0 ? 1 : -1;
	
	for( Vector beg = this->changedPositionBy; ; beg += delta )
	{
		if( this->direction.x != 0 )
			drawer->Draw( beg, '-', FOREGROUND_RED | FOREGROUND_INTENSITY );
		else
			drawer->Draw( beg, '|', FOREGROUND_RED | FOREGROUND_INTENSITY );
		
		if( beg == Vector(0,0) )
			break;
	}
	
	this->changedPositionBy = Vector( 0, 0 );
}

unsigned Projectile::Tick()
{
	if( this->timeToDespawn <= clock() )
	{
		this->world->QueueRemoveActor( this->GetName() );
	}
	
	std::set<Actor*> targets;
	this->world->GetMap()->GetActors( this->GetPos(), this->GetPos(), {this}, targets );
	for( auto it = targets.begin(); it != targets.end(); ++it )
	{
		if( (*it)->IsWalkable() == false )
		{
			this->world->QueueRemoveActor( this->GetName() );
			Character * ch = dynamic_cast<Character*>(*it);
			if( ch != nullptr )
			{
				ch->DamageAbsorb( 31.1f );
			}
		}
	}
	
	this->Move( this->direction );
	this->changedPositionBy -= this->direction;
	
	return 1000/this->velocity;
}

void Projectile::Save( std::ofstream & file ) const
{
	Actor::Save( file );
	
	file << this->direction.x << " ";
	file << this->direction.y << " ";
	
	file << this->velocity << " ";
	file << this->timeToDespawn << " ";
	
	file << this->changedPositionBy.x << " ";
	file << this->changedPositionBy.y << " ";
}

void Projectile::Load( std::ifstream & file )
{
	Actor::Load( file );
	
	file >> this->direction.x;
	file >> this->direction.y;
	
	file >> this->velocity;
	
	file >> this->changedPositionBy.x;
	file >> this->changedPositionBy.y;
}

void Projectile::Spawn( const std::string & name, const Vector & pos, const Vector & size )
{
	Actor::Spawn( name, pos, size );
	this->direction = Vector( 1, 0 );
	this->velocity = 7;
	this->timeToDespawn = clock() + 1000;
	this->changedPositionBy = Vector(0,0);
}

void Projectile::Despawn()
{
}

void Projectile::Init( class World * world )
{
	Actor::Init( world );
}

void Projectile::Deinit()
{
	Actor::Deinit();
}


std::string Projectile::GetTypeName()
{
	return "Projectile";
}

Actor * Projectile::Make()
{
	return Allocate<Projectile>();
}

Projectile::~Projectile()
{
}

Projectile::Projectile()
{
}

#endif

