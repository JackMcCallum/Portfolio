/************************************************************************/
/* @class JMShape
 * @author Jack McCallum
 * 
 * @description
 * Shape collision, shapes can be either circle or rectangle,
 * which can be checked if they intersect with each other
 * rays can be intersected with either shape
 * 
/************************************************************************/

#pragma once

class JMRay;

class JMShape
{
public:
	// Returns true if this intersects with s
	virtual bool intersects(JMShape* s) = 0;
	// Calculate the push vector as well
	virtual bool intersects(JMShape* s, float& xx, float& yy) = 0;
	// Calculate position from which a ray intersects
	virtual bool intersects(JMRay* s, float& pos) = 0;

	// Move the shape in 2D
	virtual void translate(float xx, float yy) = 0;

	// Set the position of the shape in 2D
	virtual void position(float xx, float yy) = 0;

};

