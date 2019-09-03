#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	//create video mode object
	VideoMode vm(1920, 1080);
	//create and open a window for the game
	RenderWindow window(vm, "Timber!!!", Style::Fullscreen);

	//create a texture to hold a graphic on the GPU
	Texture textureBackground;

	//load a graphic into the texture
	textureBackground.loadFromFile("graphics/background.png");

	//create a sprite
	Sprite spriteBackground;

	//attach the texture to the sprite
	spriteBackground.setTexture(textureBackground);

	//set the spriteBackground to cover the screen
	spriteBackground.setPosition(0,0);

	//creating tree sprite
	Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");
	Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(810, 0);

	//preparing bee
	Texture textureBee;
	textureBee.loadFromFile("graphics/insect.png");
	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(0, 800);
	bool beeActive = false;
	float beeSpeed = 0.0f;

	//creating clouds
	Texture textureCloud;
	textureCloud.loadFromFile("graphics/cloud.png");
	Sprite spriteCloud1;
	Sprite spriteCloud2;
	Sprite spriteCloud3;
	spriteCloud1.setTexture(textureCloud);
	spriteCloud2.setTexture(textureCloud);
	spriteCloud3.setTexture(textureCloud);
	spriteCloud1.setPosition(0, 0);
	spriteCloud2.setPosition(0, 150);
	spriteCloud3.setPosition(0, 300);
	//clouds currently not on screen
	bool cloud1Active = false;
	bool cloud2Active = false;
	bool cloud3Active = false;

	float cloud1Speed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;

	//Variables to control time
	Clock clock;
	
	while (window.isOpen())
	{
		/*
		Handle the players input
		*/
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		/*
		update the scene
		*/
		//measure time
		Time dt = clock.restart();

		//setup the bee
		if (!beeActive)
		{
			//speed
			srand((int)time(0));
			beeSpeed = (rand() % 200) + 200;
			//height
			srand((int)time(0) * 10);
			float height = (rand() % 500) + 500;
			spriteBee.setPosition(2000, height);
			beeActive = true;
		}
		else
		{
			//Move the bee
			spriteBee.setPosition(spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()), spriteBee.getPosition().y);
			if (spriteBee.getPosition().x < -100)	//when the bee reaches the edge of the screen
			{
				beeActive = false;
			}
		}

		//cloud management
		//cloud 1
		if (!cloud1Active)
		{
			//cloud speed
			srand((int)time(0) * 10);
			cloud1Speed = (rand() % 200);
			//cloud height
			srand((int)time(0) * 10);
			float height = (rand() % 150);
			spriteCloud1.setPosition(-200, height);
			cloud1Active = true;
		}
		else
		{
			spriteCloud1.setPosition(spriteCloud1.getPosition().x + (cloud1Speed * dt.asSeconds()), spriteCloud1.getPosition().y);
			if (spriteCloud1.getPosition().x > 1920)
			{
				cloud1Active = false;
			}
		}
		//cloud 2
		if (!cloud2Active)
		{
			//cloud speed
			srand((int)time(0) * 20);
			cloud2Speed = (rand() % 200);
			//cloud height
			srand((int)time(0) * 20);
			float height = (rand() % 300) - 150;
			spriteCloud2.setPosition(-200, height);
			cloud2Active = true;
		}
		else
		{
			spriteCloud2.setPosition(spriteCloud2.getPosition().x + (cloud2Speed * dt.asSeconds()), spriteCloud2.getPosition().y);
			if (spriteCloud2.getPosition().x > 1920)
			{
				cloud2Active = false;
			}
		}
		//cloud 3
		if (!cloud3Active)
		{
			//cloud speed
			srand((int)time(0) * 30);
			cloud3Speed = (rand() % 200);
			//cloud height
			srand((int)time(0) * 30);
			float height = (rand() % 450) - 150;
			spriteCloud3.setPosition(-200, height);
			cloud3Active = true;
		}
		else
		{
			spriteCloud3.setPosition(spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()), spriteCloud3.getPosition().y);
			if (spriteCloud3.getPosition().x > 1920)
			{
				cloud3Active = false;
			}
		}
		/*
		draw the scene
		*/
		window.clear();	//clears everything from the last frame

		//draw our game scene here
		window.draw(spriteBackground);

		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);

		window.draw(spriteTree);

		window.draw(spriteBee);
		

		window.display();	//displays everything we drew
	}

	return 0;
}