#pragma once
class Transformation
{
public:
	Transformation();
	
	void setTranslation(float x, float y, float z);
	void setScale(float scale);
	void setRotation(float rotation);

private:
	float translationX;
	float translationY;
	float translationZ;
	float scale;
	float rotation;
};
