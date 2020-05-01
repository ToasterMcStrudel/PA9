#pragma once
/***************************************************************************
Everything in the Character.cpp and Character.h was coded by James Whyatt  *
****************************************************************************/

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <ctime>

#define WINDOWHEIGHT 600
#define WINDOWLENGTH 1122
#define HPCONST 100

//HPCONST used as temp, feel free to change in future versions
#define BLOCKCONST 0.25
//BLOCKCONST not used yet, could be changed later on in development for balance.

using namespace std;
using namespace sf;

class Character
{
private:
	int HP;
	int damage;
	int block;
	sf::RectangleShape hitBox; //for being hit, also hitBox.getPosition() is basis for character's position.
	sf::RectangleShape punchBox; //for hitting
	sf::RectangleShape blockBox; //for blocking

public:
	Character();
	int getHP();
	void setHP(int val);

	void punchDamage(bool hit);
	void blockDamage(bool hit);

	//setter and getter blocks. sf::RectangleShape functions return the entire object, for use with collision functions.

	//setters and getters for hitBox
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f newPos);
	sf::Vector2f getDimensions();
	void setDimensions(sf::Vector2f newSize);
	sf::RectangleShape getBody();

	//setters and getters for punchBox
	sf::Vector2f getPunchPos();
	void setPunchPos(sf::Vector2f newPos);
	sf::Vector2f getPunchSize();
	void setPunchSize(sf::Vector2f newSize);
	sf::RectangleShape getPunch();

	//setters and getters for blockBox
	sf::Vector2f getBlockPos();
	void setBlockPos(sf::Vector2f newPos);
	sf::Vector2f getBlockSize();
	void setBlockSize(sf::Vector2f newSize);
	sf::RectangleShape getBlock();

	//debug function, for debugging purposes.
	void debugOn();

	void placePunch(bool facing, sf::RectangleShape hitBox);
	void removePunch();
	void placeBlock(bool facing, sf::RectangleShape hitBox);
	void removeBlock();
};

//Function declarations for collision detection - defined in source.cpp.
//Collision Testing functions - not part of the Animations class.

bool testCollision(sf::RectangleShape shape1, sf::RectangleShape shape2, char dir, int dist);

bool customCollision(sf::RectangleShape leftRect, sf::RectangleShape rightRect, float deltX);

bool leftPunch(sf::RectangleShape leftPunch, sf::RectangleShape rightBox);

bool rightPunch(sf::RectangleShape rightPunch, sf::RectangleShape leftRect);