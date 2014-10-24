/************************************************************************/
/* @class Player
 * @author Jack McCallum
 * 
 * @description
 * Player class, 
 * it takes input form the input handlers and uses it control a
 * Collidable around the map and shoot when you click
 * 
/************************************************************************/

#pragma once

#include "Destructable.h"
#include "Collidable.h"

class Player : 
	public Collidable,
	public Destructable,
	public JMKeyboardEventListener,
	public JMMouseEventListener
{
public:
	Player(GameData gd, JMMouseEventHandler* mouse = NULL, JMKeyboardEventHandler* keyboard = NULL);
	virtual ~Player();

	// Control
	virtual void update(float timeSinceLastFrame);

	// Input events
	virtual void eventKeyboardKeyPressed(const JMKeyEvent &evt);
	virtual void eventKeyboardKeyReleased(const JMKeyEvent &evt);
	virtual void eventMouseMoved(const JMMouseEvent &evt);
	virtual void eventMousePressed(const JMMouseEvent &evt);
	virtual void eventMouseReleased(const JMMouseEvent &evt);

	// Use weapon
	void firePrimaryWeapon();

	// When health reaches 0
	virtual void destroyed();

private:
	// Player control
	// Direction in degrees
	float direction;
	// Linear and angular velocity
	float linvelocity, angvelocity;
	// Linear and angular velocity
	float targetx, targety;
	
	int primaryGunTimout;


	// Input control
	// Button State
	bool upPushed, leftPushed, downPushed, rightPushed, leftmbPushed;
	// Mouse position from 0-1
	float mousex, mousey;
	
	// Input handlers
	JMMouseEventHandler* mouseEventHandler;
	JMKeyboardEventHandler* keyboardEventHandler;

	// Ogre
	SceneNode* gunNode;
	// Big main cannon
	SceneNode* primaryTipNode;
	
};

