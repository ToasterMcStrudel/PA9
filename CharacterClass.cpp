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

	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f newPos);
	sf::Vector2f getDimensions();
	void setDimensions(sf::Vector2f newSize);
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