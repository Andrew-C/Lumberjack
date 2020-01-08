#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <SFML/Audio.hpp>

using namespace sf;

void updateBranches(int seed);
const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];

enum class side { LEFT, RIGHT, NONE };
side branchPositions[NUM_BRANCHES];

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
	spriteBackground.setPosition(0, 0);

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


	Clock clock;

	//time bar
	RectangleShape timeBar;
	float timeBarStartWidth = 400;
	float timeBarHeight = 80;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

	Time gameTimeToal;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

	bool paused = true;
	int score = 0;

	sf::Text messageText;
	sf::Text scoreText;
	Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");

	//setting font to the message
	messageText.setFont(font);
	scoreText.setFont(font);
	//assigning messages
	messageText.setString("Press Enter to Start!");
	scoreText.setString("Score = 0");
	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);
	messageText.setFillColor(Color::White);
	messageText.setFillColor(Color::White);

	//positioning of text
	FloatRect textRect = messageText.getLocalBounds();		//textRect contains coordinates of messageText
	messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);	//sets origin of messageText to the center of itself
	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);			//sets messageText position to center of the screen
	scoreText.setPosition(20, 20);

	//preparing branches
	Texture textureBranch;
	textureBranch.loadFromFile("graphics/branch.png");

	for (int i = 0; i < NUM_BRANCHES; i++)
	{
		branches[i].setTexture(textureBranch);
		branches[i].setPosition(-2000, -2000);
		branches[i].setOrigin(220, 20);	//this is the center of the branch sprite
	}

	//prepare the player
	Texture texturePlayer;
	texturePlayer.loadFromFile("graphics/player.png");
	Sprite spritePlayer;
	spritePlayer.setTexture(texturePlayer);
	spritePlayer.setPosition(580, 720);
	side playerSide = side::LEFT;

	//prepare gravestone
	Texture textureRIP;
	textureRIP.loadFromFile("graphics/rip.png");
	Sprite spriteRIP;
	spriteRIP.setTexture(textureRIP);
	spriteRIP.setPosition(600, 860);

	//prepare the axe
	Texture textureAxe;
	textureAxe.loadFromFile("graphics/axe.png");
	Sprite spriteAxe;
	spriteAxe.setTexture(textureAxe);
	spriteAxe.setPosition(700, 830);

	//axe lines up with the tree
	const float AXE_POSITION_LEFT = 700;
	const float AXE_POSITION_RIGHT = 1075;

	//prepare flying log
	Texture textureLog;
	textureLog.loadFromFile("graphics/log.png");
	Sprite spriteLog;
	spriteLog.setTexture(textureLog);
	spriteLog.setPosition(810, 720);
	bool logActive = false;
	float logSpeedX = 1000;
	float logSpeedY = -1500;

	//controls the player input
	bool acceptInput = false;

	//prepare the sound
	
	SoundBuffer chopBuffer;
	chopBuffer.loadFromFile("sound/chop.wav");
	Sound chop;
	chop.setBuffer(chopBuffer);

	SoundBuffer deathBuffer;
	deathBuffer.loadFromFile("sound/death.wav");
	Sound death;
	death.setBuffer(deathBuffer);

	SoundBuffer ootBuffer;
	ootBuffer.loadFromFile("sound/out_of_time.wav");
	Sound outOfTime;
	outOfTime.setBuffer(ootBuffer);
	
	while (window.isOpen())
	{
		/*
		Handle the players input
		*/

		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyReleased && !paused)
			{
				//listen for key presses again
				acceptInput = true;
				//hide axe
				spriteAxe.setPosition(2000, spriteAxe.getPosition().y);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		//start the game
		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			paused = false;

			//resets the time and socre
			score = 0;
			timeRemaining = 6;

			//remove branches
			for (int i = 1; i < NUM_BRANCHES; i++)
			{
				branchPositions[i] = side::NONE;
			}

			//hide gravestone
			spriteRIP.setPosition(675, 2000);
			//move player into position
			spritePlayer.setPosition(580, 720);
			acceptInput = true;
		}
		
		if (acceptInput)
		{
			//handling right cursor
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				playerSide = side::RIGHT;
				score++;

				timeRemaining += (2 / score) + 0.15;

				spriteAxe.setPosition(AXE_POSITION_RIGHT, spriteAxe.getPosition().y);
				spritePlayer.setPosition(1200, 720);
				updateBranches(score);
				spriteLog.setPosition(810, 720);
				logSpeedX = -5000;
				logActive = true;

				acceptInput = false;
				chop.play();
			}

			//handling left cursor
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				playerSide = side::LEFT;
				score++;

				timeRemaining += (2 / score) + 0.15;

				spriteAxe.setPosition(AXE_POSITION_LEFT, spriteAxe.getPosition().y);
				spritePlayer.setPosition(580, 720);
				updateBranches(score);
				spriteLog.setPosition(810, 720);
				logSpeedX = 5000;
				logActive = true;

				acceptInput = false;
				chop.play();
			}
			
		}
		/*
		update the scene
		*/
		if (!paused)
		{
			//measure time
			Time dt = clock.restart();

			//subtract time remaining by however long the previous frame took to execute this code
			timeRemaining -= dt.asSeconds();
			//resize time bar
			timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

			if (timeRemaining <= 0.0f)
			{
				paused = true;
				messageText.setString("Out of Time!!");
				//reposition messageText based on new size
				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

				outOfTime.play();
			}

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
			//update score text
			std::stringstream ss;
			ss << "Score = " << score;
			scoreText.setString(ss.str());

			//updating branch sprites
			for (int i = 0; i < NUM_BRANCHES; i++)
			{
				float height = i * 150;
				if (branchPositions[i] == side::LEFT)
				{
					//moves branches to left side
					branches[i].setPosition(610, height);
					//flips sprite the other way around
					branches[i].setRotation(180);
				}
				else if (branchPositions[i] == side::RIGHT)
				{
					branches[i].setPosition(1330, height);
					branches[i].setRotation(0);
				}
				else
				{
					//hide branch
					branches[i].setPosition(3000, height);
				}
			}

			//handling flying logs
			if (logActive)
			{
				spriteLog.setPosition(spriteLog.getPosition().x + (logSpeedX * dt.asSeconds()), spriteLog.getPosition().y + (logSpeedY * dt.asSeconds()));

				//when the log reaches the edge
				if (spriteLog.getPosition().x < -100 || spriteLog.getPosition().x > 2000)
				{
					//sets it up rady to be a whole new log next frame
					logActive = false;
					spriteLog.setPosition(810, 720);
				}
			}

			//handling being squashed by branch
			if (branchPositions[5] == playerSide)
			{
				//death
				paused = true;
				acceptInput = false;

				//draw grave
				spriteRIP.setPosition(525, 760);
				//hide player
				spritePlayer.setPosition(2000,660);
				messageText.setString("SQUISHED!!");
				FloatRect textrect = messageText.getLocalBounds();

				messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
				
				death.play();
			}
		}	//end of if(!paused)
		/*
		draw the scene
		*/
		window.clear();	//clears everything from the last frame

		//draw our game scene here
		window.draw(spriteBackground);

		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);
		for(int i = 0; i < NUM_BRANCHES; i++)
		{
			window.draw(branches[i]);
		}
		window.draw(spriteTree);
		window.draw(spriteBee);
		window.draw(scoreText);
		window.draw(timeBar);
		window.draw(spritePlayer);
		window.draw(spriteAxe);
		window.draw(spriteLog);
		window.draw(spriteRIP);
		if (paused)
		{
			window.draw(messageText);
		}

		window.display();	//displays everything we drew
	}

	return 0;
}

void updateBranches(int seed)
{
	//moves branches down
	for (int j = NUM_BRANCHES - 1; j > 0; j--)
	{
		branchPositions[j] = branchPositions[j - 1];
	}

	//spawns new branch at position 0
	srand((int)time(0) + seed);
	int r = (rand() % 5);
	switch (r)
	{
	case 0:
		branchPositions[0] = side::LEFT;
		break;

	case 1:
		branchPositions[0] = side::RIGHT;
		break;

	default:
		branchPositions[0] = side::NONE;
		break;
	}

}