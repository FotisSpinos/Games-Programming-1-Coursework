/*
==================================================================================
cGame.cpp
==================================================================================
*/
#include "cGame.h"
#include "fstream"

cGame* cGame::pInstance = NULL;
static cTextureMgr* theTextureMgr = cTextureMgr::getInstance();
static cFontMgr* theFontMgr = cFontMgr::getInstance();
static cSoundMgr* theSoundMgr = cSoundMgr::getInstance();
static cSDL2CTRManager* theControllerManager = cSDL2CTRManager::getInstance();
static cButtonMgr* theButtonMgr = cButtonMgr::getInstance();
static cSceneMgr * sceneMng = cSceneMgr::getInstance();

/*
=================================================================================
Constructor
=================================================================================
*/
cGame::cGame()
{

}
/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
cGame* cGame::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cGame();
	}
	return cGame::pInstance;
}

void cGame::initialise(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	//Set the Renderer
	theRendererStored = theRenderer;

	// Get width and height of render context
	SDL_GetRendererOutputSize(theRenderer, &renderWidth, &renderHeight);
	this->m_lastTime = high_resolution_clock::now();

	// Clear the buffer with a black background
	SDL_SetRenderDrawColor(theRenderer, 0, 0, 0, 255);
	SDL_RenderPresent(theRenderer);
	
	theTextureMgr->setRenderer(theRenderer);
	theFontMgr->initFontLib();
	theSoundMgr->initMixer();

	//initialize xbox360 Controller
	theControllerManager->initCTR();

	// Set the initial value for Lives and Score
	livesValue = 3;
	scoreValue = 0;

	//store relative path and name of every texture
	textureName = { "startSceneBackground", "endSceneBackground", "theBackground", "theRocket", "theAlienSpaceShip", "bullet", "AlienShipBullet" };
	texturesToUse = { "Images\\startSceneBackground.png", "Images\\endSceneBackground.png", "Images\\theBackground.png", "Images\\rocketSprite.png", "Images\\alienSpaceShip.png", "Images\\Bullet.png", "Images\\AlienShipLazer.png" };
	//startSceneBackground, "endSceneBackground"

	//Create textures
	for (int tCount = 0; tCount < textureName.size(); tCount++)
	{
		theTextureMgr->addTexture(textureName[tCount], texturesToUse[tCount]);
	}

	// Create textures for Game Dialogue (text)
	fontList = { "digital", "spaceAge" };
	fontsToUse = { "Fonts/digital-7.ttf", "Fonts/space age.ttf" };
	for (int fonts = 0; fonts < fontList.size(); fonts++)
	{
		theFontMgr->addFont(fontList[fonts], fontsToUse[fonts], 25);
	}

	// Convert int lives to LPCSTR
	string livesString = to_string(livesValue);
	LPCSTR livesLPCSTR = livesString.c_str();

	// Convert int Score to LPCSTR
	string scoreString = to_string(scoreValue);
	LPCSTR scoreLPCSTR = scoreString.c_str();

	// Add(crate) textures to the texture manager
	gameTextList = { "Score: ", scoreLPCSTR, "Lives: ", livesLPCSTR, "Instructions" ,"- Press left/right key to move left/right", "- Press 'Space' key to shoot" };
	gameTextName = { "ScoreText", "ScoreValue", "LivesText", "LivesValue", "InstructionsTitle" , "MoveInstructions", "ShootInstructions" };

	for (int i = 0; i < gameTextList.size(); i++)
	{
		theTextureMgr->addTexture(gameTextName[i], theFontMgr->getFont("spaceAge")->createTextTexture(theRenderer, gameTextList[i], SOLID, { 0, 255, 0, 255 }, { 0, 0, 0, 0 }));	//add text using a font (and creating a texture))
	}
	
	// Load game sounds
	soundList = { "theme", "shot", "explosion", "playerLost", "AlienSpaceShipShot", "earnPoints" };
	soundTypes = { MUSIC, SFX, SFX, SFX, SFX, SFX };
	soundsToUse = { "Audio/BackgroundTheme.mp3", "Audio/shot007.wav", "Audio/explosion2.mp3", "Audio/Player_Lost.mp3", "Audio/AlienSpaceShipShot.mp3", "Audio/pointsEarned.mp3" };
	for (int sounds = 0; sounds < soundList.size(); sounds++)
	{
		theSoundMgr->add(soundList[sounds], soundsToUse[sounds], soundTypes[sounds]);
	}
	theSoundMgr->getSnd("theme")->play(-1);

	//Set the Buttons 
	btnNameList = { "exit_btn", "instructions_btn", "load_btn", "menu_btn", "play_btn", "save_btn", "settings_btn" };
	btnTexturesToUse = { "Images/Buttons/button_exit.png", "Images/Buttons/button_instructions.png", "Images/Buttons/button_load.png", "Images/Buttons/button_menu.png", "Images/Buttons/button_play.png", "Images/Buttons/button_save.png", "Images/Buttons/button_settings.png" };
	btnPos = { { 400, 375 },{ 400, 300 },{ 400, 300 },{ 500, 500 },{ 400, 300 },{ 740, 500 },{ 400, 300 } };
	for (int bCount = 0; bCount < btnNameList.size(); bCount++)
	{
		theTextureMgr->addTexture(btnNameList[bCount], btnTexturesToUse[bCount]);
	}
	for (int bCount = 0; bCount < btnNameList.size(); bCount++)
	{
		cButton * newBtn = new cButton();
		newBtn->setTexture(theTextureMgr->getTexture(btnNameList[bCount]));
		newBtn->setSpritePos(btnPos[bCount]);
		newBtn->setSpriteDimensions(theTextureMgr->getTexture(btnNameList[bCount])->getTWidth(), theTextureMgr->getTexture(btnNameList[bCount])->getTHeight());
		theButtonMgr->add(btnNameList[bCount], newBtn);
	}

	//Set the background 
	spriteBkgd.setSpritePos({ 0, 0 });
	spriteBkgd.setTexture(theTextureMgr->getTexture("theBackground"));
	spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("theBackground")->getTWidth(), theTextureMgr->getTexture("theBackground")->getTHeight());
	spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("theRocket")->getTWidth(), theTextureMgr->getTexture("theRocket")->getTHeight());

	//Set the player's rocket
	theRocket.setSpritePos({ renderWidth / 2, 600 });
	theRocket.setTexture(theTextureMgr->getTexture("theRocket"));
	theRocket.setSpriteScale({ -0.6f, -0.6f });
	theRocket.scaleSprite();

	//Set Game State
	theGameState = INSTRUCTIONS;

	//Set SceneMng
	sceneMng = new cSceneMgr(theRenderer, theButtonMgr, theTextureMgr, theFontMgr, theSoundMgr, spriteBkgd, renderWidth, renderHeight);
	sceneMng->setGameState(theGameState);
	sceneMng->setRocket(theRocket);
	sceneMng->setBullets(theBullets);
	sceneMng->setAlienShips(theAlienShips);
	sceneMng->setGameTextList(gameTextList);
	sceneMng->setLoop(true);

	sceneMng->setFiles("Data/rocket_data.dat", "Data/alien_ships_data.dat", "Data/bullets.dat", "Data/UI_Data.dat");

	if (sceneMng->filesEmpty())
	{
		sceneMng->spawnAlienShips(26, 60);	//26 60
		sceneMng->setScoreValue(0);
		sceneMng->setLivesValue(3);
	}
	else
	{
		sceneMng->loadPlayingSceneData();
	}
}

