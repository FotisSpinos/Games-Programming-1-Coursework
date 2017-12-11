#include "cSDL2CTRManager.h"


cSDL2CTRManager* cSDL2CTRManager::pInstance = NULL;


cSDL2CTRManager::cSDL2CTRManager()
{
}

bool cSDL2CTRManager::initCTR()
{
	// Initialize SDL's Game controller subsystem
	if (SDL_Init(SDL_INIT_GAMECONTROLLER) < 0)
	{
		cout << "Failed to init SDL/GAMECONTROLLER" << endl;
		return false;
	}
	// Check all joisticks and define theXBOX360Controller accordingly
	for (int i = 0; i < SDL_NumJoysticks(); i++)
	{
		if (SDL_IsGameController(i))
		{
			theXBOX360Controller = SDL_GameControllerOpen(i);
			cout << "Successfully created XBOX 360 Controller" << endl;
			break;
		}
	}
	// Check that everything worked out okay
	if (!theXBOX360Controller)
	{
		cout << "Unable to create XBOX360Controller";
		CheckSDLError(__LINE__);
		return false;
	}
	return true;
}

void cSDL2CTRManager::CheckSDLError(int line)
{
	string error = SDL_GetError();

	if (error != "")
	{
		cout << "SLD Error : " << error << std::endl;

		if (line != -1)
			cout << "\nLine : " << line << std::endl;

		SDL_ClearError();
	}
}

SDL_GameController * cSDL2CTRManager::getSDLXBOX360Controller()
{
	return theXBOX360Controller;
}

cSDL2CTRManager * cSDL2CTRManager::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cSDL2CTRManager();
	}
	return cSDL2CTRManager::pInstance;

}
