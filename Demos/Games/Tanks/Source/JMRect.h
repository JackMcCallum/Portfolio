/************************************************************************/
/* @class JMRect
 * @author Jack McCallum
 * 
 * @description
 * Rectangular collision
 * 
/************************************************************************/

#pragma once

#include "JMShape.h"

 class JMRect : public JMShape
{
public:
	JMRect(float w, float h);
	JMRect(float t, float l, float b, float r);

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
	float top, bottom, left, right;

private:
	// Keep track of the origin so we can easily set the position later
	// Upon creation origin is always 0,0
	float originx, originy;


};

