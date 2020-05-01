/**********************************************************************
Programmers: Ryan Ortuno, James Whyatt, Hannah Brickwood              *
Class: CptS 122, Spring, 2020;                                        *
Programming Assignment: PA 9                                          *
Date: April 24th, 2020                                                *
Description: This program lets players play a Mortal Kombat type      *
game. This goal is to punch the other player's charactor in the face  *
enough time to kill them.                                             *
***********************************************************************/

/********************************************************************************
Unless stated otherwise, everything here in main was programmed by Ryan Ortuno  *
*********************************************************************************/
#include "Animations.h"

int main() {
	testFunctions();
	bool debugMode = false; //SET TO FALSE FOR RELEASE VERSION - James Whyatt
	/***************************************************************************************
	Play with animationSpeed and playerSpeed, to speed up the characters' movement speeds  *
	and animation speeds. It's pretty enjoyable lol                                        *
	****************************************************************************************/
	float animationSpeed = .1f;
	float playerSpeed = .5f;
	sf::Music music;
	if (!music.openFromFile("music/DragonForce.ogg"))
		return 0;//No music
	music.play();

	sf::RenderWindow window(sf::VideoMode(1100, 600), "Cyborg vs BlockyMan!!", sf::Style::Close | sf::Style::Resize);
	sf::RenderWindow startWindow(sf::VideoMode(1100, 600), "Start Window", sf::Style::Close | sf::Style::Resize);

	/********************************************************************************************
	These create boxes for the players and background to show up it. Adjusting the values will  *
	shrink of expand the chararters                                                             *
	*********************************************************************************************/
	sf::RectangleShape player1(sf::Vector2f(200.0f, 200.0f)); //cyborg
	sf::RectangleShape player2(sf::Vector2f(200.0f, 200.0f)); //blocky
	sf::RectangleShape playerBackground(sf::Vector2f(1100, 600.0f));
	sf::RectangleShape startBackground(sf::Vector2f(1100.0f, 600.0f));
	
	//Text
	sf::Text text;
	sf::Text rules;
	sf::Text health;
	sf::Text endText;

	//Font
	sf::Font font;
	if (!font.loadFromFile("fonts/impact.ttf"))
	{
		cout << "Font doesnt work.\n";
	}

	//Set up text
	//Hannah Brickwood.///////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////
	text.setFont(font);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(5);
	text.setCharacterSize(30);
	text.setString("Welcome to Blockyman Vs. Cyborg!\n");
	text.setPosition(100.0f, 110.0f);

	rules.setFont(font);
	rules.setOutlineColor(sf::Color::Black);
	rules.setOutlineThickness(4);
	rules.setCharacterSize(25);
	rules.setString("How to play:\nCyborg controls:\n A - Left W - Jump D - Right Y - Block T - Punch S - Play dead\n\nBlockyman controls:\n Left Arrow - Left Right Arrow - Right Up Arrow - Jump / - Block . - Punch Down Arrow - Play dead\n\nEach player starts with 100 HP\nPunching removes 10 health, while successfully blocking heals 3 health!\nThe first player to make their opponent lose all their health wins!\nPress Space to start.\n");
	rules.setPosition(100.0f, 150.0f);

	endText.setFont(font);
	endText.setOutlineColor(sf::Color::Black);
	endText.setOutlineThickness(7);
	endText.setCharacterSize(50);
	endText.setPosition(400.0f, 110.0f);
	//////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////

	//This changes the position of the Sprites
	player1.setPosition(450.0f, 400.0f);
	player2.setPosition(450.0f, 400.0f);
	playerBackground.setPosition(0.0f, 0.0f);

	/**************************************************************************
	This loads the Sprite sheets for the playable charactors, and background  *
	This is heavy on processing and needs to be done before the game starts.  *
	***************************************************************************/
	sf::Texture player1Texture, player2Texture, background, winTexture, start;
	player1Texture.loadFromFile("textures/Cyborg.png");
	player2Texture.loadFromFile("textures/BlockMan.png");
	background.loadFromFile("textures/FightingStage.png");
	start.loadFromFile("textures/betterbackground.jpg");

	//Assigns the textures to the player and background
	player1.setTexture(&player1Texture);
	player2.setTexture(&player2Texture);
	playerBackground.setTexture(&background);
	startBackground.setTexture(&start);

	//Instantiates the Animation class, DO NOT CHANGE THE VECTOR2U HERE, and controls the animation speed. 
	Animations p1animation(&player1Texture, sf::Vector2u(7, 8), animationSpeed);
	Animations p2animation(&player2Texture, sf::Vector2u(7, 8), animationSpeed);
	Animations backgroundAnimation(&background, sf::Vector2u(13, 1), 0.09f);
	Animations win(&winTexture, sf::Vector2u(1, 2), 0.09f);

	stringstream ss, ss2;
	string s1, s2;
	ss << p1animation.getHP();
	ss >> s1;
	ss2 << p2animation.getHP();
	ss2 >> s2;
	string hpstring = "Cyborg's Health: ";
	hpstring += s1;
	string hpstring2 = "                                                                                                                                                             Blockyman's  Heatlh: ";
	hpstring2 += s2;
	hpstring += hpstring2;

	//sets up health text at top of game screen
	health.setFont(font);
	health.setOutlineColor(sf::Color::Black);
	health.setOutlineThickness(4);
	health.setCharacterSize(20);
	health.setString(hpstring);
	health.setPosition(50.0f, 50.0f);

	//Self explaining
	if (debugMode == true)
	{
		p1animation.debugOn();
		p2animation.debugOn();
		player1.setOutlineColor(sf::Color::White);
		player1.setOutlineThickness(5);
		player2.setOutlineColor(sf::Color::White);
		player2.setOutlineThickness(5);
	}

	//Sets up for the deltaTime to control smooth and even animations
	sf::Clock clock;
	float deltaTime = 0.0f;

	//Makes sure the animations follow through to the end.
	bool finishPunch1 = false, finishPunch2 = false, finishJump1 = false, finishJump2 = false;
	bool finishHit1 = false, finishHit2 = false, finishDeath1 = false, finishDeath2 = false;

	bool hit1 = false, hit2 = false; //hit1 and hit2 are to prevent players from taking massive damage from 1 punch.

	//Starting Window opens
	while (startWindow.isOpen())
	{
		sf::Event event1;
		while (startWindow.pollEvent(event1)) {
			if (event1.type == Event::Closed)
				startWindow.close();
		}

		startWindow.clear();
		startWindow.draw(startBackground);
		startWindow.draw(text);
		startWindow.draw(rules);
		startWindow.display();

		//Game window opens
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			startWindow.close();
			/*****************************************************************************************
			******************************  GAME STARTS HERE  ****************************************
			******************************************************************************************/
			while (window.isOpen()) {

				deltaTime = clock.restart().asSeconds();
				sf::Event event;
				while (window.pollEvent(event)) {
					if (event.type == Event::Closed)
						window.close();
				}

				backgroundAnimation.update(ABACKGROUND, deltaTime);

				/***********************************************************************************
				This controls The Cyborg! The W key makes the charater play dead lol               *
				************************************************************************************/
				if (p1animation.getHP() <= 0 || finishDeath1) {
					finishDeath1 = p1animation.update(ADEATH, deltaTime, true);

				}
				else if (Keyboard::isKeyPressed(Keyboard::T) || finishPunch1) {
					system("cls");
					p1animation.removeBlock();
					//Hannah Brickwood.///////////////////////////////////////////////////////////////////
					//////////////////////////////////////////////////////////////////////////////////////
					ss.clear();
					ss2.clear();
					ss << p1animation.getHP();
					ss2 << p2animation.getHP();
					ss >> s1;
					ss2 >> s2;
					string hpstring = "Cyborg's Health: ";
					hpstring += s1;
					hpstring += "                                                                                                                                                             Blockyman's  Heatlh: ";
					hpstring += s2;
					cout << hpstring << endl;
					health.setString(hpstring);
					//////////////////////////////////////////////////////////////////////////////////////
					//////////////////////////////////////////////////////////////////////////////////////
					/**********************************************************************************
					When T is pressed finishedPunch1 becomes equal to true until the sprite           *
					reaches the final frame making finishedPunch1 equal false to stop the animation.  *
					***********************************************************************************/
					p1animation.placePunch(true, player1);
					finishPunch1 = p1animation.update(APUNCH, deltaTime, true);
					if (!finishPunch1) {
						hit1 = false;
						p1animation.removePunch();
					}
				}
				else  if (Keyboard::isKeyPressed(Keyboard::Y)) {
					p1animation.update(ABLOCK, deltaTime, true);
					p1animation.placeBlock(true, player1);

				}
				else if (hit2 || finishHit1) {
					finishHit1 = !p1animation.update(AHIT, deltaTime, true);

				}
				else if (Keyboard::isKeyPressed(Keyboard::S) || finishJump1) {
					/**************************************************************
					This was going to be a jump function, but now it's play dead  *
					***************************************************************/
					p1animation.update(ADEATH, deltaTime, true);
				}
				else if (Keyboard::isKeyPressed(Keyboard::D)) {
					p1animation.update(AFORWARD, deltaTime, true);

					//Hannah Brickwood.///////////////////////////////////////////////////////////////////
					//////////////////////////////////////////////////////////////////////////////////////
					if (player1.getPosition().x < WINDOWLENGTH - 150 && player1.getPosition().x < WINDOWLENGTH) //checking that character is in bounds.
					{
						if (!customCollision(player1, player2, 1)) //collision test distance is greater than the actual move distance since the boxes would be stuck in each other otherwise.
							player1.setPosition(player1.getPosition().x + playerSpeed, player1.getPosition().y);
					}
					//////////////////////////////////////////////////////////////////////////////////////
					//////////////////////////////////////////////////////////////////////////////////////
				}
				else if (Keyboard::isKeyPressed(Keyboard::A)) {
					p1animation.update(ABACK, deltaTime, true);

					//Hannah Brickwood.///////////////////////////////////////////////////////////////////
					//////////////////////////////////////////////////////////////////////////////////////
					if (player1.getPosition().x > 0 && player1.getPosition().x > -100)
					{
						if (!customCollision(player1, player2, -1))
							player1.setPosition(player1.getPosition().x - playerSpeed, player1.getPosition().y);
					}
					//////////////////////////////////////////////////////////////////////////////////////
					//////////////////////////////////////////////////////////////////////////////////////
				}
				else {
					p1animation.update(AIDLE, deltaTime, true);
					p1animation.removeBlock();
				}
				/***********************************************************************************
				This controls BlockyMan! The Up key makes the charater play dead lol               *
				************************************************************************************/
				if (p2animation.getHP() <= 0 || finishDeath2) {
					finishDeath2 = !p2animation.update(ADEATH, deltaTime, false);
				}
				else if (Keyboard::isKeyPressed(Keyboard::Period) || finishPunch2) {
					system("cls");
					//Hannah Brickwood.///////////////////////////////////////////////////////////////////
					//////////////////////////////////////////////////////////////////////////////////////
					ss.clear();
					ss2.clear();
					ss << p1animation.getHP();
					ss2 << p2animation.getHP();
					ss >> s1;
					ss2 >> s2;
					string hpstring = "Cyborg's Health: ";
					hpstring += s1;
					hpstring += "                                                                                                                                                             Blockyman's  Heatlh: ";
					hpstring += s2;
					cout << hpstring << endl;
					health.setString(hpstring);
					//////////////////////////////////////////////////////////////////////////////////////
					//////////////////////////////////////////////////////////////////////////////////////
					/**********************************************************************************
					When . is pressed finishedPunch2 becomes equal to true until the sprite           *
					reaches the final frame making finishedPunch2 equal false to stop the animation.  *
					***********************************************************************************/
					p2animation.placePunch(false, player2);
					finishPunch2 = p2animation.update(APUNCH, deltaTime, false);
					if (!finishPunch2) {
						hit2 = false;
						p2animation.removePunch();
					}
				}
				else  if (Keyboard::isKeyPressed(Keyboard::Slash)) {
					p2animation.update(ABLOCK, deltaTime, false);
					p2animation.placeBlock(false, player2);
					p2animation.removePunch();
				}
				else if (hit1 || finishHit2) {

					finishHit2 = !p2animation.update(AHIT, deltaTime, false);
				}
				else if (Keyboard::isKeyPressed(Keyboard::Down) || finishJump2) {
					/**************************************************************
					This was going to be a jump function, but not it's play dead  *
					***************************************************************/
					p2animation.update(ADEATH, deltaTime, false);
				}
				else if (Keyboard::isKeyPressed(Keyboard::Left)) {
					p2animation.update(AFORWARD, deltaTime, false);

					//This if and nested if statment was made by Hannah Brickwood./////////////////////////////////////////////////////////////////////////////////////////////////////////////
					///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					if (player2.getPosition().x > -100)
					{
						if (!customCollision(player1, player2, 1))
							player2.setPosition(player2.getPosition().x - playerSpeed, player2.getPosition().y);
					}
					///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				}
				else if (Keyboard::isKeyPressed(Keyboard::Right)) {
					p2animation.update(ABACK, deltaTime, false);

					//This if and nested if statment was made by Hannah Brickwood./////////////////////////////////////////////////////////////////////////////////////////////////////////////
					///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					if (player2.getPosition().x < WINDOWLENGTH - 200)
					{
						if (!customCollision(player1, player2, -1))
							player2.setPosition(player2.getPosition().x + playerSpeed, player2.getPosition().y);
					}
					///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				}
				else {
					p2animation.update(AIDLE, deltaTime, false);
					p2animation.removeBlock();
				}

				//Assigns the correct animation to the player rectanble
				playerBackground.setTextureRect(backgroundAnimation.playerRect);
				player1.setTextureRect(p1animation.playerRect);
				player2.setTextureRect(p2animation.playerRect);

				/******************************************************
				Everything below here was programmed by James Whyatt  *
				*******************************************************/
				if (leftPunch(p1animation.getPunch(), player2) && rightPunch(p2animation.getPunch(), player1)) {
					p1animation.removePunch();
					p2animation.removePunch();
				}
				else if (leftPunch(p1animation.getPunch(), player2) && hit1 == false)
				{
					if (testCollision(p1animation.getPunch(), p2animation.getBlock(), '\0', 0)) //checking if the punch hits the block.
					{
						p2animation.blockDamage(true);
						if (debugMode == true)
							cout << "Blockyman takes 3 damage\n";
						system("cls");
						cout << "The Cyborg HP: " << p1animation.getHP() << "\tBlockyman HP: " << p2animation.getHP() << endl;

					}
					else //if the attack is not blocked.
					{
						p2animation.punchDamage(true);
						if (debugMode == true)
							cout << "Blockyman takes 10 damage\n";
						system("cls");
						cout << "The Cyborg HP: " << p1animation.getHP() << "\tBlockyman HP: " << p2animation.getHP() << endl;
					}
					hit1 = true;
				}
				if (rightPunch(p2animation.getPunch(), player1) && hit2 == false)
				{
					if (testCollision(p2animation.getPunch(), p1animation.getBlock(), '\0', 0))
					{
						p1animation.blockDamage(true);
						if (debugMode == true)
							cout << "Cyborg takes 3 damage\n";
						system("cls");
						cout << "The Cyborg HP: " << p1animation.getHP() << "\tBlockyman HP: " << p2animation.getHP() << endl;
					}
					else
					{
						p1animation.punchDamage(true);
						if (debugMode == true)
							cout << "Cyborg takes 10 damage\n";
						system("cls");
						cout << "The Cyborg HP: " << p1animation.getHP() << "\tBlockyman HP: " << p2animation.getHP() << endl;
					}
					hit2 = true;
				}

				window.clear();
				window.draw(playerBackground);
				window.draw(health);
				if (p2animation.getHP() <= 0 || p1animation.getHP() <= 0)
				{
					if (p2animation.getHP() <= 0)
					{
						endText.setString("Cyborg Wins!");
					}
					else if (p1animation.getHP() <= 0)
					{
						endText.setString("Blocky Wins!");
					}
					window.draw(endText);
				}
				window.draw(player1);
				window.draw(player2);

				if (debugMode == true)
				{
					window.draw(p1animation.getBlock());
					window.draw(p1animation.getPunch());
					window.draw(p2animation.getBlock());
					window.draw(p2animation.getPunch());
				}
				window.display();
			}
		}
	}
}