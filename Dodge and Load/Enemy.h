#pragma once

class Enemy : public GameObject
{
public:
	Enemy(float x, float y, float xVel, float yVel);
	~Enemy();

	float getXVelocity() const;
	float getYVelocity() const;

	void setXVelocity(const float velocityX);
	void setYVelocity(const float velocityY);

	void update(float elapsedTime);
private:
	float xVelocity_;
	float yVelocity_;
	sf::SoundBuffer buffer_;
	sf::Sound bounce_;
};