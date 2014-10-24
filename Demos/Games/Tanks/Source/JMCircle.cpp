#include "StdAfx.h"
#include "JMCircle.h"
#include "JMRect.h"
#include "MathsMacros.h"
#include "JMRay.h"

JMCircle::JMCircle(float rad)
{
	originx = 0;
	originy = 0;
	radius = rad;
}

JMCircle::JMCircle(float x, float y, float rad)
{
	originx = x;
	originy = y;
	radius = rad;
}

bool JMCircle::intersects(JMShape* s)
{
	if (typeid(*s) == typeid(JMCircle))
	{
		JMCircle* circ = (JMCircle*)s;
		float xdif = originx-circ->originx;
		float ydif = originy-circ->originy;
		float dist = Sqr(xdif) + Sqr(ydif);
		float d = (circ->radius+radius);
		if (dist < Sqr(d))
			// Success
			return true;
	}
	if (typeid(*s) == typeid(JMRect))
	{
		return s->intersects(this);
	}
	// Unsuccessful
	return false;
}

bool JMCircle::intersects(JMShape* s, float& xx, float& yy)
{
	xx = 0;
	yy = 0;

	if (typeid(*s) == typeid(JMCircle))
	{
		JMCircle* circ = (JMCircle*)s;

		// Direction vector
		float dirx = circ->originx-originx;
		float diry = circ->originy-originy;

		// Length of it
		float dist = (Sqr(dirx) + Sqr(diry));
		float d = (circ->radius+radius);
		
		// If its at 0,0 relative to the other circle
		// It will never push apart so nudge it a little to side
		if (dist == 0)
		{
			xx = 0.1f;
			yy = 0;
			// Successful
			return true;
		}
		else if (dist < Sqr(d))
		{
			dist = Sqrt(dist);
			// Distance the circle needs to be pushed away
			float pushdist = radius+circ->radius-dist;

			// Normal
			xx = (dirx/dist) * pushdist;
			yy = (diry/dist) * pushdist;

			return true;

		}
		
		// Unsuccessful
		return false;
	}
	else if (typeid(*s) == typeid(JMRect))
	{
		if (s->intersects(this, xx, yy))
		{
			xx = -xx;
			yy = -yy;
			// Successful
			return true;
		}
		// Unsuccessful
		return false;
	}
	// Failure?
	return false;
}

bool JMCircle::intersects(JMRay* s, float& pos)
{
	pos = 0;

	// Ive made my custom algorithm out of 2 different ones i found on google,
	// a simplified one that does not find the point of intersection is used as a
	// broad phase, then a more complex one is used when we are certain that theres a good chance
	// of an intersection. i don't think its going to get any faster than this

	// Get data
	float ox, oy, tx, ty;
	ox = s->originx;
	oy = s->originy;
	tx = s->targetx;
	ty = s->targety;

	// Ray vector
	float dirx, diry;
	dirx = tx-ox;
	diry = ty-oy;

	// Vector from circle origin to ray origin
	float cirx, ciry;
	cirx = originx-ox;
	ciry = originy-oy;

	// Broad phase check,
	// Some data here used in narrow phase
	float pd, a, b, sr;
	a = Sqr(dirx) + Sqr(diry);
	b = Dot(dirx,diry,cirx,ciry);
	sr = Sqr(radius);
	pd = (b / a);
	
	if (Sqr(cirx-pd*dirx) + Sqr(ciry-pd*diry) < sr)
	{
		// Google majick
		float c, d;
		b *= 2;
		c = Sqr(cirx) + Sqr(ciry) - sr;
		d = b*b-4*a*c;

		if (d > 0)
		{
			float t = (b-Sqrt(d)) / (2*a);
			if (t > 0)
			{
				pos = t;
				// Success
				return true;
			}
		}
	}
	// Unsuccessful
	return false;
}

void JMCircle::translate(float xx, float yy)
{
	originx += xx;
	originy += yy;
}

void JMCircle::position(float xx, float yy)
{
	originx = xx;
	originy = yy;
}
