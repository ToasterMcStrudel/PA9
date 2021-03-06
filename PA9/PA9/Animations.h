#pragma once
/*******************************************************************
Everything in the Animations.cpp, Animations.h, and Sprite sheets  *
was coded and created by Ryan Ortuno                               *
********************************************************************/
#include "Character.h"
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <ctime>
#include <string>
#include <sstream>

#define AIDLE 0
#define ABACK 1
#define ADEATH 2
#define AFORWARD 3
#define AHIT 4
#define APUNCH 5
#define AJUMP 6
#define ABLOCK 7
#define ABACKGROUND 0
#define BLOCKYWIN 0
#define CYBORGWIN 1

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

void testFunctions();