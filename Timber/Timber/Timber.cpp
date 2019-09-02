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

		/*
		draw the scene
		*/
		window.clear();	//clears everything from the last frame

		//draw our game scene here
		window.draw(spriteBackground);

		window.display();	//displays everything we drew
	}

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
