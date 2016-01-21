#include "stdafx.h"
#include "Game.h"
#include "GameObjectManager.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
	std::for_each(gameObjects_.begin(), gameObjects_.end(), GameObjectDeallocator());
}

void GameObjectManager::add(std::string name, GameObject* gameObject)
{
	gameObjects_.insert(std::pair<std::string, GameObject*>(name, gameObject));
}

void GameObjectManager::remove(std::string name)
{
	std::map<std::string, GameObject*>::iterator results = gameObjects_.find(name);
	if (results != gameObjects_.end())
	{
		delete results->second;
		gameObjects_.erase(results);
	}
}

GameObject* GameObjectManager::get(std::string name) const
{
	std::map<std::string, GameObject*>::const_iterator results = gameObjects_.find(name);
	if (results == gameObjects_.end())
		return NULL;
	return results->second;

}

int GameObjectManager::getObjectCount() const
{
	return gameObjects_.size();
}


void GameObjectManager::drawAll(sf::RenderWindow& renderWindow)
{
	std::map<std::string, GameObject*>::const_iterator itr = gameObjects_.begin();
	while (itr != gameObjects_.end())
	{
		itr->second->draw(renderWindow);
		itr++;
	}
}


void GameObjectManager::updateAll()
{
	std::map<std::string, GameObject*>::const_iterator itr = gameObjects_.begin();

	while (itr != gameObjects_.end())
	{
		itr->second->update(Game::getClock().getElapsedTime().asSeconds());
		itr++;
	}

}