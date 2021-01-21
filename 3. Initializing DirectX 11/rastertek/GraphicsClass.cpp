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

	// Direct3D ��ü ����.
	mDirect3D = new D3DClass;
	if (!mDirect3D) return false;

	// Direct3D ��ü �ʱ�ȭ.
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
	// Direct3D ��ü ����.
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

	// �׷��� ���� �������Ѵ�.
	result = Render();
	if (!result) return false;

	return true;
}

bool GraphicsClass::Render()
{
	// ó�� ���� ������ �� ���۸� Ŭ�����Ѵ�.
	mDirect3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// ȭ�鿡 ���� ǥ���Ѵ�.
	mDirect3D->EndScene();

	return true;
}
