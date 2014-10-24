/************************************************************************/
/* @class EffectsManager
 * @author Jack McCallum
 * 
 * @description
 * Effect manager handlers visual effects, keeps them updated so they can animate
 * 
/************************************************************************/

#pragma once
#include "JMFrameEventHandler.h"

class Effect;

class EffectsManager : JMFrameEventListener
{
public:
	EffectsManager(JMFrameEventHandler* frameHndl = NULL);
	~EffectsManager();

	// Add/remove effetcts
	void addEffect(Effect* fx);
	void removeEffect(Effect* fx);

	// Update all effects
	void updateEffects();
	
	// Destroy all effects
	void destroyAllEffects();

	// Automatic updating
	virtual void eventPreRender(const JMFrameEvent &evt);

private:
	std::list<Effect*> effectList;
	
	// Frame handler
	JMFrameEventHandler* frameHandler;
};

