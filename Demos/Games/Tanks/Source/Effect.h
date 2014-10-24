/************************************************************************/
/* @class Effect
 * @author Jack McCallum
 * 
 * @description
 * Base class for all simple visual effects,
 * An effect must have a manager, to automatically call update,
 * the manager can listen to frame events
 * 
/************************************************************************/

#pragma once

#include "EffectsManager.h"

class Effect
{
public:
	Effect(EffectsManager* mgr);
	~Effect();

	// Update animations/positions/color etc
	virtual void update() = 0;

protected:
	EffectsManager* manager;
	float animate;
	bool deleteMe;
};

