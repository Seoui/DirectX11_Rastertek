#include "InputClass.h"

InputClass::InputClass()
{
}

InputClass::InputClass(const InputClass &)
{
}

InputClass::~InputClass()
{
}

void InputClass::Initialize()
{
	int i;
	
	// Initialize all the keys to being released and not pressed.
	for (i = 0; i < 256; i++)
	{
		mKeys[i] = false;
	}

	return;
}

void InputClass::KeyDown(unsigned int input)
{
	// If a key is pressed then save that state in the key array.
	mKeys[input] = true;
	return;
}

void InputClass::KeyUp(unsigned int input)
{
	// If a key is released then clear that state in the key array.
	mKeys[input] = false;
	return;
}

bool InputClass::IsKeyDown(unsigned int key)
{
	// Return what state the key is in (pressed/not pressed).
	return mKeys[key];
}
