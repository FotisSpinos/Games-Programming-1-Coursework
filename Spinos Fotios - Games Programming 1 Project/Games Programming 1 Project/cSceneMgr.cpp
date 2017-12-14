#include "cSceneMgr.h"


cSceneMgr* cSceneMgr::pInstance = NULL;

cSceneMgr * cSceneMgr::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cSceneMgr();
	}
	return cSceneMgr::pInstance;

}

bool cSceneMgr::getLoop()
{
	return theLoop;
}

string cSceneMgr::getGameDataBullets()
{
	return gameDataBullets;
}

vector<LPCSTR> cSceneMgr::getGameTextList()
{
	return gameTextList;
}

bool cSceneMgr::filesEmpty()
{
	//Check if files are empty
	if (!theRocketFile.openFile(ios::in) || !theAlienShipFile.openFile(ios::in)
		|| !theBulletsFile.openFile(ios::in) || !theUIFile.openFile(ios::in)) //open file for input output
	{
		cout << "Could not open specified files. Error " << SDL_GetError() << endl;
	}
	else
	{
		cout << "Files opened for input!" << endl;
	}

	//if the files are empty
	if (theRocketFile.readDataFromFile() == "" &&
		theAlienShipFile.readDataFromFile() == "" &&
		theBulletsFile.readDataFromFile() == "" &&
		theUIFile.readDataFromFile() == "")
	{
		//close files
		theRocketFile.closeFile();
		theAlienShipFile.closeFile();
		theBulletsFile.closeFile();
		theUIFile.closeFile();
		return true;
	}
	else
	{
		//close files
		theRocketFile.closeFile();
		theAlienShipFile.closeFile();
		theBulletsFile.closeFile();
		theUIFile.closeFile();
		return false;
	}
}

cSceneMgr::cSceneMgr()
{
}

cSceneMgr::cSceneMgr(SDL_Renderer * theRenderer, cButtonMgr * theButtonMgr, cTextureMgr * theTextureMgr, cFontMgr * theFontMgr, cSoundMgr * theSoundMgr, cSprite spriteBkgd, int renderWidth, int renderHeight)
{
	//Set initial values
	this->theRenderer = theRenderer;
	this->theButtonMgr = theButtonMgr;
	this->theTextureMgr = theTextureMgr;
	this->theFontMgr = theFontMgr;
	this->theSoundMgr = theSoundMgr;
	this->spriteBkgd = spriteBkgd;
	this->renderWidth = renderWidth;
	this->renderHeight = renderHeight;

	//Set the scale for every alien spaceship
	alienShip.setSpriteScale({ -0.6f,-0.6f });
}

cSceneMgr::~cSceneMgr()
{
}

void cSceneMgr::renderTexture(cTexture * tempTextTexture, SDL_Rect pos, FPoint scale)
{
	tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), (&tempTextTexture->getTextureRect()), &pos, scale);
}

void cSceneMgr::renderButton(int posX, int posY ,LPCSTR buttonName)
{
	theButtonMgr->getBtn(buttonName)->setSpritePos({ posX , posY});
	theButtonMgr->getBtn(buttonName)->render(theRenderer, &theButtonMgr->getBtn(buttonName)->getSpriteDimensions(), &theButtonMgr->getBtn(buttonName)->getSpritePos(), theButtonMgr->getBtn(buttonName)->getSpriteScale());
}

void cSceneMgr::renderBackground(LPCSTR textueName, cSprite backgroundSprite)
{
	backgroundSprite.setTexture(theTextureMgr->getTexture(textueName));
	backgroundSprite.render(theRenderer, NULL, NULL, backgroundSprite.getSpriteScale());
}

void cSceneMgr::renderBullets(vector<cBullet*> theBullets)
{
	for (int draw = 0; draw < theBullets.size(); draw++)
	{
		theBullets[draw]->render(theRenderer, &theBullets[draw]->getSpriteDimensions(), &theBullets[draw]->getSpritePos(),
			theBullets[draw]->getSpriteRotAngle(), &theBullets[draw]->getSpriteCentre(), theBullets[draw]->getSpriteScale());
	}
}

