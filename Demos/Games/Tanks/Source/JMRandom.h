/************************************************************************/
/* @class JMCircle
 * @author Jack McCallum
 * 
 * @description
 * Basic random number generator, runs faster than standard rand()
 * a friend showed me this but he dosn't know where he found it
 * 
/************************************************************************/

#pragma once

#define JMRAND_MAX 0x7fffffff

class JMRandom
{
public:
	JMRandom(float s = 0);

	void seed(int s);
	int generate();

	float range(float rmin, float rmax);
	float clamped();

private:
	int xor_x;
	int xor_y;
	int xor_z;
	int xor_w;
};

