#pragma once
#include "cSprite.h"
#ifndef _CALIENSHIP_H
#define _CALIENSHIP_H

class cAlienShip : public cSprite
{

private:
	SDL_Point alienShipVelocity;
	double AlienShipRotAngle;
	bool moveRight;
	int moveBorder;
	SDL_Point initialPos;
	float rateOfFire;
public:
	cAlienShip();
	~cAlienShip();
	void update(float deltaTime);
	void movement();

	void setRateOfFire();
	float getRateOfFire();
	void setAlienShipVelocity(SDL_Point rocketVel);   // Sets the velocity for the rocket
	SDL_Point getAlienShipVelocity();				 // Gets the rocket velocity
	void setAlienShipRotation(double theRotAngle);   // Sets the rotation angle for the rocket
	double getAlienShipRotation();					// Gets the rotation angle for the rocket velocity
	SDL_Point defaultVelocity;

	void initialize();
	void setInitialPos(SDL_Point initialPos);
	
};
#endif