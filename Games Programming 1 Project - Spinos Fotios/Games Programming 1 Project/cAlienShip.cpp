#include "cAlienShip.h"



cAlienShip::cAlienShip()
{

}


cAlienShip::~cAlienShip()
{
}

void cAlienShip::update(float deltaTime)
{
	rateOfFire -= deltaTime;

	//Get position of Alien Ship
	SDL_Rect currentSpritePos = this->getSpritePos();

	if (moveRight)
	{
		if (this->getSpritePos().x > initialPos.x + 35)
		{
			moveRight = false;
		}
		else
		{
			currentSpritePos.x += 10 * 8 * deltaTime;
		}
	}
	else
	{
		if (this->getSpritePos().x < initialPos.x - 35)
		{
			moveRight = true;
		}
		else
		{
			currentSpritePos.x -= 5 * 8 * deltaTime;	//alienShipVelocity.x
		}
	}

	//Set Alien Ship position
	this->setSpritePos({ currentSpritePos.x , currentSpritePos.y });

	// Set bounding Rectingles
	this->setBoundingRect(this->getSpritePos());

}
/*
=================================================================
Sets the velocity for the rocket
=================================================================
*/
void cAlienShip::setAlienShipVelocity(SDL_Point alienShipVel)
{
	alienShipVelocity = alienShipVel;
}
/*
=================================================================
Gets the rocket velocity
=================================================================
*/
SDL_Point cAlienShip::getAlienShipVelocity()
{
	return alienShipVelocity;
}
/*
=================================================================
Sets the rotation angle for the rocket
=================================================================
*/
void cAlienShip::setAlienShipRotation(double theRotAngle)
{
	AlienShipRotAngle = theRotAngle;
}
/*
=================================================================
Gets the rotation angle for the rocket
=================================================================
*/
double cAlienShip::getAlienShipRotation()
{
	return AlienShipRotAngle;
}

void cAlienShip::initialize()
{
	alienShipVelocity.x = 3;
	moveRight = true;
}

void cAlienShip::setInitialPos(SDL_Point initialPos)
{
	this->initialPos = initialPos;
}

void cAlienShip::setRateOfFire()
{
	rateOfFire = rand() % 20 + 2;
}

float cAlienShip::getRateOfFire()
{
	return rateOfFire;
}