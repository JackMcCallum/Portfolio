#include "StdAfx.h"
#include "Effect.h"

Effect::Effect(EffectsManager* mgr)
{
	manager = mgr;
	manager->addEffect(this);
	animate = 0;
}

Effect::~Effect()
{
	manager->removeEffect(this);
}

