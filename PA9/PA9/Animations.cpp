/*******************************************************************
Everything in the Animations.cpp, Animations.h, and Sprite sheets  *
was coded and created by Ryan Ortuno                               *
********************************************************************/
#include "Animations.h"

Animations::Animations(sf::Texture* texture, sf::Vector2u spriteCount, float animationSpeed)
{
	this->spriteCount = spriteCount;
	this->animationSpeed = animationSpeed;
	totalTime = 0.0f;
	currentSprite.x = 0;

	//Gets the size of the sprite sheet and devides it by num
	//of rows, and colms to make animation easier. 
	playerRect.width = texture->getSize().x / float(spriteCount.x);
	playerRect.height = texture->getSize().y / float(spriteCount.y);
}

Animations::~Animations()
{
}

/***********************************************************************
This function updates the animation using the global AVALUES to        *
use the correct animations. deltaTime is used to keep the animation    *
speed uniform across computers that vary in speed. rightFace is used   *
to check a bool to make sure if a player is on the left or right side  *
of the other and have the animation face the correct way.              *
************************************************************************/
bool Animations::update(int row, float deltaTime, bool rightFace)//needs to be updated with a interup for getting hit. maybe
{
	//Animating only works with punch and jump to finish the animation with one keypress. 
	bool animating = true;
	currentSprite.y = row;
	totalTime += deltaTime;

	if (totalTime >= animationSpeed) {
		totalTime -= animationSpeed;
		currentSprite.x++;

		if (row == ABACK) {
			if (currentSprite.x >= 5) {
				currentSprite.x = 0;
			}
		}
		else if (row == ADEATH) {
			if (currentSprite.x >= 6) {
				currentSprite.x = 6;
			}
		}
		else if (row == AFORWARD) {
			if (currentSprite.x >= 4) {
				currentSprite.x = 0;
			}
		}
		else if (row == AHIT) {
			if (currentSprite.x >= 4) {
				currentSprite.x = 0;
			}
		}
		else if (row == APUNCH) {
			if (currentSprite.x >= 6) {
				currentSprite.x = 0;
				animating = false;
			}
		}
		else if (row == AJUMP) {
			if (currentSprite.x >= 5) {
				currentSprite.x = 0;
				animating = false;
			}
		}
		else if (row == ABLOCK) {
			if (currentSprite.x >= 0) {
				currentSprite.x = 0;
			}
		}
		else if (row == AIDLE) { //change to else later for static idle when a eventkey is not pressed. 
			if (currentSprite.x >= 4) {
				currentSprite.x = 0;
			}
		}
	}

	playerRect.top = currentSprite.y * playerRect.height;

	//Makes the animation flip it's facing depending  
	//on position of the players.                      
	if (rightFace) {
		playerRect.left = currentSprite.x * playerRect.width;
		playerRect.width = abs(playerRect.width);
	}
	else {
		playerRect.left = (currentSprite.x + 1) * abs(playerRect.width);
		playerRect.width = -abs(playerRect.width);
	}

	return animating;	//Sets whether the animation is done or not. True for done, false for not done.


}

/*****************************************************
 This funtion is a overloaded function that updates  *
 the animated background for the game.               *
 *****************************************************/
void Animations::update(int row, float deltaTime)
{
	currentSprite.y = row;
	totalTime += deltaTime;

	if (totalTime >= animationSpeed) {
		totalTime -= animationSpeed;
		currentSprite.x++;

		if (row == ABACKGROUND) {
			if (currentSprite.x >= 13) {
				currentSprite.x = 0;
			}
		}
	}
	playerRect.top = currentSprite.y * playerRect.height;
	playerRect.left = currentSprite.x * playerRect.width;
}

void testFunctions()
{

	//Pressing any that is not assigned to an event
	//will not trigger anything.
	RectangleShape test(sf::Vector2f(200.0f, 200.0f));
	RectangleShape test2(sf::Vector2f(200.0f, 200.0f));
	RectangleShape test3(sf::Vector2f(0.0f, 200.0f));
	cout << leftPunch(test, test2) << endl;
	cout << leftPunch(test3, test) << endl;
	cout << rightPunch(test, test2) << endl;
	cout << rightPunch(test, test3) << endl;
	cout << customCollision(test, test2, 0.0f) << endl;
	cout << customCollision(test, test3, 0.5f) << endl;
}
