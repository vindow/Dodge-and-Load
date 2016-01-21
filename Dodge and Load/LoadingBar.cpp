#include "stdafx.h"
#include "GameObject.h"
#include "LoadingBar.h"

LoadingBar::LoadingBar() : loadSpeed_(2)
{
	load("images/loadingbar.png");
	setPosition(-1024, 300);
}
LoadingBar::~LoadingBar()
{
}

float LoadingBar::getLoadSpeed() const
{
	return loadSpeed_;
}

void LoadingBar::setLoadSpeed(const float speed)
{
	loadSpeed_ = speed;
}

void LoadingBar::update(float elapsedTime)
{
	float xPos = getPosition().x;
	float yPos = getPosition().y;
	xPos += loadSpeed_;
	setPosition(xPos, yPos);
}
