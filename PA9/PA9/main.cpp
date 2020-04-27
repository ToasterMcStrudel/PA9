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

    sf::RenderWindow window(sf::VideoMode(800, 600), "Cyborg vs BlockyMan!!", sf::Style::Close | sf::Style::Resize );
    
    /*************************************************************************************************
    This makes the rectangle the Sprite shows up in. The native pixel size for the Sprites is (125,125),  *
    but by changing th e Vector2f() the image will grow to fit propotionally.                        *
    **************************************************************************************************/
    sf::RectangleShape player1(sf::Vector2f(125.0f, 125.0f));
    sf::RectangleShape player2(sf::Vector2f(125.0f, 125.0f));


    //This changes the position of the Sprites
    player1.setPosition(300.0f, 200.0f);
    player2.setPosition(400.0f, 200.0f);

    /**************************************************************************
    This loads the Sprite sheets for the playable charactors.                 *
    This is heavy on processing and needs to be done before the game starts.  *
    ***************************************************************************/
    sf::Texture player1Texture, player2Texture;
    player1Texture.loadFromFile("textures/Cyborg.png");
    player2Texture.loadFromFile("textures/BlockMan.png");

    //Assigns the textures to the player.
    player1.setTexture(&player1Texture);
    player2.setTexture(&player2Texture);

    //Instantiates the Animation class, DO NOT CHANGE THE VECTOR2U, and controls the animation speed. 
    Animations p1animation(&player1Texture, sf::Vector2u(7, 8), .12f);
    Animations p2animation(&player2Texture, sf::Vector2u(7, 8), .12f);

    //Sets up for the deltaTime to control smooth and even animations
    sf::Clock clock;
    float deltaTime = 0.0f;
   

    while (window.isOpen()) {

        deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {

            switch (event.type) {

            case sf::Event::Closed:
                window.close();
                break;
            }
        }

        //Change AIDLE to one of the 7 globally defined variables to change the animation.
        p1animation.update(AIDLE, deltaTime, true);
        p2animation.update(AIDLE, deltaTime, false);
        
        //Assigns the correct animation to the player rectanble
        player1.setTextureRect(p1animation.playerRect);
        player2.setTextureRect(p2animation.playerRect);

        window.clear();
        window.draw(player1);
        window.draw(player2);
        window.display();
    }
}