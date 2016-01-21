#pragma once


class LoadingBar : public GameObject {
public:
	LoadingBar();
	~LoadingBar();

	float getLoadSpeed() const;
	void setLoadSpeed(const float speed);

	void update(float elapsedTime);
private:
	float loadSpeed_;
};