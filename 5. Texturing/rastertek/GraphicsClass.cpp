#include "GraphicsClass.h"

GraphicsClass::GraphicsClass()
{
	mDirect3D = nullptr;
	mCamera = 0;
	mModel = 0;
	mTextureShader = 0;
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

	// Create the Direct3D object.
	mDirect3D = new D3DClass;
	if (!mDirect3D) return false;

	// Initialize the Direct3D object.
	result = mDirect3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could nor initialize Direct3D", L"Error", MB_OK);
		return false;
	}
	
	// Create the camera object.
	mCamera = new CameraClass;
	if (!mCamera) return false;
	// Set the initial position of the camera.
	mCamera->SetPosition(0.0f, 0.0f, -5.0f);

	// Create the model object.
	mModel = new ModelClass;
	if (!mModel) return false;

	// Initialize the model object.
	result = mModel->Initialize(mDirect3D->GetDevice(),
		const_cast<WCHAR*>(L"Images/stone01.tga"));
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the texture shader object.
	mTextureShader = new TextureShaderClass;
	if (!mTextureShader) return false;
	// Initialize the texture shader object.
	result = mTextureShader->Initialize(mDirect3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}

void GraphicsClass::ShutDown()
{
	// Release the texture shader object.
	if (mTextureShader)
	{
		mTextureShader->Shutdown();
		delete mTextureShader;
		mTextureShader = 0;
	}
	// Release the model object.
	if (mModel)
	{
		mModel->Shutdown();
		delete mModel;
		mModel = 0;
	}

	// Release the camera object.
	if (mCamera)
	{
		delete mCamera;
		mCamera = 0;
	}

	// Release the Direct3D object.
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

	// Render the graphics scene.
	result = Render();
	if (!result) return false;

	return true;
}

bool GraphicsClass::Render()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;

	// Clear the buffers to begin the scene.
	mDirect3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);
	// Generate the view matrix based on the camera's position.
	mCamera->Render();
	// Get the world, view, and projection matrices from the camera and d3d objects.
	mDirect3D->GetWorldMatrix(worldMatrix);
	mCamera->GetViewMatrix(viewMatrix);
	mDirect3D->GetProjectionMatrix(projectionMatrix);
	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	mModel->Render(mDirect3D->GetDeviceContext());
	// Render the model using the texture shader.
	result = mTextureShader->Render(mDirect3D->GetDeviceContext(), mModel->GetIndexCount(),
		worldMatrix, viewMatrix, projectionMatrix, mModel->GetTexture());
	if (!result) return false;
	// Present the rendered scene to the screen.
	mDirect3D->EndScene();

	return true;
}
