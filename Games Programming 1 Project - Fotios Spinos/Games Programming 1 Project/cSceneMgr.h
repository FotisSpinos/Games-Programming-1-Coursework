#pragma once
#include "asteroidsGame.h"
class cSceneMgr
{
public:
	//Constructors / Destractors
	cSceneMgr();
	~cSceneMgr();
	cSceneMgr(SDL_Renderer * theRenderer, cButtonMgr * theButtonMgr, cTextureMgr * theTextureMgr,
		cFontMgr * theFontMgr, cSoundMgr * theSoundMgr, cSprite spriteBkgd, int renderWidth, int renderHeight);

	//Render Functions
	void renderTexture(cTexture * tempTextTexture, SDL_Rect pos, FPoint scale);
	void renderButton(int posX, int posY, LPCSTR buttonName);
	void renderBackground(LPCSTR textueName, cSprite backgroundSprite);
	void renderBullets(vector<cBullet*> theBullets);
	void renderAlienSpaceShips(vector<cAlienShip*> theAlienShips);
	void renderUI(LPCSTR textureName, vector<LPCSTR> gameTextList, bool updateBool, int UIValue);

	//Render Scenes
	void renderInstructions();
	void renderEnd();
	void renderPlaying();
	void renderScene();

	//Update Functions
	void updateGameState(LPCSTR buttonName, gameState newGameState, SDL_Point theAreaClicked);
	void updateGameState(gameState gameState);
	void updateBulletsVisibility(float deltaTime);
	void updateAlienShipsVisibility(float deltaTime);
	void updateAlienShipsFireRate(float deltaTime);
	void updateCollisions(float deltaTime);
	void updateRocket(float deltaTime);

	//Spawn Functions
	void spawnAlienShips(int remainingShips, float height);
	void spawnRocket(string rocketData);
	void updateXY(string fileData);
	void spawnAlienShips(vector<int> xAxis, vector<int> yAxis);
	void spawnBullets(vector<int> xAxis, vector<int> yAxis);
	void generateUI(string uiData);

	//Update Scenes
	void updateInstructionsScene();
	void updateEndScene();
	void updatePlayingScene(float deltaTime);
	void loadPlayingSceneData();	//edit
	bool updateEvents();
	void updateScenes(float deltaTime);
	void clearFiles();

	//Setters
	void setBullets(vector<cBullet*> theBullets);
	void setAlienShips(vector<cAlienShip*> theAlienShips);
	void setRocket(cRocket theRocket);
	void setLivesValue(int livesValue);
	void setScoreValue(int scoreValue);
	void setUpdateLives(bool updateLives);
	void setUpdateScore(bool updateScore);
	void setLoop(bool loop);
	void setGameState(gameState theGameState);
	void setGameTextList(vector<LPCSTR> gameTextList);
	void setFiles(string rocketFileName, string alienShipsFileName, string bulletsName, string uIFileName);

	//Getters
	int getLivesValue();
	int getScoreValue();
	bool getUpdateLives();
	bool getUpdateScore();
	vector<cAlienShip*> getAlienShips();
	vector<cBullet*> getBullets();
	cRocket getRocket();
	SDL_Point getAreaClicked();
	gameState getGameState();
	static cSceneMgr * getInstance();
	bool getLoop();

	string getGameDataBullets();
	vector<LPCSTR> getGameTextList();

	bool filesEmpty();

private:
	// Game Variables
	SDL_Renderer * theRenderer;
	cButtonMgr * theButtonMgr;
	cTextureMgr * theTextureMgr;
	cFontMgr * theFontMgr;
	cSprite spriteBkgd; 
	cSoundMgr * theSoundMgr;
	int renderWidth; 
	int renderHeight;
	bool updateLives;
	bool updateScore;
	static cSceneMgr * pInstance;

	SDL_Point theAreaClicked;
	gameState theGameState;

	int livesValue;
	int scoreValue;

	vector<cAlienShip*> theAlienShips;
	vector<cBullet*> theBullets;

	string gameDataBullets;
	string gameDataAlienSpaceShips;
	string gameDataRocket;
	string gameDataToFile;
	float autoSaveTimer = 0;
	cFileHandler theRocketFile;
	cFileHandler theAlienShipFile;
	cFileHandler theBulletsFile;
	cFileHandler theUIFile;
	bool clearedFiles = false;

	cRocket theRocket;
	bool theLoop;

	cAlienShip alienShip;
	vector<LPCSTR> gameTextList;

	int rocketX;
	int rocketY;
	vector<int> xAxisData;
	vector<int> yAxisData;
	
	cBullet * theBullet;
};