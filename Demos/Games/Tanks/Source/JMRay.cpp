#include "StdAfx.h"
#include "JMRay.h"


JMRay::JMRay()
{
	originx = 0;
	originy = 0;
	targetx = 0;
	targety = 0;
}

JMRay::JMRay(float ox, float oy, float tx, float ty)
{
	originx = ox;
	originy = oy;
	targetx = tx;
	targety = ty;
}

void JMRay::getPointOnRay(float pos, float& px, float& py)
{
	px = originx + (targetx-originx) * pos;
	py = originy + (targety-originy) * pos;
}
