#include "stdafx.h"
#include "GameObject.h"
#include "Game.h"
#include "LoadingBar.h"
#include "Enemy.h"

Enemy::Enemy(float  x, float y, float xVel, float yVel)
{
	load("images/enemy.png");
	xVelocity_ = xVel;
	yVelocity_ = yVel;
	setPosition(x, y);
	buffer_.loadFromFile("audio/Bounce.wav");
	bounce_.setBuffer(buffer_);
}
Enemy::~Enemy()
{
}

float Enemy::getXVelocity() const
{
	return xVelocity_;
}
float Enemy::getYVelocity() const
{
	return yVelocity_;
}

void Enemy::setXVelocity(const float velocityX)
{
	xVelocity_ = velocityX;
}
void Enemy::setYVelocity(const float velocityY)
{
	yVelocity_ = velocityY;
}

void Enemy::update(float elapsedTime)
{
	float xPos = getPosition().x;
	float yPos = getPosition().y;

	xPos += xVelocity_;
	yPos += yVelocity_;

	//Get loading bar object
	LoadingBar* loadingBar = dynamic_cast<LoadingBar*>(Game::GetGameObjectManager().get("LoadingBar"));

	//Richochet if colliding with wall or loading bar
	if (yPos + getHeight() > 768)
	{
		bounce_.play();
		yVelocity_ *= -1;
		yPos = 767 - getHeight();
	}
	if (yPos < 300) 
	{
		bounce_.play();
		yVelocity_ *= -1;
		yPos = 300;
	}
	if (xPos + getWidth() > 1024)
	{
		bounce_.play();
		xVelocity_ *= -1;
		xPos = 1023 - getWidth();
	}
	if (xPos < loadingBar->getPosition().x + loadingBar->getWidth())
	{
		bounce_.play();
		xVelocity_ *= -1;
		xPos = loadingBar->getPosition().x + loadingBar->getWidth();
	}

	//Update position
	setPosition(xPos, yPos);
}