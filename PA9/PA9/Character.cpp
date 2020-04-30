#include "Character.h"

Character::Character()
{
	HP = HPCONST;
	

}

int Character::getHP()
{
	return HP;
}

void Character::setHP(int val)
{
	HP = val;
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