void cSceneMgr::renderAlienSpaceShips(vector<cAlienShip> theAlienShips)
{
	for (int draw = 0; draw < theAlienShips.size(); draw++)
	{
		theAlienShips[draw].render(theRenderer, &theAlienShips[draw].getSpriteDimensions(), &theAlienShips[draw].getSpritePos(), theAlienShips[draw].getAlienShipRotation(),
			&theAlienShips[draw].getSpriteCentre(), theAlienShips[draw].getSpriteScale());
	}
}

void cSceneMgr::renderUI(LPCSTR textureName, vector<LPCSTR> gameTextList, bool updateBool, int UIValue)
{
	int index;

	if (updateBool)
	{
		theTextureMgr->deleteTexture(textureName);
		string livesString = to_string(UIValue);
		LPCSTR livesLPCSTR = livesString.c_str();
		if (textureName == "LivesValue")
		{
			index = 3;
		}
		else
		{
			index = 1;
		}
		gameTextList[index] = livesLPCSTR;
		theTextureMgr->addTexture(textureName, theFontMgr->getFont("spaceAge")->createTextTexture(theRenderer, gameTextList[index], SOLID, { 0, 255, 0, 255 }, { 0, 0, 0, 0 }));	//add text using a font (and creating a texture)
	}
}

void cSceneMgr::renderInstructions()
{
	//Render the background 
	this->renderBackground("startSceneBackground", spriteBkgd);

	//Render instruction's Title text
	this->renderTexture(theTextureMgr->getTexture("InstructionsTitle"),
	{ 5, 10, theTextureMgr->getTexture("InstructionsTitle")->getTextureRect().w, theTextureMgr->getTexture("InstructionsTitle")->getTextureRect().h },
	{ 0.13f, 0.13f });

	//Render move's Instructions text
	this->renderTexture(theTextureMgr->getTexture("MoveInstructions"),
	{ 5, 60, theTextureMgr->getTexture("MoveInstructions")->getTextureRect().w, theTextureMgr->getTexture("MoveInstructions")->getTextureRect().h },
	{ 0.13f, 0.13f });

	//Render shoot's instructions text
	this->renderTexture(theTextureMgr->getTexture("ShootInstructions"),
	{ 5, 90, theTextureMgr->getTexture("ShootInstructions")->getTextureRect().w, theTextureMgr->getTexture("ShootInstructions")->getTextureRect().h },
	{ 0.13f, 0.13f });

	//Render play button
	this->renderButton((renderWidth - theButtonMgr->getBtn("play_btn")->getSpriteDimensions().w) / 2, renderHeight - 150, "play_btn");

	//Render exit button
	this->renderButton((renderWidth - theButtonMgr->getBtn("exit_btn")->getSpriteDimensions().w) / 2, renderHeight - 100, "exit_btn");
}

void cSceneMgr::renderEnd()
{
	//Render background
	this->renderBackground("endSceneBackground", spriteBkgd);

	//Render menu button 
	this->renderButton(((renderWidth - theButtonMgr->getBtn("menu_btn")->getSpriteDimensions().w) / 2), renderHeight - 150, "menu_btn");

	//Render play button 
	this->renderButton(((renderWidth - theButtonMgr->getBtn("exit_btn")->getSpriteDimensions().w) / 2), renderHeight - 100, "exit_btn");

	//Render ScoreText
	this->renderTexture(theTextureMgr->getTexture("ScoreText"),
	{ (renderWidth - theTextureMgr->getTexture("ScoreText")->getTWidth()) / 2 - 30, (renderHeight - theTextureMgr->getTexture("ScoreText")->getTHeight()) / 2 + 150,
		theTextureMgr->getTexture("ScoreText")->getTextureRect().w, theTextureMgr->getTexture("ScoreText")->getTextureRect().h },
		{ 0.5f, 0.5f });

	//Render Score Value
	this->renderTexture(theTextureMgr->getTexture("ScoreValue"),
	{ (renderWidth - theTextureMgr->getTexture("ScoreValue")->getTWidth()) / 2 + 100, (renderHeight - theTextureMgr->getTexture("ScoreValue")->getTHeight()) / 2 + 150,
		theTextureMgr->getTexture("ScoreValue")->getTextureRect().w, theTextureMgr->getTexture("ScoreValue")->getTextureRect().h },
		{ 0.5f, 0.5f });
}

