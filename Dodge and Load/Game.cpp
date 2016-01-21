#include "stdafx.h"
#include "GameObject.h"
#include "Player.h"
#include "LoadingBar.h"
#include "Enemy.h"
#include "Game.h"

void Game::start(void)
{
	if (gameState_ != Uninitialized)
		return;

	mainWindow_.create(sf::VideoMode(1024, 768, 32), "Dodge and Load");
	mainWindow_.setFramerateLimit(60);

	init();

	float frameTime = 1.0f / 60.0f;
	float currTime = 0.0f;
	while (!isExiting())
	{
		if (currTime > frameTime)
		{
			gameLoop();
			currTime = 0.0f;
		}
		currTime += clock_.getElapsedTime().asSeconds();
		clock_.restart().asSeconds();
	}

	mainWindow_.close();
}

sf::RenderWindow& Game::getWindow()
{
	return mainWindow_;
}

sf::Clock& Game::getClock()
{
	return clock_;
}

void Game::end()
{
	gameState_ = Game::Finished;
}



bool Game::isExiting()
{
	if (gameState_ == Game::Exiting)
		return true;
	else
		return false;
}

void Game::gameLoop()
{
	sf::Event currentEvent;
	mainWindow_.pollEvent(currentEvent);


	switch (gameState_)
	{
	case Game::ShowingMenu:
	{
		gameObjectManager_.drawAll(mainWindow_);
		showMenu();
		mainWindow_.display();
		break;
	}
	case Game::Playing:
	{
		mainWindow_.clear(sf::Color(100, 100, 100));

		gameObjectManager_.updateAll();
		gameObjectManager_.drawAll(mainWindow_);
		sf::RectangleShape bar(sf::Vector2f(1024, 20));
		bar.setPosition(0, 280);
		bar.setFillColor(sf::Color(0, 0, 0));
		mainWindow_.draw(bar);

		displayScore();
		mainWindow_.display();
		if (currentEvent.type == sf::Event::Closed) gameState_ = Game::Exiting;
		break;
	}
	case Game::Finished:
	{
		displayText();
		mainWindow_.display();
		break;
	}
	}
}

void Game::displayText()
{
	sf::RectangleShape blackScreen(sf::Vector2f(1024, 768));
	blackScreen.setFillColor(sf::Color(0, 0, 0));
	mainWindow_.draw(blackScreen);

	sf::Font font;
	if (!font.loadFromFile("fonts/Square.ttf"))
	{
		std::cout << "Could not load font.\n";
	}
	else
	{
		sf::Text gameOver;
		gameOver.setFont(font);
		gameOver.setString("GAME OVER");
		gameOver.setCharacterSize(100);
		gameOver.setPosition(512 - gameOver.getGlobalBounds().width / 2, 200);

		sf::Text finalScore;
		finalScore.setFont(font);
		int amountLoaded = (int)(dynamic_cast<LoadingBar*>(gameObjectManager_.get("LoadingBar"))->getPosition().x) + 1024;
		int numHits = dynamic_cast<Player*>(gameObjectManager_.get("Player"))->getNumHits();
		finalScore.setString("Final Score: " + std::to_string(amountLoaded - numHits * 150));
		finalScore.setCharacterSize(100);
		finalScore.setPosition(512 - finalScore.getGlobalBounds().width / 2, 300);

		sf::Text tryAgain;
		tryAgain.setFont(font);
		tryAgain.setString("Reload?");
		tryAgain.setCharacterSize(100);
		tryAgain.setPosition(512 - tryAgain.getGlobalBounds().width / 2, 400);

		sf::RectangleShape tryAgainBox(sf::Vector2f(tryAgain.getGlobalBounds().width + 20, tryAgain.getGlobalBounds().height + 30));
		tryAgainBox.setPosition(512 - tryAgain.getGlobalBounds().width / 2, 384 - tryAgain.getGlobalBounds().height + 100);
		tryAgainBox.setFillColor(sf::Color(128, 128, 128));

		mainWindow_.draw(gameOver);
		mainWindow_.draw(finalScore);
		mainWindow_.draw(tryAgainBox);
		mainWindow_.draw(tryAgain);

		sf::Rect<float> bSpriteRect = tryAgainBox.getGlobalBounds();
		sf::Event event;
		while (mainWindow_.pollEvent(event))
		{
			if (event.type == sf::Event::MouseButtonPressed)
			{
				float x = event.mouseButton.x;
				float y = event.mouseButton.y;
				if (bSpriteRect.height + bSpriteRect.top> y
					&& bSpriteRect.top < y
					&& bSpriteRect.left < x
					&& bSpriteRect.width + bSpriteRect.left > x)
				{
					gameObjectManager_.remove("Player");
					gameObjectManager_.remove("LoadingBar");
					gameObjectManager_.remove("Enemy1");
					gameObjectManager_.remove("Enemy2");
					gameObjectManager_.remove("Enemy3");
					gameObjectManager_.remove("Enemy4");
					gameObjectManager_.remove("Enemy5");
					init();
				}
			}
			if (event.type == sf::Event::Closed)
			{
				gameState_ = Game::Exiting;
				break;
			}
		}
	}
}

