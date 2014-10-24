#include "StdAfx.h"
#include "JMRandom.h"


JMRandom::JMRandom(float s)
{
	seed(0);
}

void JMRandom::seed(int s)
{
	xor_x = 123456789;
	xor_y = 362436069;
	xor_z = 521288629;
	xor_w = s;

	// Generate 4 times to put the start values out
	for (int i=0; i<4; i++)
		generate();
}

int JMRandom::generate()
{
	int t;
	t = xor_x ^ (xor_x << 11);
	xor_x = xor_y; 
	xor_y = xor_z; 
	xor_z = xor_w;
	return xor_w = xor_w ^ (xor_w >> 19) ^ (t ^ (t >> 8));
}

float JMRandom::range(float rmin, float rmax)
{
	return float(rmin + (rmax - rmin) * clamped());
}

float JMRandom::clamped()
{
	int b = generate();
	return b/float(JMRAND_MAX);
}
