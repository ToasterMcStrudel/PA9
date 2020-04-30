#pragma once
#include "Character.h"
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <ctime>

class Animations : public Character
{
private:

	sf::Vector2u spriteCount;
	sf::Vector2u currentSprite;

	float totalTime;
	float animationSpeed;

public:

	Animations(sf::Texture* texture, sf::Vector2u spriteCount, float animationSpeed);
	~Animations();


	bool update(int row, float deltaTime, bool rightFace);
	void update(int row, float deltaTime);

	//Used to make the player rectangle____update later with player and controler class stuff. 
	sf::IntRect playerRect;
};

//bool testCollision(sf::RectangleShape shape1, sf::RectangleShape shape2, char dir, int dist);
