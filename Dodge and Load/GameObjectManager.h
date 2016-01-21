#pragma once
#include "GameObject.h"

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	void add(std::string name, GameObject* gameObject);
	void remove(std::string name);
	int getObjectCount() const;
	GameObject* get(std::string name) const;

	void drawAll(sf::RenderWindow& renderWindow);
	void updateAll();

private:
	std::map<std::string, GameObject*> gameObjects_;

	struct GameObjectDeallocator
	{
		void operator()(const std::pair<std::string, GameObject*> & p) const
		{
			delete p.second;
		}
	};
};