void cSceneMgr::renderPlaying()
{
	//Render background
	this->renderBackground("theBackground", spriteBkgd);

	//Render Score text
	this->renderTexture(theTextureMgr->getTexture("ScoreText"),
	{ 10, 10, theTextureMgr->getTexture("ScoreText")->getTextureRect().w, theTextureMgr->getTexture("ScoreText")->getTextureRect().h },
	{ 0.1f, 0.1f });

	//Render Score Value
	this->renderTexture(theTextureMgr->getTexture("ScoreValue"),
	{ 200, 10, theTextureMgr->getTexture("ScoreValue")->getTextureRect().w, theTextureMgr->getTexture("ScoreValue")->getTextureRect().h },
	{ 0.5f, 0.5f });

	//Render Lives text
	this->renderTexture(theTextureMgr->getTexture("LivesText"),
	{ 10, 40, theTextureMgr->getTexture("LivesText")->getTextureRect().w, theTextureMgr->getTexture("LivesText")->getTextureRect().h },
	{ 0.5f, 0.5f });

	//Render Lives text
	this->renderTexture(theTextureMgr->getTexture("LivesValue"),
	{ 200, 40, theTextureMgr->getTexture("LivesValue")->getTextureRect().w, theTextureMgr->getTexture("LivesValue")->getTextureRect().h },
	{ 0.5f, 0.5f });

	//Render menu buttons
	this->renderButton((renderWidth - theButtonMgr->getBtn("menu_btn")->getSpriteDimensions().w - 10), 10, "menu_btn");

	//Render each bullet in the vector array
	this->renderBullets(theBullets);

	//Render Alien Space Ships
	this->renderAlienSpaceShips(theAlienShips);

	//Render the rocket
	this->theRocket.render(theRenderer, &this->theRocket.getSpriteDimensions(),
		&this->theRocket.getSpritePos(), this->theRocket.getSpriteRotAngle(), &this->theRocket.getSpriteCentre(),
		this->theRocket.getSpriteScale());

	//Render lives
	if (updateLives)
	{
		this->renderUI("LivesValue", this->gameTextList, this->updateLives, this->livesValue);
		this->updateLives = false;
	}

	//Update Score
	if (updateScore)
	{
		this->renderUI("ScoreValue", this->gameTextList, this->updateScore, this->scoreValue);
		this->updateScore = false;
	}
}

void cSceneMgr::renderScene()
{
	switch (this->theGameState)
	{
	case INSTRUCTIONS:
	{
		this->renderInstructions();
	}
	break;

	case END:
	{
		this->renderEnd();
	}
	break;

	case PLAYING:
	{
		this->renderPlaying();
	}
	}
}

void cSceneMgr::updateGameState(LPCSTR buttonName, gameState newGameState, SDL_Point theAreaClicked)
{
	theGameState = theButtonMgr->getBtn(buttonName)->update(theGameState, newGameState, theAreaClicked);
}

void cSceneMgr::updateGameState(gameState gameState)
{
	this->theGameState = gameState;
}

