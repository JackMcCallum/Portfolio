/************************************************************************/
/* @class JMRay
 * @author Jack McCallum
 * 
 * @description
 * Ray collision
 * 
/************************************************************************/

#pragma once

class JMRay
{
public:
	JMRay();
	JMRay(float ox, float oy, float tx, float ty);

	// Gets a point on the ray where pos 0 is the origin and 1 is the target
	void getPointOnRay(float pos, float& px, float& py);

public:
	// Public access for optimizations
	float originx, originy;
	float targetx, targety;
};

