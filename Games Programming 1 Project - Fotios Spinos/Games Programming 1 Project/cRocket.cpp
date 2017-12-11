/*
=================
cRocket.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cRocket.h"

/*
=================================================================
Defualt Constructor
=================================================================
*/
cRocket::cRocket() : cSprite()
{
	this->rocketVelocity = { 0, 0 };
	rateOfFire = 0;
	rateOfFireStore = 0.8f;
}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cRocket::update(double deltaTime)
{

	//updates rate of fire
	rateOfFire -= deltaTime;

	// Set bounding Rectingles
	this->setBoundingRect(this->getSpritePos());

	SDL_Rect currentSpritePos = this->getSpritePos();

	currentSpritePos.x += rocketVelocity.x * 50 * deltaTime; //* this->getRocketRotation();
	currentSpritePos.y += rocketVelocity.y * 50 * deltaTime; //* this->getRocketRotation();

	rocketVelocity.x *= 0.95;
	rocketVelocity.y *= 0.95;
	this->setSpritePos({ currentSpritePos.x , currentSpritePos.y });
}
/*
=================================================================
Sets the velocity for the rocket
=================================================================
*/
void cRocket::setRocketVelocity(SDL_Point rocketVel)
{
	rocketVelocity = rocketVel;
}
/*
=================================================================
Gets the rocket velocity
=================================================================
*/
SDL_Point cRocket::getRocketVelocity()
{
	return rocketVelocity;
}


float cRocket::getRateOfFire()
{
	return rateOfFire;
}

void cRocket::setRateOfFire(float rateOfFire)
{
	this->rateOfFire = rateOfFire;
}

float cRocket::getRateOfFireStore()
{
	return rateOfFireStore;
}

void cRocket::shoot(vector<cBullet*> theBullets, cTextureMgr * theTextureMgr, int numBullets)
{
	theBullets[numBullets]->setSpriteTranslation({ 2, 2 });
	theBullets[numBullets]->setTexture(theTextureMgr->getTexture("bullet"));
	theBullets[numBullets]->setSpriteDimensions(theTextureMgr->getTexture("bullet")->getTWidth(), theTextureMgr->getTexture("bullet")->getTHeight());
	theBullets[numBullets]->setBulletVelocity({ 2, 2 });
	theBullets[numBullets]->setSpriteRotAngle(this->getSpriteRotAngle());
	theBullets[numBullets]->setSpriteScale({ -0.9f,-0.9f });
	theBullets[numBullets]->scaleSprite();
	theBullets[numBullets]->setSpritePos({ this->getSpritePos().x + this->getSpriteCentre().x - theBullets[numBullets]->getSpriteCentre().x
		,this->getSpritePos().y - 50 });
	theBullets[numBullets]->setOrigin("User_Space_Ship");
	theBullets[numBullets]->setActive(true);

	this->setRateOfFire(this->getRateOfFireStore());
}

void cRocket::moveLeft(float velocity)
{
	if (this->getSpritePos().x >= 0)
		this->setRocketVelocity({ -5, 0 });
}

void cRocket::moveRight(float velocity, int renderWidth)
{
	if (this->getSpritePos().x <= renderWidth)
		this->setRocketVelocity({ 5, 0 });
}

void cRocket::moveUp(float velocity)
{
	if (this->getSpritePos().y >= 0)
		this->setRocketVelocity({ 0, -5 });
}

void cRocket::moveDown(float velocity, int renderHeight)
{
	if (this->getSpritePos().y <= renderHeight)
		this->setRocketVelocity({ 0, 5 });
}
