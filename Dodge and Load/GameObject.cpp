#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject() : x_(0), y_(0), isLoaded_(false)
{
}

GameObject::~GameObject()
{
}

void GameObject::load(std::string filename)
{
	if (texture_.loadFromFile(filename)) 
	{
		sprite_.setTexture(texture_);
		isLoaded_ = true;
	} 
	else 
	{
		std::cout << "Could not load file: " << filename << "\n";
		isLoaded_ = false;
	}
}

void GameObject::draw(sf::RenderWindow & window)
{
	if (isLoaded_)
	{
		window.draw(sprite_);
	}
}

void GameObject::update(float elapsedTime)
{

}

void GameObject::setPosition(float x, float y)
{
	x_ = x;
	y_ = y;
	sprite_.setPosition(x_, y_);
}

sf::Vector2f GameObject::getPosition() const
{
	return sf::Vector2f(x_, y_);
}
float GameObject::getWidth() const
{
	return sprite_.getGlobalBounds().width;
}
float GameObject::getHeight() const
{
	return sprite_.getGlobalBounds().height;
}
sf::Rect<float> GameObject::getBoundingRect() const
{
	return sprite_.getGlobalBounds();
}

sf::Sprite& GameObject::getSprite()
{
	return sprite_;
}

sf::Texture& GameObject::getTexture()
{
	return texture_;
}