void cSceneMgr::updateBulletsVisibility(float deltaTime)
{
	vector<cBullet*>::iterator bulletIterartor = this->theBullets.begin();
	while (bulletIterartor != this->theBullets.end())
	{
		// Store every bullet position to gameDataBullets string
		gameDataBullets += to_string((*bulletIterartor)->getSpritePos().x) + "," + to_string((*bulletIterartor)->getSpritePos().y) + ',';

		if ((*bulletIterartor)->getSpritePos().y <= -(*bulletIterartor)->getSpriteDimensions().w
			|| (*bulletIterartor)->getSpritePos().y >= renderWidth)
		{
			(*bulletIterartor)->setActive(false);
		}
		if ((*bulletIterartor)->isActive() == false)
		{
			bulletIterartor = this->theBullets.erase(bulletIterartor);
		}
		else
		{
			(*bulletIterartor)->update(deltaTime);
			++bulletIterartor;
		}
	}
}

void cSceneMgr::updateAlienShipsVisibility(float deltaTime)
{
	vector<cAlienShip>::iterator alienShipIterartor = theAlienShips.begin();

	if (alienShipIterartor == theAlienShips.end())	//if all alien ships are destroyed
	{
		this->updateGameState(END);
	}

	while (alienShipIterartor != theAlienShips.end())
	{
		// Store every alien Ship position to gameDataAlienSpaceShips string 
		gameDataAlienSpaceShips += to_string((alienShipIterartor)->getSpritePos().x) + ',' + to_string((alienShipIterartor)->getSpritePos().y) + ',';
		//gameDataAlienShips Data

		if ((alienShipIterartor)->getSpritePos().y <= -(alienShipIterartor)->getSpriteDimensions().w
			|| (alienShipIterartor)->getSpritePos().y >= renderWidth)
		{
			(alienShipIterartor)->setActive(false);
		}
		if ((alienShipIterartor)->isActive() == false)
		{
			alienShipIterartor = theAlienShips.erase(alienShipIterartor);
		}
		else
		{
			alienShipIterartor->update(deltaTime);
			++alienShipIterartor;
		}
	}
}

void cSceneMgr::updateAlienShipsFireRate(float deltaTime)
{
	for (vector<cAlienShip>::iterator alienShipIterator = theAlienShips.begin(); alienShipIterator != theAlienShips.end(); ++alienShipIterator)
	{
		alienShipIterator->update(deltaTime);

		//spawn bullet and change rate of fire (of the current alienShip)
		if (alienShipIterator->getRateOfFire() <= 0)
		{
			theBullets.push_back(new cBullet);
			int numBullets = theBullets.size() - 1;
			theBullets[numBullets]->setSpriteTranslation({ -2, -2 });
			theBullets[numBullets]->setTexture(theTextureMgr->getTexture("AlienShipBullet"));
			theBullets[numBullets]->setSpriteDimensions(theTextureMgr->getTexture("AlienShipBullet")->getTWidth(), theTextureMgr->getTexture("AlienShipBullet")->getTHeight());
			theBullets[numBullets]->setBulletVelocity({ 2, 2 });
			theBullets[numBullets]->setSpriteRotAngle(alienShipIterator->getSpriteRotAngle());
			theBullets[numBullets]->setSpriteScale({ -0.9f, -0.9f });
			theBullets[numBullets]->scaleSprite();
			theBullets[numBullets]->setSpritePos({ alienShipIterator->getSpritePos().x + alienShipIterator->getSpriteCentre().x - theBullets[numBullets]->getSpriteCentre().x
				,alienShipIterator->getSpritePos().y + alienShipIterator->getSpriteCentre().x * 2 + 30 }); 
			theBullets[numBullets]->setOrigin("Alien_Space_Ship");
			theBullets[numBullets]->setActive(true);
			alienShipIterator->setRateOfFire();

			theSoundMgr->getSnd("AlienSpaceShipShot")->play(0);
		}
	}
}

