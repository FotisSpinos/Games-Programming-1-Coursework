/*
=================
cRocket.h
- Header file for class definition - SPECIFICATION
- Header file for the Rocket class which is a child of cSprite class
=================
*/
#ifndef _CROCKET_H
#define _CROCKET_H
#include "cSprite.h"
#include "cBullet.h"
#include "cTextureMgr.h"

class cRocket : public cSprite
{
private:
	SDL_Point rocketVelocity;
	float rateOfFire;
	float rateOfFireStore;
public:
	cRocket();
	void update(double deltaTime);		// Rocket update method
	void setRocketVelocity(SDL_Point rocketVel);   // Sets the velocity for the rocket
	SDL_Point getRocketVelocity();				 // Gets the rocket velocity
	float getRateOfFire();						//Gets the rate of fire
	void setRateOfFire(float rateOfFire);		//Sets the rate of fire
	float getRateOfFireStore();					//Gets rate of fire
	void shoot(vector<cBullet*> theBullets, cTextureMgr* theTextureMgr, int numBullets);
	void moveLeft(float velocity);
	void moveRight(float velocity, int renderWidth);
	void moveUp(float velocity);
	void moveDown(float velocity, int renderHeight);
};
#endif