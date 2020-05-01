#include "Character.h"

Character::Character()
{
	HP = HPCONST;
	damage = 10;
	block = 3;
}
int Character::getHP()
{
	return HP;
}

void Character::setHP(int val)//-edit Hannah Brickwood
{
	if (val < 0)
	{
		HP = 0;
	}
	else
	{
		HP = val;
	}

	return;
}

//hitBox Functions

sf::Vector2f Character::getPosition()
{
	return hitBox.getPosition();
}

void Character::setPosition(sf::Vector2f newPos)
{
	hitBox.setPosition(newPos);
	return;
}

sf::Vector2f Character::getDimensions()
{
	return hitBox.getSize();
}

void Character::setDimensions(sf::Vector2f newSize)
{
	hitBox.setSize(newSize);
	return;
}

sf::RectangleShape Character::getBody()
{
	return hitBox;
}

//punchBox Functions

sf::Vector2f Character::getPunchPos()
{
	return punchBox.getPosition();
}

void Character::setPunchPos(sf::Vector2f newPos)
{
	punchBox.setPosition(newPos);
	return;
}

sf::Vector2f Character::getPunchSize()
{
	return punchBox.getSize();
}

void Character::setPunchSize(sf::Vector2f newSize)
{
	punchBox.setSize(newSize);
	return;
}

sf::RectangleShape Character::getPunch()
{
	return punchBox;
}

//blockBox Functions

sf::Vector2f Character::getBlockPos()
{
	return blockBox.getPosition();
}

void Character::setBlockPos(sf::Vector2f newPos)
{
	blockBox.setPosition(newPos);
	return;
}

sf::Vector2f Character::getBlockSize()
{
	return blockBox.getSize();
}

void Character::setBlockSize(sf::Vector2f newSize)
{
	blockBox.setSize(newSize);
	return;
}

sf::RectangleShape Character::getBlock()
{
	return blockBox;
}


void Character::debugOn()
{
	punchBox.setOutlineColor(sf::Color::Red);
	punchBox.setOutlineThickness(5);
	punchBox.setFillColor(sf::Color::Transparent);

	blockBox.setOutlineColor(sf::Color::Blue);
	blockBox.setOutlineThickness(5);
	blockBox.setFillColor(sf::Color::Transparent);

	return;
}

//places punch relative to the origin of rectangle hitBox.
void Character::placePunch(bool facing, sf::RectangleShape hitBox)
{
	punchBox.setSize(sf::Vector2f(95, 20));

	//facing is true for left, false for right.
	if (facing) //cyborg
	{
		punchBox.setPosition(sf::Vector2f(hitBox.getPosition().x + 95, hitBox.getPosition().y + 65));
	}
	if (!facing) //blockyman
	{
		punchBox.setPosition(sf::Vector2f(hitBox.getPosition().x + 40, hitBox.getPosition().y + 65));
	}
	return;
}

void Character::removePunch()
{
	punchBox.setPosition(sf::Vector2f(0, 0));
	punchBox.setSize(sf::Vector2f(0, 0));
	return;
}


void Character::placeBlock(bool facing, sf::RectangleShape hitBox)
{
	blockBox.setSize(sf::Vector2f(40, 100));
	//The punchbox is awkwardly offset to account for the proper hitbox of the player, and to make sure it covers the left bound.

	if (facing) //cyborg
	{
		blockBox.setPosition(sf::Vector2f(hitBox.getPosition().x + 60, hitBox.getPosition().y + 20));
	}
	if (!facing) //blockyguy
	{
		blockBox.setPosition(sf::Vector2f(hitBox.getPosition().x + 100, hitBox.getPosition().y + 20));
	}
	return;
}

void Character::removeBlock()
{
	blockBox.setSize(sf::Vector2f(0, 0));
	blockBox.setPosition(sf::Vector2f(2, 0));
	//Blockboxes are placed away from the origin so they don't intersect punchboxes, which are at the origin.

	return;
}



void Character::punchDamage(bool hit)
{
	HP -= damage;
}

void Character::blockDamage(bool hit)
{
	HP += block;

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

//Specialized functions for testing collision between the characters, since the hitboxes are janky.
bool customCollision(sf::RectangleShape leftRect, sf::RectangleShape rightRect, float deltX) //deltX is how far the player is going to be moving in a given movement, and thus what it's testing for.
{
	leftRect.setSize(sf::Vector2f(leftRect.getSize().x / 2, 200));

	rightRect.setSize(sf::Vector2f(leftRect.getSize().x / 2, 200));
	rightRect.setPosition(sf::Vector2f(rightRect.getPosition().x + 100, rightRect.getPosition().y)); //moving the right hitbox over by 100 pixels since it's offset by 100.

	if (deltX > 0)
		return testCollision(leftRect, rightRect, 'd', deltX); //test if moving right.
	if (deltX < 0)
		return testCollision(leftRect, rightRect, 'a', abs(deltX)); //tests if moving left
}

//Function for the left character (cyborg) punching right character (blockyman)
bool leftPunch(sf::RectangleShape leftPunch, sf::RectangleShape rightBox)
{
	rightBox.setSize(sf::Vector2f(100, 200));
	rightBox.setPosition(sf::Vector2f(rightBox.getPosition().x + 100, rightBox.getPosition().y));

	return testCollision(leftPunch, rightBox, '\0', 0);
}

//Function for the right character (blockyman) punching left character (cyborg)
bool rightPunch(sf::RectangleShape rightPunch, sf::RectangleShape leftRect)
{
	leftRect.setSize(sf::Vector2f(100, 200));

	return testCollision(rightPunch, leftRect, '\0', 0);
}

