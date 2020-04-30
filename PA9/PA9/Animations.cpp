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
			if (currentSprite.x >= 7) {
				currentSprite.x = 0;
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



bool testCollision(sf::RectangleShape shape1, sf::RectangleShape shape2, char dir, int dist)
{
	dir = toupper(dir);

	sf::Vector2f pos1 = shape1.getPosition();
	if (dir == 'W')
		pos1.y -= dist;
	if (dir == 'A')
		pos1.x -= dist;
	if (dir == 'S')
		pos1.y += dist;
	if (dir == 'D')
		pos1.x += dist;
	sf::Vector2f dimension1 = shape1.getSize();
	sf::Vector2f pos2 = shape2.getPosition();
	sf::Vector2f dimension2 = shape2.getSize();

	bool checkX = false, checkY = false;
	//checkX is checked true if one shape or the other is within X bounds, and vice versa for checkY

	//check if shape2 is within bounds of shape1
	//X 1
	if ((pos2.x >= pos1.x) && (pos2.x < (pos1.x + dimension1.x)))
		checkX = true; //the origin of object 2 is within X bounds of object 1.

	//Y 1
	if ((pos2.y >= pos1.y) && (pos2.y < (pos1.y + dimension1.y)))
		checkY = true; //the origin of object 2 is within Y bounds of object 1.

	//check if shape1 is within bounds of shape2
	//X2
	if ((pos1.x >= pos2.x) && (pos1.x < (pos2.x + dimension2.x)))
		checkX = true; //the origin of object 1 is within X bounds of object 2.

	//Y2
	if ((pos1.y >= pos2.y) && pos1.y < (pos2.y + dimension2.y))
		checkY = true; //the origin of object 1 is within Y bounds of object 2.

	if (checkX == true && checkY == true)
		return true;
	else
		return false;
}