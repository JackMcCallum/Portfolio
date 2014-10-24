#include "StdAfx.h"
#include "EffectsManager.h"
#include "Effect.h"

// ------------------------------------------------------------------------------------------------------------
EffectsManager::EffectsManager(JMFrameEventHandler* frameHndl)
{
	frameHandler = frameHndl;

	// If given a frame handler, add it
	if (frameHandler)
		frameHandler->addListener((JMFrameEventListener*)this);
}
// ------------------------------------------------------------------------------------------------------------
EffectsManager::~EffectsManager()
{
	// If given a frame handler, remove it
	if (frameHandler)
		frameHandler->removeListener((JMFrameEventListener*)this);
}
// ------------------------------------------------------------------------------------------------------------
void EffectsManager::addEffect(Effect* fx)
{
	effectList.push_back(fx);
}
// ------------------------------------------------------------------------------------------------------------
void EffectsManager::removeEffect(Effect* fx)
{
	effectList.remove(fx);
}
// ------------------------------------------------------------------------------------------------------------
void EffectsManager::updateEffects()
{
	// Update all child effects of this manager
	std::list<Effect*>::iterator effectIter = effectList.begin();
	while (effectIter != effectList.end())
		(*effectIter++)->update();
}
// ------------------------------------------------------------------------------------------------------------
void EffectsManager::destroyAllEffects()
{
	// Destroy all effects
	std::list<Effect*>::iterator effectIter = effectList.begin();
	while (effectIter != effectList.end())
		delete (*effectIter++);
	effectList.clear();
}
// ------------------------------------------------------------------------------------------------------------
void EffectsManager::eventPreRender( const JMFrameEvent &evt )
{
	updateEffects();
}
// ------------------------------------------------------------------------------------------------------------