void Game::displayScore()
{
	sf::Font font;
	if (!font.loadFromFile("fonts/Square.ttf"))
	{
		std::cout << "Could not load font.\n";
	}
	else
	{
		sf::Text score;
		score.setFont(font);
		int amountLoaded = (int)(dynamic_cast<LoadingBar*>(gameObjectManager_.get("LoadingBar"))->getPosition().x) + 1024;
		int numHits = dynamic_cast<Player*>(gameObjectManager_.get("Player"))->getNumHits();
		score.setString("Score: " + std::to_string(amountLoaded - numHits * 150));
		score.setCharacterSize(30);
		score.setPosition(10, 10);
		mainWindow_.draw(score);
	}
}

void Game::showMenu()
{
	sf::Font font;
	if (!font.loadFromFile("fonts/Square.ttf"))
	{
		std::cout << "Could not load font.\n";
	}
	else
	{
		sf::RectangleShape blackScreen(sf::Vector2f(1024, 768));
		blackScreen.setFillColor(sf::Color(0, 0, 0));
	
		sf::Text buttonText;
		buttonText.setFont(font);
		buttonText.setString("Start Loading...");
		buttonText.setCharacterSize(100);
		buttonText.setPosition(512 - buttonText.getGlobalBounds().width / 2, 384 - buttonText.getGlobalBounds().height / 2);

		sf::RectangleShape button(sf::Vector2f(buttonText.getGlobalBounds().width + 20, buttonText.getGlobalBounds().height + 30));
		button.setPosition(512 - buttonText.getGlobalBounds().width / 2, 384 - buttonText.getGlobalBounds().height + 50);
		button.setFillColor(sf::Color(128, 128, 128));
		mainWindow_.draw(blackScreen);
		mainWindow_.draw(button);
		mainWindow_.draw(buttonText);
		sf::Rect<float> bSpriteRect = button.getGlobalBounds();
		sf::Event event;
		while (mainWindow_.pollEvent(event))
		{
			if (event.type == sf::Event::MouseButtonPressed)
			{
				float x = event.mouseButton.x;
				float y = event.mouseButton.y;
				if (bSpriteRect.height + bSpriteRect.top> y
					&& bSpriteRect.top < y
					&& bSpriteRect.left < x
					&& bSpriteRect.width + bSpriteRect.left > x)
				{
					gameState_ = Game::Playing;
				}
			}
			if (event.type == sf::Event::Closed)
			{
				gameState_ = Game::Exiting;
				break;
			}
		}
	}
}



void Game::init()
{
	Player *player = new Player();
	gameObjectManager_.add("Player", player);

	LoadingBar *loadingBar = new LoadingBar();
	gameObjectManager_.add("LoadingBar", loadingBar);

	srand(time(NULL));

	Enemy* enemy1 = new Enemy(400, 350, -(((float)rand() / RAND_MAX) * 2 + 3), ((float)rand() / RAND_MAX) * 2 + 3);
	Enemy* enemy2 = new Enemy(800, 350, ((float)rand() / RAND_MAX) * 2 + 3, ((float)rand() / RAND_MAX) * 2 + 3);
	Enemy* enemy3 = new Enemy(400, 600, ((float)rand() / RAND_MAX) * 2 + 3, -(((float)rand() / RAND_MAX) * 2 + 3));
	Enemy* enemy4 = new Enemy(800, 600, -(((float)rand() / RAND_MAX) * 2 + 3), ((float)rand() / RAND_MAX) * 2 + 3);
	Enemy* enemy5 = new Enemy(200, 425, -(((float)rand() / RAND_MAX) * 2 + 3), ((float)rand() / RAND_MAX) * 2 + 3);
	gameObjectManager_.add("Enemy1", enemy1);
	gameObjectManager_.add("Enemy2", enemy2);
	gameObjectManager_.add("Enemy3", enemy3);
	gameObjectManager_.add("Enemy4", enemy4);
	gameObjectManager_.add("Enemy5", enemy5);

	gameState_ = Game::ShowingMenu;
}

Game::GameState Game::gameState_ = Uninitialized;
sf::RenderWindow Game::mainWindow_;
sf::Clock Game::clock_;
GameObjectManager Game::gameObjectManager_;