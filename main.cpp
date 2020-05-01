/**********************************************************************
Programmer: Ryan Ortuno                                               *
Class: CptS 122, Spring, 2020;                                        *
Programming Assignment: PA 9                                          *
Date: April 24th, 2020                                                *
Description: This program lets players play a Mortal Kombat type      *
game. This goal is to punch the other player's charactor in the face  *
enough time to kill them.                                             *
***********************************************************************/
//#include "Character.h"
#include "Animations.h"

//This is for changing the direction of the character jumping 
bool goingUP = true;
bool goingDOWN = false;
bool goingUP2 = true;
bool goingDOWN2 = false;

int main() {

	sf::RenderWindow window(sf::VideoMode(1100, 600), "Cyborg vs BlockyMan!!", sf::Style::Close | sf::Style::Resize);
	sf::RenderWindow startWindow(sf::VideoMode(1100, 600), "Start Window", sf::Style::Close | sf::Style::Resize);

	/******************************************************************************************************
	This makes the rectangle the Sprite shows up in. The native pixel size for the Sprites is (125,125),  *
	but by changing th e Vector2f() the image will grow to fit propotionally.                             *
	I'm going to guess to make the hit box about (110, 200) pixels with all the animations, but increase  *
	it to (200,200) pixels when punching. This is because all the animations are set farther back to      *
	make room for the length of the punch.                                                                *
	*******************************************************************************************************/
	sf::RectangleShape player1(sf::Vector2f(200.0f, 200.0f)); //cyborg
	sf::RectangleShape player2(sf::Vector2f(200.0f, 200.0f)); //blocky
	sf::RectangleShape playerBackground(sf::Vector2f(1100, 600.0f));
	sf::RectangleShape startBackground(sf::Vector2f(1100.0f, 600.0f));
	Character p1, p2;

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
	rules.setString("How to play:\nCyborg controls: A - Left W - Jump D - Right Y - Block T - Punch\nBlockyman controls: Left Arrow - Left Right Arrow - Right Up Arrow - Jump / - Block . - Punch\n\nEach player starts with 100 HP\nThe first player to make their opponent lose all their health wins!\nPress Space to start.\n");
	rules.setPosition(100.0f, 150.0f);

	endText.setFont(font);
	endText.setOutlineColor(sf::Color::Black);
	endText.setOutlineThickness(7);
	endText.setCharacterSize(50);
	endText.setPosition(400.0f, 110.0f);

	//Set up health string
	p1.setHP(100);
	p2.setHP(100);
	stringstream ss, ss2;
	string s1, s2;
	ss << p1.getHP();
	ss >> s1;
	ss2 << p2.getHP();
	ss2 >> s2;
	string hpstring = "Cyborg's Health: ";
	hpstring += s1;
	string hpstring2 = "                                                                                                                                                                Blocky's  Heatlh: ";
	hpstring2 += s2;
	hpstring += hpstring2;

	//sets up health text at top of game screen
	health.setFont(font);
	health.setOutlineColor(sf::Color::Black);
	health.setOutlineThickness(4);
	health.setCharacterSize(20);
	health.setString(hpstring);
	health.setPosition(50.0f, 50.0f);

	//This changes the position of the Sprites
	player1.setPosition(450.0f, 400.0f);
	player2.setPosition(450.0f, 400.0f);
	playerBackground.setPosition(0.0f, 0.0f);

	/**************************************************************************
	This loads the Sprite sheets for the playable charactors, and background  *
	This is heavy on processing and needs to be done before the game starts.  *
	***************************************************************************/
	sf::Texture player1Texture, player2Texture, background, start;
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
	Animations p1animation(&player1Texture, sf::Vector2u(7, 8), .12f);
	Animations p2animation(&player2Texture, sf::Vector2u(7, 8), .12f);
	Animations backgroundAnimation(&background, sf::Vector2u(13, 1), 0.09f);
	
	//Sets up for the deltaTime to control smooth and even animations
	sf::Clock clock;
	float deltaTime = 0.0f;

	bool finishPunch1 = false, finishPunch2 = false, finishJump1 = false, finishJump2 = false;
	int p1press = 0, p2press = 0;


	//Starting Window opens
	while (startWindow.isOpen())
	{
		//Game window opens
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			
			startWindow.close();

			while (window.isOpen()) {

				deltaTime = clock.restart().asSeconds();

				sf::Event event;
				while (window.pollEvent(event)) {
					if (event.type == Event::Closed)
						window.close();
				}

				backgroundAnimation.update(ABACKGROUND, deltaTime);

				/***********************************************************************************
				This controls The Cyborg! The punch and jump animation still needs work though     *
				We need a position bool check to make sure the players' are on the left or right!  * position bool is unneeded, since collision prevents players from passing each other. -james
				************************************************************************************/
				if (Keyboard::isKeyPressed(Keyboard::T) || finishPunch1) {
					/*
					When T is pressed finishedPunch1 becomes equal to true until the sprite
					reaches the final frame making finishedPunch1 equal false to stop the animation.
					*/
					
					finishPunch1 = p1animation.update(APUNCH, deltaTime, true);

					if (leftPunch(player1, player2) && !finishPunch1)
					{
						if (Keyboard::isKeyPressed(Keyboard::Slash))
						{
							p2.setHP(p2.getHP() - 5);
						}
						else
						{
							p2.setHP(p2.getHP() - 10);
						}
						cout << "Player2 HP: " << p2.getHP() << endl;

						ss.clear();
						ss2.clear();
						ss << p1.getHP();
						ss >> s1;
						ss2 << p2.getHP();
						ss2 >> s2;
						hpstring = "Cyborg's Health: ";
						hpstring += s1;
						hpstring2 = "                                                                                                                                                                Blocky's  Heatlh: ";
						hpstring2 += s2;
						hpstring += hpstring2;

						cout << hpstring << endl;
						health.setString(hpstring);
					}
				}
				else  if (Keyboard::isKeyPressed(Keyboard::Y)) {
					p1animation.update(ABLOCK, deltaTime, true);
				}
				else if (Keyboard::isKeyPressed(Keyboard::W) || finishJump1) {
					/*
					When T is pressed finishJump1 becomes equal to true until the sprite
					reaches the final frame making finishJump1 equal false to stop the animation.
					*/
					//cout << "P1Y: " << player1.getPosition().y << endl;
					//cout << "P2Y: " << player2.getPosition().y << endl;

					/* if (goingUP) {
						 player1.setPosition(player1.getPosition().x, player1.getPosition().y - 1);
						 cout << "GOING UP\n";
						 if (player1.getPosition().y <= 200)
						 {
							 goingUP = false;
							 goingDOWN = true;
						 }
					 }

					 if (goingDOWN) {
						 player1.setPosition(player1.getPosition().x, player1.getPosition().y + 1);
						 cout << "GOING DOWN\n";
						 if (player1.getPosition().y >= 400)
						 {
							 goingUP = true;
							 goingDOWN = false;
						 }
					 }

					 finishJump1 = p1animation.update(AJUMP, deltaTime, true);*/
				}
				else if (Keyboard::isKeyPressed(Keyboard::D)) {
					p1animation.update(AFORWARD, deltaTime, true);

					if (player1.getPosition().x < WINDOWLENGTH - 150 && player1.getPosition().x < WINDOWLENGTH) //checking that character is in bounds.
					{
						if (!customCollision(player1, player2, 1)) { //collision test distance is greater than the actual move distance since the boxes would be stuck in each other otherwise.
							player1.setPosition(player1.getPosition().x + .75, player1.getPosition().y);
						}
					}
				}
				else if (Keyboard::isKeyPressed(Keyboard::A)) {
					p1animation.update(ABACK, deltaTime, true);
					if (player1.getPosition().x > 0 && player1.getPosition().x > -100)
					{
						if (!customCollision(player1, player2, -1))
							player1.setPosition(player1.getPosition().x - .75, player1.getPosition().y);
					}
				}
				else {
					p1animation.update(AIDLE, deltaTime, true);
				}

				/***********************************************************************************
				This controls BlockyMan! The punch and jump animation still needs work though      *
				We need a position bool check to make sure the players' are on the left or right!  *
				************************************************************************************/
				if (Keyboard::isKeyPressed(Keyboard::Period) || finishPunch2) {
					/*
					When T is pressed finishPunch2 becomes equal to true until the sprite
					reaches the final frame making finishPunch2 equal false to stop the animation.
					*/
					
					finishPunch2 = p2animation.update(APUNCH, deltaTime, false);

					//Once the punch is finish player takes damage
					if (rightPunch(player2, player1) && !finishPunch2)
					{
						//If other player blocks
						if (Keyboard::isKeyPressed(Keyboard::Y))
						{
							p1.setHP(p1.getHP() - 5);
						}
						else
						{
							p1.setHP(p1.getHP() - 10);
						}

						//Changes HP text
						cout << "Player1 HP: " << p1.getHP() << endl;
						ss.clear();
						ss2.clear();
							ss << p1.getHP();
							ss >> s1;
							ss2 << p2.getHP();
							ss2 >> s2;
							hpstring = "Cyborg's Health: ";
							hpstring += s1;
							hpstring2 = "                                                                                                                                                                Blocky's  Heatlh: ";
							hpstring2 += s2;
							hpstring += hpstring2;

							health.setString(hpstring);
					}
				}
				else  if (Keyboard::isKeyPressed(Keyboard::Slash)) {
					p2animation.update(ABLOCK, deltaTime, false);
				}
				else if (Keyboard::isKeyPressed(Keyboard::Up) || finishJump2) {
					/*
					When T is pressed finishJump2 becomes equal to true until the sprite
					reaches the final frame making finishJump2 equal false to stop the animation.
					*/
					//cout << "P1Y: " << player1.getPosition().y << endl;
					//cout << "P2Y: " << player2.getPosition().y << endl;

					/*if (goingUP2) {
						player2.setPosition(player2.getPosition().x, player2.getPosition().y - 1);
						cout << "GOING UP\n";
						if (player2.getPosition().y <= 200)
						{
							goingUP2 = false;
							goingDOWN2 = true;
						}
					}

					if (goingDOWN2) {
						player2.setPosition(player2.getPosition().x, player2.getPosition().y + 1);
						cout << "GOING DOWN\n";
						if (player2.getPosition().y >= 400)
						{
							goingUP2 = true;
							goingDOWN2 = false;
						}
					}*/
					//finishJump2 = p2animation.update(AJUMP, deltaTime, false);
				}
				else if (Keyboard::isKeyPressed(Keyboard::Left)) {
					p2animation.update(AFORWARD, deltaTime, false);
					if (player2.getPosition().x > -100)
					{
						if (!customCollision(player1, player2, 1)) //float values for BlockyMan are backwards because of how the test collision functionality is set up. Should still work, though.
							player2.setPosition(player2.getPosition().x - .75, player2.getPosition().y);
					}
				}
				else if (Keyboard::isKeyPressed(Keyboard::Right)) {
					p2animation.update(ABACK, deltaTime, false);
					if (player2.getPosition().x < WINDOWLENGTH - 200)
					{
						if (!customCollision(player1, player2, -1))
							player2.setPosition(player2.getPosition().x + .75, player2.getPosition().y);
					}
				}
				else {
					p2animation.update(AIDLE, deltaTime, false);
				}

				
				

				//Assigns the correct animation to the player rectanble
				playerBackground.setTextureRect(backgroundAnimation.playerRect);
				player1.setTextureRect(p1animation.playerRect);
				player2.setTextureRect(p2animation.playerRect);

				window.clear();
				window.draw(playerBackground);
				window.draw(health);
				if (p2.getHP() <= 0 || p1.getHP() <= 0)
				{
					if (p2.getHP() <= 0)
					{
						endText.setString("Cyborg Wins!");
					}
					else if(p1.getHP() <= 0)
					{
						endText.setString("Blocky Wins!");
					}
					window.draw(endText);
				}
				window.draw(player1);
				window.draw(player2);
				window.display();
			}
		}
		
		startWindow.clear();
		startWindow.draw(startBackground);
		startWindow.draw(text);
		startWindow.draw(rules);
		startWindow.display();
	}
}