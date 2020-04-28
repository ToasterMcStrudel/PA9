/*
Programmed by James Whyatt, last edit 4/27/20
Basic character class, needs fleshing out for hitboxes and animations, along with whatever else is needed.
*/

using namespace std;

#include "SFML/Graphics.hpp"

#define HPCONST 100
//HPCONST used as temp, feel free to change in future versions
#define BLOCKCONST 0.25
//BLOCKCONST not used yet, could be changed later on in development for balance.

//character class is barebones at the moment, needs to be fleshed out.
class character
{
private:
	int HP;
	sf::RectangleShape hitBox; //for being hit, also hitBox.getPosition() is basis for character's position.
	sf::RectangleShape punchBox; //for hitting
	sf::RectangleShape blockBox; //for blocking

public:
	character(sf::Vector2f location, sf::Vector2f size);
	int getHP();
	void setHP(int val);

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

	//functions for actually generating the punch and block boxes would be dependant on the model's rig relative to its hitbox, so they're not being written until animation is implimented.
};

character::character(sf::Vector2f location, sf::Vector2f size)
{
	HP = HPCONST;
	hitBox.setSize(size);
	hitBox.setPosition(location);
}

int character::getHP()
{
	return HP;
}

void character::setHP(int val)
{
	HP = val;
	return;
}


//hitBox Functions

sf::Vector2f character::getPosition()
{
	return hitBox.getPosition();
}

void character::setPosition(sf::Vector2f newPos)
{
	hitBox.setPosition(newPos);
	return;
}

sf::Vector2f character::getDimensions()
{
	return hitBox.getSize();
}

void character::setDimensions(sf::Vector2f newSize)
{
	hitBox.setSize(newSize);
	return;
}

sf::RectangleShape character::getBody()
{
	return hitBox;
}

//punchBox Functions

sf::Vector2f character::getPunchPos()
{
	return punchBox.getPosition();
}

void character::setPunchPos(sf::Vector2f newPos)
{
	punchBox.setPosition(newPos);
	return;
}

sf::Vector2f character::getPunchSize()
{
	return punchBox.getSize();
}

void character::setPunchSize(sf::Vector2f newSize)
{
	punchBox.setSize(newSize);
	return;
}

sf::RectangleShape character::getPunch()
{
	return punchBox;
}

//blockBox Functions

sf::Vector2f character::getBlockPos()
{
	return blockBox.getPosition();
}

void character::setBlockPos(sf::Vector2f newPos)
{
	blockBox.setPosition(newPos);
	return;
}

sf::Vector2f character::getBlockSize()
{
	return blockBox.getSize();
}

void character::setBlockSize(sf::Vector2f newSize)
{
	blockBox.setSize(newSize);
	return;
}

sf::RectangleShape character::getBlock()
{
	return blockBox;
}