void cSceneMgr::updateCollisions(float deltaTime)
{
	for (vector<cBullet*>::iterator bulletIterator = theBullets.begin(); bulletIterator != theBullets.end(); ++bulletIterator)
	{
		//if bullets collide with the user's space ship
		if ((*bulletIterator)->collidedWith(&(*bulletIterator)->getBoundingRect(), &(theRocket).getBoundingRect())	//if a bullet collided
			&& (*bulletIterator)->getOrigin() == "Alien_Space_Ship"													//if bullet came from alien ship
			&& livesValue > 0)																						//if lives > 0
		{
			livesValue--;
			updateLives = true;
			//The bullet collided is inactive
			(*bulletIterator)->setActive(false);

			//play explosion sound
			if (livesValue >= 1)
				theSoundMgr->getSnd("explosion")->play(0);
			else
			{
				theSoundMgr->getSnd("playerLost")->play(0);
				this->updateGameState(END);
			}
		}

		//if bullets collide with each alien space ship 
		for (vector<cAlienShip>::iterator alienShipIterator = theAlienShips.begin(); alienShipIterator != theAlienShips.end(); ++alienShipIterator)
		{
			if ((alienShipIterator)->collidedWith(&(*alienShipIterator).getBoundingRect(), &(*bulletIterator)->getBoundingRect())
				&& (*bulletIterator)->getOrigin() == "User_Space_Ship")
			{
				scoreValue += 300;
				updateScore = true;
				theSoundMgr->getSnd("earnPoints")->play(0);
				//The bullet and alien spaceShip collided are inactive
				(*bulletIterator)->setActive(false);
				alienShipIterator->setActive(false);
			}
		}
	}
}

void cSceneMgr::updateRocket(float deltaTime)
{
	theRocket.update(deltaTime);
}

void cSceneMgr::autoSave(float deltaTime)
{
	//Autosave
	autoSaveTimer += deltaTime;

	//check if 2 seconds have passed
	if (autoSaveTimer >= 2)
	{
		autoSaveTimer = 0;
		gameDataRocket = to_string(theRocket.getSpritePos().x) + ',' + to_string(theRocket.getSpritePos().y) + ',';
		gameDataToFile = "rocket pos: " + gameDataRocket + "\n\n" +
			"Alien SpaceShips Pos: " + gameDataAlienSpaceShips + "\n\n" +
			"Bullets Pos: " + gameDataBullets;
		cout << gameDataToFile;

		// Check file is available
		if (!theRocketFile.openFile(ios::out) || !theAlienShipFile.openFile(ios::out) ||
			!theBulletsFile.openFile(ios::out) || !theUIFile.openFile(ios::out)) //open file for input output
		{
			cout << "Could not open specified files. '. Error " << SDL_GetError() << endl;
		}
		else
		{
			cout << "File '" << theRocketFile.getFileName() << "' opened for input!" << endl;
		}

		//Write data to files
		theRocketFile.writeDataToFile(gameDataRocket);
		theAlienShipFile.writeDataToFile(gameDataAlienSpaceShips);
		theBulletsFile.writeDataToFile(gameDataBullets);
		theUIFile.writeDataToFile(to_string(livesValue) + to_string(scoreValue));

		//Close Files
		theRocketFile.closeFile();
		theAlienShipFile.closeFile();
		theBulletsFile.closeFile();
		theUIFile.closeFile();
	}
}

void cSceneMgr::spawnAlienShips(int remainingShips, float height)
{
	int spawnedShips = 0;
	for (int i = 0; i <= remainingShips; i++)
	{
		if (80 + i * 100 <= 900)
		{
			//Set alien ship's state
			alienShip.setSpritePos({ 80 + i * 100, (int)height });
			alienShip.setTexture(theTextureMgr->getTexture("theAlienSpaceShip"));
			alienShip.scaleSprite();
			alienShip.setRateOfFire();
			alienShip.setInitialPos({ alienShip.getSpritePos().x, alienShip.getSpritePos().y });
			alienShip.initialize();
			//Add alien ship to the vector theAlienShips
			theAlienShips.push_back(alienShip);
			spawnedShips++;
		}
		else
		{
			cSceneMgr::spawnAlienShips(remainingShips - spawnedShips, height + 100);
			break;
		}
	}

}

