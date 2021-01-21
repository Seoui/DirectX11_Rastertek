#include "GraphicsClass.h"

GraphicsClass::GraphicsClass()
{
	mDirect3D = nullptr;
}

GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}

GraphicsClass::~GraphicsClass()
{
}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;

	// Direct3D 객체 생성.
	mDirect3D = new D3DClass;
	if (!mDirect3D) return false;

	// Direct3D 객체 초기화.
	result = mDirect3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could nor initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	return true;
}

void GraphicsClass::ShutDown()
{
	// Direct3D 객체 해제.
	if (mDirect3D)
	{
		mDirect3D->Shutdown();
		delete mDirect3D;
		mDirect3D = 0;
	}

	return;
}

bool GraphicsClass::Frame()
{
	bool result;

	// 그래픽 씬을 렌더링한다.
	result = Render();
	if (!result) return false;

	return true;
}

bool GraphicsClass::Render()
{
	// 처음 씬이 시작할 때 버퍼를 클리어한다.
	mDirect3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// 화면에 씬을 표시한다.
	mDirect3D->EndScene();

	return true;
}
