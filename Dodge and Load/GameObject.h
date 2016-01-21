#pragma once

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void load(std::string filename);
	virtual void draw(sf::RenderWindow & window);

	virtual void update(float elapsedTime);

	virtual void setPosition(float x, float y);

	virtual sf::Vector2f getPosition() const;
	virtual float getWidth() const;
	virtual float getHeight() const;
	virtual sf::Rect<float> getBoundingRect() const;

	sf::Sprite& getSprite();
	sf::Texture& getTexture();
private:
	float x_;
	float y_;
	sf::Sprite sprite_;
	sf::Texture texture_;
	bool isLoaded_;
};