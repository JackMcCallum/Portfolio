#include "StdAfx.h"
#include "Collidable.h"
#include "CollisionManager.h"
#include "JMCircle.h"
#include "JMRect.h"

// ------------------------------------------------------------------------------------------------------------
Collidable::Collidable(GameData gd)
{
	gameData = gd;
	assert(gameData.ogreMain);
	assert(gameData.collisionManager);
	
	// Nullify the shape, this gets controlled from derived classed
	collisionShape = NULL;

	nDelete = false;
	posx = 0;
	posy = 0;
	// Set this object to be static by default
	mass = 0;

	// Create the scene node that a derive class can use
	mainNode = gameData.ogreMain->getSceneManager()->getRootSceneNode()->createChildSceneNode();

	// Add this to the collision manager
	gameData.collisionManager->addCollidable(this);
}
// ------------------------------------------------------------------------------------------------------------
Collidable::~Collidable()
{
	// Remove this from the collision manager
	gameData.collisionManager->removeCollidable(this);
	// Destroy node and its children
	mainNode->removeAndDestroyAllChildren();
	gameData.ogreMain->getSceneManager()->destroySceneNode(mainNode);
	if (collisionShape) delete collisionShape;
}
// ------------------------------------------------------------------------------------------------------------
JMShape* Collidable::getCollision()
{
	return collisionShape;
}
// ------------------------------------------------------------------------------------------------------------
void Collidable::setCollisionCircle(float radius)
{
	// Delete the old shape if its there
	if (collisionShape) delete collisionShape;
	collisionShape = new JMCircle(radius);
	// Move it to where this object is located
	collisionShape->translate(posx, posy);
}
// ------------------------------------------------------------------------------------------------------------
void Collidable::setCollisionCircle(float xx, float yy, float radius)
{
	// Delete the old shape if its there
	if (collisionShape) delete collisionShape;
	collisionShape = new JMCircle(xx,yy,radius);
	// Move it to where this object is located
	collisionShape->translate(posx, posy);
}
// ------------------------------------------------------------------------------------------------------------
void Collidable::setCollisionRect(float width, float height)
{
	// Delete the old shape if its there
	if (collisionShape) delete collisionShape;
	collisionShape = new JMRect(width, height);
	// Move it to where this object is located
	collisionShape->translate(posx, posy);
}
// ------------------------------------------------------------------------------------------------------------
void Collidable::setCollisionRect(float top, float left, float bottom, float right)
{
	// Delete the old shape if its there
	if (collisionShape) delete collisionShape;
	collisionShape = new JMRect(top, left, bottom, right);
	// Move it to where this object is located
	collisionShape->translate(posx, posy);
}
// ------------------------------------------------------------------------------------------------------------
void Collidable::position(float xx, float yy)
{
	// Update the position of the node and the collision shape
	posx = xx;
	posy = yy;
	mainNode->setPosition(xx, 0, yy);
	if (collisionShape) collisionShape->position(xx, yy);
}
// ------------------------------------------------------------------------------------------------------------
void Collidable::translate(float xx, float yy)
{
	// Move the node and the collision shape
	posx += xx;
	posy += yy;
	mainNode->translate(xx, 0, yy);
	if (collisionShape) collisionShape->translate(xx, yy);
}
// ------------------------------------------------------------------------------------------------------------
void Collidable::getPosition(float& xx, float& yy)
{
	xx = posx;
	yy = posy;
}
// ------------------------------------------------------------------------------------------------------------
float Collidable::getMass()
{
	return mass;
}
// ------------------------------------------------------------------------------------------------------------
void Collidable::setMass(float val)
{
	mass = val;
}
// ------------------------------------------------------------------------------------------------------------
void Collidable::setRayQueryFlags(int flags)
{
	rayQueryFlags = flags;
}
// ------------------------------------------------------------------------------------------------------------
int Collidable::getRayQueryFlags()
{
	return rayQueryFlags;
}
// ------------------------------------------------------------------------------------------------------------
void Collidable::deleteThis()
{
	nDelete = true;
}
// ------------------------------------------------------------------------------------------------------------
void Collidable::collision(Collidable* obj, float pushx, float pushy)
{
	// Do nothing
}
// ------------------------------------------------------------------------------------------------------------
void Collidable::update(float timeSinceLastFrame)
{
	// Do nothing
}
// ------------------------------------------------------------------------------------------------------------