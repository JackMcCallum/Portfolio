/************************************************************************/
/* @class JMCircle
 * @author Jack McCallum
 * 
 * @description
 * Circle collision
 * 
/************************************************************************/

#pragma once

#include "JMShape.h"

class JMCircle : public JMShape
{
public:
	JMCircle(float rad);
	JMCircle(float x, float y, float rad);

	// Returns true if this intersects with s
	virtual bool intersects(JMShape* s);
	// Calculate the push vector as well
	virtual bool intersects(JMShape* s, float& xx, float& yy);
	// Calculate position from which a ray intersects
	virtual bool intersects(JMRay* s, float& pos);

	// Move the shape in 2D
	virtual void translate(float xx, float yy);

	// Set the position of the shape in 2D
	virtual void position(float xx, float yy);


public:
	// Public access for optimization reasons
	float originx, originy, radius;


};

