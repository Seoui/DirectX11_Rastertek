#include "LightClass.h"

LightClass::LightClass()
{
}

LightClass::LightClass(const LightClass &)
{
}

LightClass::~LightClass()
{
}

void LightClass::SetDiffuseColor(float red, float green, float blue, float alpha)
{
	mDiffuseColor = XMFLOAT4(red, green, blue, alpha);
	return;
}

void LightClass::SetDirection(float x, float y, float z)
{
	mDirection = XMFLOAT3(x, y, z);
	return;
}

XMFLOAT4 LightClass::GetDiffuseColor()
{
	return mDiffuseColor;
}

XMFLOAT3 LightClass::GetDirection()
{
	return mDirection;
}