void cSceneMgr::spawnRocket()
{
	theRocket.setSpritePos({ renderWidth / 2, 600 });
	theRocket.setTexture(theTextureMgr->getTexture("theRocket"));
	theRocket.setSpriteScale({ -0.6f, -0.6f });
	theRocket.scaleSprite();
}

void cSceneMgr::spawnRocket(string rocketData)
{
	string tempX, tempY;
	bool updateX = true, updateY = false;

	for (int i = 0; i < rocketData.size(); i++)
	{
		if (rocketData[i] != ',')	//if char = , set the other oposite axis
		{
			if (updateX)
			{
				tempX += rocketData[i];
			}
			if (updateY)
			{
				tempY += rocketData[i];
			}
		}
		else if (rocketData[i] == ',')
		{
			updateX = !updateX;
			updateY = !updateY;
		}
	}
	//Set the rocket position
	rocketX = stoi(tempX);
	rocketY = stoi(tempY);
	theRocket.setSpritePos({ rocketX, rocketY });
}

void cSceneMgr::updateXY(string alienShipsData)
{
	string tempX, tempY;

	bool updateX = true, updateY = false;

	for (int i = 0; i < alienShipsData.size(); i++)
	{
		if (alienShipsData[i] != ',')
		{
			if (updateX)
			{
				tempX += alienShipsData[i];
			}
			if (updateY)
			{
				tempY += alienShipsData[i];
			}
		}
		else
		{
			if (updateX)
			{
				xAxisData.push_back(stoi(tempX));
			}
			if (updateY)
			{
				yAxisData.push_back(stoi(tempY));
			}
			tempX = "";
			tempY = "";
			updateX = !updateX;
			updateY = !updateY;
		}
	}
}

void cSceneMgr::spawnAlienShips(vector<int> xAxis, vector<int> yAxis)
{
	//spawn every alien ship
	for (int i = 0; i < xAxis.size(); i++)
	{
		alienShip.setSpritePos({ xAxis[i], yAxis[i] });
		alienShip.setTexture(theTextureMgr->getTexture("theAlienSpaceShip"));
		alienShip.scaleSprite();
		alienShip.setRateOfFire();
		alienShip.setInitialPos({ alienShip.getSpritePos().x, alienShip.getSpritePos().y });
		alienShip.initialize();
		theAlienShips.push_back(alienShip);
	}
}

void cSceneMgr::spawnBullets(vector<int> xAxis, vector<int> yAxis)
{

	for (int i = 0; i < xAxis.size(); i++)
	{
		theBullets.push_back(new cBullet);
		int numBullets = theBullets.size() - 1;

		theBullets[numBullets]->setSpritePos({ xAxis[i], yAxis[i] });
		theBullets[numBullets]->setBoundingRect(theBullets[i]->getSpritePos());
		theBullets[numBullets]->setSpriteTranslation({ -2, -2 });
		theBullets[numBullets]->setTexture(theTextureMgr->getTexture("bullet"));
		theBullets[numBullets]->setSpriteDimensions(theTextureMgr->getTexture("bullet")->getTWidth(), theTextureMgr->getTexture("bullet")->getTHeight());
		theBullets[numBullets]->setBulletVelocity({ 2, 2 });
		theBullets[numBullets]->setSpriteRotAngle(theBullets[i]->getSpriteRotAngle());
		theBullets[numBullets]->setSpriteScale({ -0.9f,-0.9f });	//-0.9f,-0.9f
		theBullets[numBullets]->setOrigin("Alien_Space_Ship");
		theBullets[numBullets]->setActive(true);
		theBullets[numBullets]->setTexture(theTextureMgr->getTexture("AlienShipBullet"));
		theBullets[numBullets]->scaleSprite();
	}
}

