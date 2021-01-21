#include "GraphicsClass.h"

GraphicsClass::GraphicsClass()
{
	mDirect3D = nullptr;
	mCamera = 0;
	mModel = 0;
	mLightShader = 0;
	mLight = 0;
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
	result = mModel->Initialize(mDirect3D->GetDevice(), "Models/cube.txt", L"Images/seafloor.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the light shader object.
	mLightShader = new LightShaderClass;
	if (!mLightShader) return false;
	// Initialize the texture shader object.
	result = mLightShader->Initialize(mDirect3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}
	
	// Create the light object.
	mLight = new LightClass;
	if (!mLight) return false;

	// Initialize the light object.
	// white
	mLight->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	mLight->SetDirection(0.0f, 0.0f, 1.0f);


	return true;
}

void GraphicsClass::ShutDown()
{
	// Release the light object.
	if (mLight)
	{
		delete mLight;
		mLight = 0;
	}
	// Release the light shader object.
	if (mLightShader)
	{
		mLightShader->Shutdown();
		delete mLightShader;
		mLightShader = 0;
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

	static float rotation = 0.0f;

	// Update the rotation variable each frame.
	rotation += XM_PI * 0.001f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	// Render the graphics scene.
	result = Render(rotation);
	if (!result) return false;

	return true;
}

bool GraphicsClass::Render(float rotation)
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

	// Rotate the world matrix by the rotation value so that the triangle will spin.
	worldMatrix = XMMatrixRotationY(rotation);
	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	mModel->Render(mDirect3D->GetDeviceContext());
	// Render the model using the light shader.
	result = mLightShader->Render(mDirect3D->GetDeviceContext(), mModel->GetIndexCount(),
		worldMatrix, viewMatrix, projectionMatrix, mModel->GetTexture(),
		mLight->GetDirection(), mLight->GetDiffuseColor());
	if (!result) return false;
	// Present the rendered scene to the screen.
	mDirect3D->EndScene();

	return true;
}
