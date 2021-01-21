#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_

// INCLUDES
#include <Windows.h>

// MY CLASS INCLUDES
#include "D3DClass.h"
#include "CameraClass.h"
#include "ModelClass.h"
#include "LightShaderClass.h"
#include "LightClass.h"


// GLOBALS
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void ShutDown();
	bool Frame();

private:
	bool Render(float);

private:
	D3DClass* mDirect3D;
	CameraClass* mCamera;
	ModelClass* mModel;
	LightShaderClass* mLightShader;
	LightClass* mLight;
};
#endif