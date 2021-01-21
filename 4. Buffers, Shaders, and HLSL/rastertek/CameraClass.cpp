#include "CameraClass.h"

CameraClass::CameraClass()
{
	mPositionX = 0.0f;
	mPositionY = 0.0f;
	mPositionZ = 0.0f;
	mRotationX = 0.0f;
	mRotationY = 0.0f;
	mRotationZ = 0.0f;
}

CameraClass::CameraClass(const CameraClass &)
{
}

CameraClass::~CameraClass()
{
}

void CameraClass::SetPosition(float x, float y, float z) 
{
	mPositionX = x;
	mPositionY = y;
	mPositionZ = z;
	return;
}

void CameraClass::SetRotation(float x, float y, float z)
{
	mRotationX = x;
	mRotationY = y;
	mRotationZ = z;
	return;
}

XMFLOAT3 CameraClass::GetPosition()
{
	return { mPositionX, mPositionY, mPositionZ };
}

XMFLOAT3 CameraClass::GetRotation()
{
	return { mRotationX, mRotationY, mRotationZ };
}

void CameraClass::Render()
{
	XMFLOAT3 up, position, lookAt;
	XMVECTOR upVector, positionVector, lookAtVector;
	float yaw, pitch, roll;
	XMMATRIX rotationMatrix;

	// Setup the vector that points upward.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;
	// Load it into a XMVECTOR structure.
	upVector = XMLoadFloat3(&up);
	// Setup the position of the camera in the world.
	position.x = mPositionX;
	position.y = mPositionY;
	position.z = mPositionZ;
	// Load it into a XMVECTOR structure.
	positionVector = XMLoadFloat3(&position);
	// Setup where the camera is looking by default.
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;
	// Load it into a XMVECTOR structure.
	lookAtVector = XMLoadFloat3(&lookAt);
	// Set the yaw (Y axis), pitch (X axis), roll (Z axis) rotations in radians.
	pitch = mRotationX * 0.0174532925f;
	yaw = mRotationY * 0.0174532925f;
	roll = mRotationZ * 0.0174532925f;
	// Create the rotation matrix from the yaw, pitch, and roll values.
	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	lookAtVector = XMVector3TransformCoord(lookAtVector, rotationMatrix);
	// Transform the rotated camera position to the location of the viewer.
	/* ���⼭ positionVector�� ���ϴ� ������
	lookAtVector�� �̵���ȯ�� ������ ���̴�. �̵���ȯ�� ���ϱ�. */
	lookAtVector = XMVectorAdd(positionVector, lookAtVector);
	// Finally create the view matrix from the three updated vectors.
	mViewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);

	/*
	XMMatrixLookAtLH()�� ī�޶��� ��ġ, �ٶ󺸴� ���⺤��, �����͸� �Ķ���ͷ� �䱸
	ī�޶��� ��ġ�� ���� ��ġ�̰� SetPosition()���� ������. �⺻�� (0, 0, 0)�� ��ġ
	�ٶ󺸴� ��ġ�� ī�޶� ȸ���� ���� �����ϱ� ȸ���� ���� �������־�� �Ѵ�.
	0.0174532925�� ����/180��, ������ �������� �ٲٱ� ���ؼ���.
	*/
	return;
}

void CameraClass::GetViewMatrix(XMMATRIX & viewMatrix)
{
	viewMatrix = mViewMatrix;
	return;
}
