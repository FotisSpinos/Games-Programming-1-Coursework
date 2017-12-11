#ifndef _SDL2CTRMANAGER_H
#define _SDL2CTRMANAGER_H

/*
==================================================================================
cSDL2WNDManager.h
==================================================================================
*/
#include <SDL.h>
#include <string>
#include <iostream>

using namespace std;

class cSDL2CTRManager
{
public:
	cSDL2CTRManager();

	bool initCTR();
	void CheckSDLError(int line);

	SDL_GameController* getSDLXBOX360Controller();


	static cSDL2CTRManager* getInstance();

private:

	static cSDL2CTRManager* pInstance;
	SDL_GameController* theXBOX360Controller;
};

#endif

