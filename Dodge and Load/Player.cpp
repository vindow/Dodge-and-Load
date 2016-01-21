#include "stdafx.h"
#include "GameObject.h"
#include "LoadingBar.h"
#include "Enemy.h"
#include "Game.h"
#include "Player.h"

Player::Player() : hitsTaken_(0), isInvincible_(true), invincibilityTimer_(0)
{
	maxVelocity_ = 10;
	load("images/player.png");
	setPosition(512, 534);
	invincibilityTexture_.loadFromFile("images/iplayer.png");
	buffer_.loadFromFile("audio/Hurt.wav");
	buffer2_.loadFromFile("audio/explosion.wav");
	hurt_.setBuffer(buffer_);
	explode_.setBuffer(buffer2_);
}
Player::~Player()
{
}


void Player::setMaxVelocity(const float velocity)
{
	maxVelocity_ = velocity;
}
float Player::getMaxVelocity() const
{
	return maxVelocity_;
}

int Player::getNumHits() const
{
	return hitsTaken_;
}

void Player::update(float elapsedTime)
{
	
	float xPos = getPosition().x;
	float yPos = getPosition().y;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		xPos -= maxVelocity_;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		xPos += maxVelocity_;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		yPos -= maxVelocity_ ;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		yPos += maxVelocity_;
	}

	if (xPos + getWidth() > 1024) 
	{
		xPos = 1024 - getWidth();
	}
	if (yPos + getHeight() > 768) 
	{
		yPos = 768 - getHeight();
	}
	if (yPos < 300) 
	{
		yPos = 300;
	}
	setPosition(xPos, yPos);

	LoadingBar* loadingBar = dynamic_cast<LoadingBar*>(Game::GetGameObjectManager().get("LoadingBar"));
	if (xPos < loadingBar->getPosition().x + loadingBar->getWidth())
	{
		explode_.play();
		Game::end();
	}

	if (isInvincible_) 
	{
		if (invincibilityTimer_ & 2) {
			getSprite().setTexture(invincibilityTexture_);
		}
		else {
			getSprite().setTexture(getTexture());
		}
		if (invincibilityTimer_ > 30) {
			isInvincible_ = false;
			getSprite().setTexture(getTexture());
		}
		invincibilityTimer_++;
	}
	else {
		std::vector<Enemy*> enemies;
		for (int i = 1; i <= 5; i++)
		{
			Enemy* enemy = dynamic_cast<Enemy*>(Game::GetGameObjectManager().get("Enemy" + std::to_string(i)));
			enemies.push_back(enemy);
		}
		for (int i = 0; i < enemies.size(); i++)
		{
			float enemyRadius = enemies[i]->getWidth() / 2;
			float enemyX = enemies[i]->getPosition().x + enemyRadius;
			float enemyY = enemies[i]->getPosition().y + enemyRadius;
			if (sqrt(pow(xPos + getWidth() / 2 - enemyX, 2) + pow(yPos + getWidth() / 2 - enemyY, 2)) < getWidth())
			{
				hurt_.play();
				hitsTaken_++;
				isInvincible_ = true;
				invincibilityTimer_ = 0;
			}
		}
	}
}