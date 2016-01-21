#pragma once

class Player : public GameObject
{
public:
	Player();
	~Player();

	void setMaxVelocity(const float velocity);
	float getMaxVelocity() const;

	int getNumHits() const;

	void update(float elapsedTime);
private:
	float maxVelocity_;
	int hitsTaken_;
	bool isInvincible_;
	int invincibilityTimer_;
	sf::Texture invincibilityTexture_;
	sf::SoundBuffer buffer_;
	sf::SoundBuffer buffer2_;
	sf::Sound hurt_;
	sf::Sound explode_;
};