#include "StdAfx.h"
#include "JMCircle.h"
#include "JMRect.h"
#include "MathsMacros.h"
#include "JMRay.h"

JMRect::JMRect(float w, float h)
{
	top = -h/2.0f;
	bottom = h/2.0f;
	left = -w/2.0f;
	right = w/2.0f;
	originx = 0;
	originy = 0;
}

JMRect::JMRect(float t, float l, float b, float r)
{
	top = t;
	left = l;
	bottom = b;
	right = r;
	originx = 0;
	originy = 0;
}

bool JMRect::intersects(JMShape* s)
{
	if (typeid(*s) == typeid(JMCircle))
	{
		
		JMCircle* circ = (JMCircle*)s;

		float x = circ->originx;
		float y = circ->originy;
		float rad = circ->radius;

		// Broad phase
		if (x > left-rad && x < right+rad && y > top-rad && y < bottom+rad)
		{
			float xl, xr, yt, yb;
			// Differences
			xl = x-left;
			xr = x-right;
			yt = y-top;
			yb = y-bottom;
			// Squared differences
			xl *= xl;
			xr *= xr;
			yt *= yt;
			yb *= yb;

			// Squared radius
			float radSqr = rad*rad;

			// Narrow phase
			if ((x+rad > left && x-rad < right && y > top && y < bottom) ||
				(x > left && x < right && y+rad > top && y-rad < bottom) ||
				(xl + yt <= radSqr) ||
				(xr + yt <= radSqr) ||
				(xl + yb <= radSqr) ||
				(xr + yb <= radSqr))
				return true;
		}
	}
	else if (typeid(*s) == typeid(JMRect))
	{
		// Rectangle/Rectangle intersection
		JMRect* rect = (JMRect*)s;
		if (bottom > rect->top && right > rect->left && top < rect->bottom && left < rect->right)
			return true;
	}
	return false;
}