void cSceneMgr::generateUI(string uiData)
{
	updateScore = true;
	updateLives = true;
	string tmpScore = "";

	livesValue = (int)uiData[0] - 48 ;

	for (int i = 1; i < uiData.size(); i++)
	{
		tmpScore += uiData[i];
	}

	scoreValue = stoi(tmpScore);
}


void cSceneMgr::updateInstructionsScene()
{
	// Check if buttons are pressed and update game state accordingly
	this->updateGameState("exit_btn", QUIT, this->theAreaClicked);
	this->updateGameState("play_btn", PLAYING, this->theAreaClicked);

	this->theAreaClicked = { 0 , 0 };
}

void cSceneMgr::updateEndScene()
{
	this->clearFiles();

	// Check if buttons are pressed
	this->updateGameState("exit_btn", QUIT, this->theAreaClicked);
	this->updateGameState("menu_btn", INSTRUCTIONS, this->theAreaClicked);


	// Reset Area Clicked
	theAreaClicked = { 0,0 };

	// Clear and respawn AlienShips
	theAlienShips.clear();

	//SpawnAlienSpaceShips(26, 60);
	spawnAlienShips(26, 60);

	// Clear Bullets
	theBullets.clear();

	scoreValue = 0;
	livesValue = 3;
	updateLives = true;
	updateScore = true;
}

void cSceneMgr::updatePlayingScene(float deltaTime)
{
	//update the rocket
	theRocket.update(deltaTime);

	//update the scene(game state)
	this->updateGameState("menu_btn", INSTRUCTIONS, this->theAreaClicked);

	//update the visubility of each bullet
	this->updateBulletsVisibility(deltaTime);

	//update alien space ships bisibility
	this->updateAlienShipsVisibility(deltaTime);

	//update rate of fire for every alien ship
	this->updateAlienShipsFireRate(deltaTime);

	//check for collisions / update ui accordingly
	this->updateCollisions(deltaTime);

	//save game object positions and ui values to files
	this->autoSave(deltaTime);
}

void cSceneMgr::loadPlayingSceneData()
{

	if (!theRocketFile.openFile(ios::in) || !theAlienShipFile.openFile(ios::in) 
		|| !theBulletsFile.openFile(ios::in) || !theUIFile.openFile(ios::in)) //open file for input output
	{
		cout << "Could not open specified files. Error " << SDL_GetError() << endl;
	}
	else
	{
		cout << "File '" << theRocketFile.getFileName() << "' opened for input!" << endl;
	}

	spawnRocket(theRocketFile.readDataFromFile());
	theRocketFile.closeFile();

	updateXY(theAlienShipFile.readDataFromFile());
	spawnAlienShips(xAxisData, yAxisData);
	theAlienShipFile.closeFile();

	xAxisData.clear();
	yAxisData.clear();

	updateXY(theBulletsFile.readDataFromFile());
	spawnBullets(xAxisData, yAxisData);
	theBulletsFile.closeFile();

	xAxisData.clear();
	yAxisData.clear();

	//method for updating ui here
	generateUI(theUIFile.readDataFromFile());
	theUIFile.closeFile();
}

