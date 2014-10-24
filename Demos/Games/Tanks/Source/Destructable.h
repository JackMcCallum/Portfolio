/************************************************************************/
/* @class Destructable
 * @author Jack McCallum
 * 
 * @description
 * Very simple class for giving an class a simple hit points system
 * 
/************************************************************************/

#pragma once

class Destructable
{
public:
	Destructable(float hp = 100.0f);

	// Health alterations
	void damage(float hp);
	void heal(float hp);
	void setHitPonts(float hp);

	// Get health
	float getHitPoints();
	float& getHitPointsAddress();

	// When health < 0
	virtual void destroyed();

private:
	float hitPoints;
	bool isDestroyed;
};

