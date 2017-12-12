#ifndef _GAME_H
#define _GAME_H

/*
==================================================================================
cGame.h
==================================================================================
*/

#include <SDL.h>

// Game specific includes
#include "asteroidsGame.h"


using namespace std;

class cGame
{
public:
	cGame();

	void initialise(SDL_Window* theSDLWND, SDL_Renderer* theRenderer);
	void run(SDL_Window* theSDLWND, SDL_Renderer* theRenderer);
	void cleanUp(SDL_Window* theSDLWND);
	void render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer);
	void render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, double rotAngle, SDL_Point* spriteCentre);
	void update();
	void update(double deltaTime);
	bool getInput(bool theLoop);
	double getElapsedSeconds();

	//Sets Bools UpdateScore and UpdateLives
	void setTextureUpdateBool(bool updateScore, bool updateLives);

	static cGame* getInstance();

private:

	static cGame* pInstance;
	// for framerates
	time_point< high_resolution_clock > m_lastTime;
	time_point< high_resolution_clock > m_CurrentTime;
	duration< double > deltaTime;

	// Sprites for displaying background and rocket textures
	cSprite spriteBkgd;
	cRocket theRocket;
	cAsteroid theAsteroid;
	cBullet * theBullet;
	// game related variables
	vector<LPCSTR> textureName;
	vector<LPCSTR> textName;
	vector<LPCSTR> texturesToUse;
	vector<cAsteroid> theAsteroids;
	vector<cBullet*> theBullets;
	// Fonts to use
	vector<LPCSTR> fontList;
	vector<LPCSTR> fontsToUse;
	// Text for Game
	vector<LPCSTR> gameTextList;
	vector<LPCSTR> gameTextName;
	// Game Sounds
	vector<LPCSTR> soundList;
	vector<soundType> soundTypes;
	vector<LPCSTR> soundsToUse;
	// Game objects
	vector<cAlienShip*> theAlienShips;
	// Spawn Function
	// Define the elements and there position in/on the array/map
	int renderWidth, renderHeight;
	int scoreValue;
	int livesValue;

	//define the Renderer
	SDL_Renderer* theRendererStored;

	//define Xbox360 Controller
	SDL_GameController* theXbox360Controller;

	gameState theGameState;
	btnTypes theBtnType;
	SDL_Rect pos;
	FPoint scale;
	SDL_Rect aRect;
	SDL_Color aColour;
	cTexture* tempTextTexture;
	SDL_Point theAreaClicked;

	vector<LPCSTR> btnNameList;
	vector<LPCSTR> btnTexturesToUse;
	vector<SDL_Point> btnPos;
	vector <cButton> theButtons;

	bool loop;

	bool updateLives = false;
	bool updateScore = false;

	// File Related Variables
	bool fileAvailable;
	cFileHandler theRocketFile;
	cFileHandler theAlienShipsFile;
	cFileHandler theBulletsFile;
	float autoSaveTimer = 2.0f;
	string gameDataRocket;
	string gameDataBullets;
	string gameDataAlienSpaceShips;
	string gameDataToFile;
};

#endif