bool cSceneMgr::updateEvents()
{
	SDL_Event event;

	//Keyboard events
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			theLoop = false;
		}
		switch (event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
		{
			case SDL_BUTTON_LEFT:
			{
				theAreaClicked = { event.motion.x, event.motion.y };
				break;
			}
		}
		case SDL_KEYDOWN:
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				theLoop = false;
				break;

			case SDLK_RIGHT:
			{
				theRocket.moveRight(5.0f, renderWidth - theRocket.getSpriteDimensions().w + 100);	//question
			}
			break;

			case SDLK_LEFT:
			{
				theRocket.moveLeft(5.0f);
			}
			break;

			case SDLK_SPACE:
			{
				//Shoot 
				if (theRocket.getRateOfFire() <= 0)
				{
					theBullets.push_back(new cBullet);
					int numBullets = theBullets.size() - 1;

					theRocket.shoot(theBullets, theTextureMgr, numBullets);
					//play shot sound
					theSoundMgr->getSnd("shot")->play(0);
				}
			}
			break;
			default:
				break;
			}
		default:
			break;
		}
		
		//Xbox 360 Controller events
		case SDL_CONTROLLERBUTTONDOWN:
		{
			switch (event.cbutton.button)
			{
				case SDL_CONTROLLER_BUTTON_A:
				{
					if (theRocket.getRateOfFire() <= 0)
					{
						theBullets.push_back(new cBullet);
						int numBullets = theBullets.size() - 1;

						theRocket.shoot(theBullets, theTextureMgr, numBullets);
						//play shot sound
						theSoundMgr->getSnd("shot")->play(0);
					}
					break;
				}
				case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
				{
					theRocket.moveLeft(5.0f);
					break;
				}
				case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
				{
					theRocket.moveRight(5.0f, renderWidth);
					break;
				}
			}
			break;
		}			
			case SDL_CONTROLLERDEVICEREMOVED:
			{
				cout << "Controller Disconected" << endl;
			}
			
			case SDL_CONTROLLERDEVICEADDED:
			{
				cout << "Controller Connected" << endl;
			}
		}
	}
	return theLoop;
}

void cSceneMgr::updateScenes(float deltaTime)
{
	// Clear playing data
	gameDataAlienSpaceShips = "";
	gameDataRocket = "";
	gameDataBullets = "";

	//Update Scenes
	switch (theGameState)
	{
	case QUIT:
	{
		theLoop = false;
	}
	break;
	case INSTRUCTIONS:
	{
		this->updateInstructionsScene();
	}
	break;
	case END:
	{
		this->updateEndScene();
	}
	break;
	case PLAYING:
	{
		this->updatePlayingScene(deltaTime);
	}
	}
}

void cSceneMgr::clearFiles()
{
	if (!clearedFiles)
	{
		if (!theRocketFile.openFile(ios::out) || !theAlienShipFile.openFile(ios::out)
			|| !theBulletsFile.openFile(ios::out) || !theUIFile.openFile(ios::out)) //open file for input output
		{
			cout << "Could not open files. Error: " << SDL_GetError() << endl;
		}
		else
		{
			cout << "File opened for input!" << endl;
		}

		//clear files
		theRocketFile.writeDataToFile("");
		theAlienShipFile.writeDataToFile("");
		theBulletsFile.writeDataToFile("");
		theUIFile.writeDataToFile("");

		//close files
		theRocketFile.closeFile();
		theAlienShipFile.closeFile();
		theBulletsFile.closeFile();
		theUIFile.closeFile();

		clearedFiles = true;
	}
}



void cSceneMgr::setRocket(cRocket theRocket)
{
	this->theRocket = theRocket;
}

void cSceneMgr::setLivesValue(int livesValue)
{
	this->livesValue = livesValue;
}

void cSceneMgr::setScoreValue(int scoreValue)
{
	this->livesValue = livesValue;
}


void cSceneMgr::setLoop(bool theloop)
{
	this->theLoop = theloop;
}

void cSceneMgr::setGameState(gameState theGameState)
{
	this->theGameState = theGameState;
}

void cSceneMgr::setGameTextList(vector<LPCSTR> gameTextList)
{
	this->gameTextList = gameTextList;
}

void cSceneMgr::setFiles(string rocketFileName, string alienShipsFileName, string bulletsName, string uIFileName)
{
	//set file names
	theUIFile.setFileName(uIFileName);
	theRocketFile.setFileName(rocketFileName);
	theAlienShipFile.setFileName(alienShipsFileName);
	theBulletsFile.setFileName(bulletsName);
}