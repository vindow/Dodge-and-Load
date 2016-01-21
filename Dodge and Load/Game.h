#pragma once
#include "GameObjectManager.h"

class Game
{
public:
	static void start();
	static sf::RenderWindow& getWindow();
	static sf::Clock& getClock();
	static void end();
	
	static GameObjectManager& GetGameObjectManager()
	{
		return gameObjectManager_;
	}
	const static int SCREEN_WIDTH = 1024;
	const static int SCREEN_HEIGHT = 768;

private:
	static bool isExiting();
	static void gameLoop();

	static void displayText();
	static void displayScore();
	static void showMenu();

	static void init();

	enum GameState {
		Uninitialized, ShowingMenu, Playing, Exiting, Finished
	};

	static GameState gameState_;
	static sf::RenderWindow mainWindow_;
	static sf::Clock clock_;

	static sf::Font font_;
	static GameObjectManager gameObjectManager_;
};