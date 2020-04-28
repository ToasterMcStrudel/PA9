/**********************************************************************
Programmer: Ryan Ortuno                                               *
Class: CptS 122, Spring, 2020;                                        *
Programming Assignment: PA 9                                          *
Date: April 24th, 2020                                                *
Description: This program lets players play a Mortal Kombat type      *
game. This goal is to punch the other player's charactor in the face  *
enough time to kill them.                                             *
***********************************************************************/
#include "Animations.h"


int main() {

    sf::RenderWindow window(sf::VideoMode(1122, 600), "Cyborg vs BlockyMan!!", sf::Style::Close | sf::Style::Resize);

    /******************************************************************************************************
    This makes the rectangle the Sprite shows up in. The native pixel size for the Sprites is (125,125),  *
    but by changing th e Vector2f() the image will grow to fit propotionally.                             *
    I'm going to guess to make the hit box about (110, 200) pixels with all the animations, but increase  *
    it to (200,200) pixels when punching. This is because all the animations are set farther back to      *
    make room for the length of the punch.                                                                *
    *******************************************************************************************************/
    sf::RectangleShape player1(sf::Vector2f(200.0f, 200.0f));
    sf::RectangleShape player2(sf::Vector2f(200.0f, 200.0f));
    sf::RectangleShape playerBackground(sf::Vector2f(1122, 600.0f));



    //This changes the position of the Sprites
    player1.setPosition(300.0f, 400.0f);
    player2.setPosition(400.0f, 400.0f);
    playerBackground.setPosition(0.0f, 0.0f);

    /**************************************************************************
    This loads the Sprite sheets for the playable charactors, and background  *
    This is heavy on processing and needs to be done before the game starts.  *
    ***************************************************************************/
    sf::Texture player1Texture, player2Texture, background;
    player1Texture.loadFromFile("textures/Cyborg.png");
    player2Texture.loadFromFile("textures/BlockMan.png");
    background.loadFromFile("textures/FightingStage.png");

    //Assigns the textures to the player and background
    player1.setTexture(&player1Texture);
    player2.setTexture(&player2Texture);
    playerBackground.setTexture(&background);


    //Instantiates the Animation class, DO NOT CHANGE THE VECTOR2U HERE, and controls the animation speed. 
    Animations p1animation(&player1Texture, sf::Vector2u(7, 8), .12f);
    Animations p2animation(&player2Texture, sf::Vector2u(7, 8), .12f);
    Animations backgroundAnimation(&background, sf::Vector2u(13, 1), 0.09f);

    //Sets up for the deltaTime to control smooth and even animations
    sf::Clock clock;
    float deltaTime = 0.0f;

    bool finishPunch1 = false, finishPunch2 = false, finishJump1 = false, finishJump2 = false;
    int p1press = 0, p2press = 0;

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
        We need a position bool check to make sure the players' are on the left or right!  *
        ************************************************************************************/
        if (Keyboard::isKeyPressed(Keyboard::T) || finishPunch1) {
            /*
            When T is pressed finishedPunch1 becomes equal to true until the sprite
            reaches the final frame making finishedPunch1 equal false to stop the animation.
            */
            finishPunch1 = p1animation.update(APUNCH, deltaTime, true);
        }
        else  if (Keyboard::isKeyPressed(Keyboard::Y)) {
            p1animation.update(ABLOCK, deltaTime, true);
        }
        else if (Keyboard::isKeyPressed(Keyboard::W) || finishJump1) {
            /*
            When T is pressed finishJump1 becomes equal to true until the sprite
            reaches the final frame making finishJump1 equal false to stop the animation.
            */
            finishJump1 = p1animation.update(AJUMP, deltaTime, true);
        }
        else if (Keyboard::isKeyPressed(Keyboard::D)) {
            p1animation.update(AFORWARD, deltaTime, true);
        }
        else if (Keyboard::isKeyPressed(Keyboard::A)) {
            p1animation.update(ABACK, deltaTime, true);
        }
        else {
            p1animation.update(AIDLE, deltaTime, true);
        }

        /***********************************************************************************
        This controls BlockyMan! The punch and jump animation still needs work though      *
        We need a position bool check to make sure the players' are on the left or right!  *
        ************************************************************************************/
        if (Keyboard::isKeyPressed(Keyboard::Numpad1) || finishPunch2) {
            /*
            When T is pressed finishPunch2 becomes equal to true until the sprite
            reaches the final frame making finishPunch2 equal false to stop the animation.
            */
            finishPunch2 = p2animation.update(APUNCH, deltaTime, false);
        }
        else  if (Keyboard::isKeyPressed(Keyboard::Numpad2)) {
            p2animation.update(ABLOCK, deltaTime, false);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Up) || finishJump2) {
            /*
            When T is pressed finishJump2 becomes equal to true until the sprite
            reaches the final frame making finishJump2 equal false to stop the animation.
            */
            finishJump2 = p2animation.update(AJUMP, deltaTime, false);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Left)) {
            p2animation.update(AFORWARD, deltaTime, false);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Right)) {
            p2animation.update(ABACK, deltaTime, false);
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
        window.draw(player1);
        window.draw(player2);
        window.display();
    }
}