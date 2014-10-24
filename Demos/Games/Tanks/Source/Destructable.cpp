#include "StdAfx.h"
#include "Destructable.h"

// ------------------------------------------------------------------------------------------------------------
Destructable::Destructable(float hp)
{
	hitPoints = hp;
	isDestroyed = false;
}
// ------------------------------------------------------------------------------------------------------------
void Destructable::damage(float hp)
{
	hitPoints -= hp;
	if (hitPoints <= 0 && !isDestroyed)
	{
		destroyed();
		isDestroyed = true;
	}
}
// ------------------------------------------------------------------------------------------------------------
void Destructable::heal(float hp)
{
	hitPoints += hp;
	if (hitPoints <= 0 && !isDestroyed)
	{
		destroyed();
		isDestroyed = true;
	}
}
// ------------------------------------------------------------------------------------------------------------
void Destructable::setHitPonts(float hp)
{
	hitPoints = hp;
	if (hitPoints <= 0 && !isDestroyed)
	{
		destroyed();
		isDestroyed = true;
	}
}
// ------------------------------------------------------------------------------------------------------------
float Destructable::getHitPoints()
{
	return hitPoints;
}
// ------------------------------------------------------------------------------------------------------------
float& Destructable::getHitPointsAddress()
{
	return hitPoints;
}
// ------------------------------------------------------------------------------------------------------------
void Destructable::destroyed()
{
	// Do nothing
}
// ------------------------------------------------------------------------------------------------------------