void cGame::run(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	loop = true;

	while (loop)
	{
		//We get the time that passed since the last frame
		double elapsedTime = this->getElapsedSeconds();

		loop = this->getInput(loop);
		this->update(elapsedTime);
		this->render(theSDLWND, theRenderer);
	}
}

void cGame::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	SDL_RenderClear(theRenderer);

	sceneMng->renderScene();

	SDL_RenderPresent(theRenderer);
}

void cGame::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, double rotAngle, SDL_Point* spriteCentre)
{

	SDL_RenderPresent(theRenderer);
}

void cGame::update()
{

}

void cGame::update(double deltaTime)
{
	sceneMng->updateScenes(deltaTime);
}

bool cGame::getInput(bool theLoop)
{
	return sceneMng->updateEvents();
}

double cGame::getElapsedSeconds()
{
	this->m_CurrentTime = high_resolution_clock::now();
	this->deltaTime = (this->m_CurrentTime - this->m_lastTime);
	this->m_lastTime = this->m_CurrentTime;
	return deltaTime.count();
}

void cGame::setTextureUpdateBool(bool updateScore, bool updateLives)
{
	this->updateScore = updateScore;
	this->updateLives = updateLives;
}

void cGame::cleanUp(SDL_Window* theSDLWND)
{
	// Delete our OpengL context
	SDL_GL_DeleteContext(theSDLWND);

	// Destroy the window
	SDL_DestroyWindow(theSDLWND);

	// Quit IMG system
	IMG_Quit();

	// Shutdown SDL 2
	SDL_Quit();
}
