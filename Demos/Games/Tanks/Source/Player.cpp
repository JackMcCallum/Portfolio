#include "StdAfx.h"
#include "Player.h"
#include "MathsMacros.h"

#include "JMRay.h"
#include "CollisionManager.h"

#include "Enemy.h"
#include "Spawner.h"
#include "ShockBeam.h"
#include "Explosion.h"

// ------------------------------------------------------------------------------------------------------------
Player::Player(GameData gd, JMMouseEventHandler* mouse, JMKeyboardEventHandler* keyboard) : Collidable(gd)
{
	// Object properties
	setMass(100);
	setHitPonts(100);
	setCollisionCircle(8);
	setRayQueryFlags(FLAG_PLAYER);

	// Setup ogre nodes
	mainNode->attachObject(gameData.ogreMain->getSceneManager()->createEntity("Tank_Body.mesh"));
	gunNode = mainNode->createChildSceneNode(Vector3(2,0,0));
	primaryTipNode = gunNode->createChildSceneNode(Vector3(-12,4.5f,0));
	gunNode->setInheritOrientation(false);
	gunNode->attachObject(gameData.ogreMain->getSceneManager()->createEntity("Tank_Gun.mesh"));

	// Setup input handlers
	mouseEventHandler = mouse;
	if (mouseEventHandler)
		mouseEventHandler->addListener((JMMouseEventListener*)this);

	keyboardEventHandler = keyboard;
	if (keyboardEventHandler)
		keyboardEventHandler->addListener((JMKeyboardEventListener*)this);
	
	// Zero memory
	posx = 0;
	posy = 0;
	mousex = 0;
	mousey = 0;
	targetx = 0;
	targety = 0;
	direction = 0;
	linvelocity = 0;
	angvelocity = 0;
	upPushed = false;
	leftPushed = false;
	downPushed = false;
	rightPushed = false;
	leftmbPushed = false;
	primaryGunTimout = 0;
}
// ------------------------------------------------------------------------------------------------------------
Player::~Player()
{
	// Remove from event handlers
	if (mouseEventHandler)
		mouseEventHandler->removeListener((JMMouseEventListener*)this);

	if (keyboardEventHandler)
		keyboardEventHandler->removeListener((JMKeyboardEventListener*)this);
}
// ------------------------------------------------------------------------------------------------------------
void Player::update(float timeSinceLastFrame)
{
	// Apply force
	if (upPushed)
		linvelocity += 0.2f;
	if (downPushed)
		linvelocity -= 0.2f;
	if (leftPushed)
		angvelocity += 1.0f * (1+linvelocity*0.2f);
	if (rightPushed)
		angvelocity -= 1.0f * (1+linvelocity*0.2f);

	// Apply friction
	linvelocity *= 0.9f;
	angvelocity *= 0.7f;

	// Calculate the direction vector
	float dirx, diry;
	dirx = SinD(direction);
	diry = CosD(direction);

	// Move in direction
	posx += dirx*linvelocity;
	posy += diry*linvelocity;

	// Update position
	position(posx, posy);

	// Apply angular velocity
	direction += angvelocity;

	// Body to face the direction
	Matrix3 m;
	Quaternion q;
	m.FromEulerAnglesXYZ(Degree(0), Degree(direction+90), Degree(0));
	q.FromRotationMatrix(m);
	mainNode->setOrientation(q);

	// Update cameras position to follow the player
	gameData.ogreMain->getCamera()->setFixedYawAxis(true, Vector3(0,0,1));
	gameData.ogreMain->getCamera()->setPosition(posx,150,posy);
	gameData.ogreMain->getCamera()->lookAt(posx,0,posy);

	// Calculate the target position by converting 2d position (mouse pos) to a 3d position
	Ray oray;
	gameData.ogreMain->getCamera()->getCameraToViewportRay(mousex, mousey, &oray);

	Plane plane(Vector3(0,-1,0), Vector3(0,0,0));
	std::pair<bool, float> r = oray.intersects(plane);
	if (r.first)
	{
		Vector3 mpos = oray.getPoint(r.second);
		targetx = mpos.x;
		targety = mpos.z;
	}

	// Calculate the guns direction
	Vector3 gunPos = gunNode->_getDerivedPosition();
	float gundirx, gundiry;
	gundirx = gunPos.x - targetx;
	gundiry = gunPos.z - targety;

	// Update the gun node orientation
	m.FromEulerAnglesXYZ(Degree(0), Math::ATan2(-gundiry, gundirx), Degree(0));
	q.FromRotationMatrix(m);
	gunNode->setOrientation(q);

	// Fire gun if button pushed
	if (leftmbPushed && primaryGunTimout <= 0)
	{
		firePrimaryWeapon();
		primaryGunTimout = 5;
	}
	primaryGunTimout--;
}
// ------------------------------------------------------------------------------------------------------------
void Player::firePrimaryWeapon()
{
	// Make a ray query of the gun trajectory
	
	Vector3 p0 = gunNode->_getDerivedPosition();
	Vector3 p1 = primaryTipNode->_getDerivedPosition();

	JMRay jmray(p0.x, p0.z, p1.x, p1.z); 
	rayResults results;
	gameData.collisionManager->rayQuery(&jmray, results, FLAG_WALL|FLAG_ENEMY);
	
	
	if (results.size() > 0)
	{
		// Sort the list then find the first
		results.sort();
		std::pair<float, Collidable*> t = *results.begin();
		
		float xx, yy;
		jmray.getPointOnRay(t.first, xx, yy);
		new ShockBeam(gameData.effectsManager, gameData.ogreMain, p1.x, p1.z, xx, yy, 1, ColourValue(1, 0.6f, 0.3f));


		// If it hits an enemy, damage it
		if (typeid(*t.second) == typeid(Enemy))
			static_cast<Enemy*>(t.second)->damage(50);
		// If it hits a spawner, damage it
		else if (typeid(*t.second) == typeid(Spawner))
			static_cast<Spawner*>(t.second)->damage(50);
	}

}
// ------------------------------------------------------------------------------------------------------------
void Player::eventKeyboardKeyPressed(const JMKeyEvent &evt)
{
	// Process input
	if (evt.key == 'W' || evt.key == VK_UP)
		upPushed = true;
	else if (evt.key == 'A' || evt.key == VK_LEFT)
		leftPushed = true;
	else if (evt.key == 'S' || evt.key == VK_DOWN)
		downPushed = true;
	else if (evt.key == 'D' || evt.key == VK_RIGHT)
		rightPushed = true;
	else if (evt.key == VK_SPACE)
		leftmbPushed = true;
}
// ------------------------------------------------------------------------------------------------------------
void Player::eventKeyboardKeyReleased(const JMKeyEvent &evt)
{
	// Process input
	if (evt.key == 'W' || evt.key == VK_UP)
		upPushed = false;
	else if (evt.key == 'A' || evt.key == VK_LEFT)
		leftPushed = false;
	else if (evt.key == 'S' || evt.key == VK_DOWN)
		downPushed = false;
	else if (evt.key == 'D' || evt.key == VK_RIGHT)
		rightPushed = false;
	else if (evt.key == VK_SPACE)
		leftmbPushed = false;
}
// ------------------------------------------------------------------------------------------------------------
void Player::eventMouseMoved(const JMMouseEvent &evt)
{
	// Process input
	mousex = evt.scaledX;
	mousey = evt.scaledY;
}
// ------------------------------------------------------------------------------------------------------------
void Player::eventMousePressed(const JMMouseEvent &evt)
{
	// Process input
	if (evt.button == MB_LBUTTON)
		leftmbPushed = true;
}
// ------------------------------------------------------------------------------------------------------------
void Player::eventMouseReleased(const JMMouseEvent &evt)
{
	// Process input
	if (evt.button == MB_LBUTTON)
		leftmbPushed = false;
}
// ------------------------------------------------------------------------------------------------------------
void Player::destroyed()
{
	new Explosion(gameData.effectsManager, gameData.ogreMain, posx, posy, 1, ColourValue(0.6f,1,0.1f));
	deleteThis();
}
// ------------------------------------------------------------------------------------------------------------