bool JMRect::intersects(JMShape* s, float& xx, float& yy)
{
	xx = 0;
	yy = 0;

	if (typeid(*s) == typeid(JMCircle))
	{
		JMCircle* circ = (JMCircle*)s;

		float x = circ->originx;
		float y = circ->originy;
		float rad = circ->radius;

		if (x > left-rad && x < right+rad && y > top-rad && y < bottom+rad)
		{
			//return true;
			// Check what area the origin of the sphere is in
			float xdif, ydif, dist;

			// Checking if origin is withing 2 rectangles, one vertical and one horizontal
			// by doing this we're not checking the corners
			if ((x+rad > left && x-rad < right && y > top && y < bottom) ||
				(x > left && x < right && y+rad > top && y-rad < bottom))
			{
				// Okay, we know it intersect, now
				// Lets calculate the smallest vector it should move to not intersect
				float v1, v2, xo, yo;
				v1 = left-rad-x;
				v2 = right+rad-x;

				// First calculate if its faster to go up than it is to go down
				if (Abs(v1) < Abs(v2))
					xo = v1;
				else
					xo = v2;

				v1 = top-rad-y;
				v2 = bottom+rad-y;
				
				// Now calculate if its faster to go left than it is to go right
				if (Abs(v1) < Abs(v2))
					yo = v1;
				else
					yo = v2;

				// Now pick its faster to go vertical than it is to go horizontal
				if (Abs(yo) < Abs(xo))
					yy = yo;
				else
					xx = xo;

				return true;
			}
			// Top left
			else if (y < top && x < left)
			{
				// Ill explain this once...
				// Vector from circle origin, to corner of rectangle
				xdif = x-left;
				ydif = y-top;
				// Check squared distance
				dist = Sqr(xdif) + Sqr(ydif);
				if (dist < Sqr(rad))
				{
					// If it is within range, We only need to calculate 
					// the push vector then return true;
					// If not we need to keep calculating
					dist = Sqrt(dist);
					// Take the squared distance then change the vector to the 
					// length we need which is radius - distance
					xx = (xdif/dist)*(rad-dist);
					yy = (ydif/dist)*(rad-dist);
					return true;
				}
			}
			// Top left
			else if (y < top && x > right)
			{
				xdif = x-right;
				ydif = y-top;
				dist = Sqr(xdif) + Sqr(ydif);
				if (dist < Sqr(rad))
				{
					dist = Sqrt(dist);
					xx = (xdif/dist)*(rad-dist);
					yy = (ydif/dist)*(rad-dist);
					return true;
				}
			}
			// Bottom left
			else if (y > bottom && x < left)
			{
				xdif = x-left;
				ydif = y-bottom;
				dist = Sqr(xdif) + Sqr(ydif);
				if (dist < Sqr(rad))
				{
					dist = Sqrt(dist);
					xx = (xdif/dist)*(rad-dist);
					yy = (ydif/dist)*(rad-dist);
					return true;
				}
			}
			// Bottom right
			else if (y > bottom && x > right)
			{
				xdif = x-right;
				ydif = y-bottom;
				dist = Sqr(xdif) + Sqr(ydif);
				if (dist < Sqr(rad))
				{
					dist = Sqrt(dist);
					xx = (xdif/dist)*(rad-dist);
					yy = (ydif/dist)*(rad-dist);
					return true;
				}
			}
			
			return false;
		}
	}
	else if (typeid(*s) == typeid(JMRect))
	{
		JMRect* rect = (JMRect*)s;
		float t, l, b, r;
		t = rect->top;
		l = rect->left;
		b = rect->bottom;
		r = rect->right;

		if (bottom > t && right > l && top < b && left < r)
		{
			// Okay, we know it intersect, now
			// Lets calculate the smallest vector it should move to not intersect
			float v1, v2, xo, yo;

			// First calculate if its faster to go up than it is to go down
			v1 = bottom-t;
			v2 = top-b;

			if (Abs(v1) < Abs(v2))
				yo = v1;
			else
				yo = v2;

			// Now calculate if its faster to go left than it is to go right
			v1 = right-l;
			v2 = left-r;

			if (Abs(v1) < Abs(v2))
				xo = v1;
			else
				xo = v2;

			// Now pick its faster to go vertical than it is to go horizontal
			if (Abs(xo) < Abs(yo))
				xx = xo;
			else
				yy = yo;

			// Return successful
			return true;
		}
		// Unsuccessful
		return false;
	}	
	// Failure?
	return false;
}

bool JMRect::intersects(JMRay* s, float& pos)
{
	pos = 0;

	float ox, oy, tx, ty;
	ox = s->originx;
	oy = s->originy;
	tx = s->targetx;
	ty = s->targety;

	float dirx, diry;
	dirx = tx-ox;
	diry = ty-oy;

	float h, t, ft = 0;
	
	// Checking vertical sides
	// Check left side
	if (dirx > 0)
	{
		t = (left-ox)/dirx;
		h = oy+diry*t;
		if (h < bottom && h > top)
			ft = t;
	}
	// Check right side
	else if (dirx < 0)
	{
		t = (right-ox)/dirx;
		h = oy+diry*t;
		if (h < bottom && h > top)
			ft = t;
	}

	// Checking horizontal sides
	// Check top side
	if (diry > 0)
	{
		t = (top-oy)/diry;
		h = ox+dirx*t;
		if (h < right && h > left)
			ft = t;
	}
	// Check bottom side
	else if (diry < 0)
	{
		t = (bottom-oy)/diry;
		h = ox+dirx*t;
		if (h < right && h > left)
			ft = t;
	}

	if (ft > 0)
	{
		pos = ft;
		// Successful
		return true;
	}
	// Unsuccessful
	return false;
}

void JMRect::translate(float xx, float yy)
{
	top += originy;
	bottom += originy;
	left += originx;
	right += originx;
	originx += xx;
	originy += yy;
}

void JMRect::position(float xx, float yy)
{
	top = yy+top-originx;
	bottom = yy+bottom-originy;
	left = xx+left-originx;
	right = xx+right-originx;
	originx = xx;
	originy = yy;
}
