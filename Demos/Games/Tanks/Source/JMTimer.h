/****************************************************
Author: Jack McCallum

Description: 
http://stackoverflow.com/questions/13948105/high-resolution-timer-library-in-c-windows
Very simple high resolution timer

****************************************************/

#pragma once

class JMTimer
{
public:
	// Default constructor
	JMTimer();
		
	// Gets time in milliseconds since last reset, 
	// or since creation if reset has not been called
	float getms();

	// Resets the timer to  0
	void reset();

private:
	// For keeping track of time
	long long time;
	float PCFreq;
};