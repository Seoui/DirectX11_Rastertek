#ifndef _SYSTEMCLASS_H_
#define _SYSTEMCLASS_H_

// PRE-PROCESSING DIRECTIVES
// 아래 지시문은 컴파일러에게 외부 MFC 오버헤더를 포함하지 말도록 지시함.
// <Windows.h>를 선언하기 전에 정의해야 함.
#define WIN32_LEAN_AND_MEAN

// INCLUDES
#include <Windows.h>

// MY CLASS INCLUDES
#include "InputClass.h"
#include "GraphicsClass.h"

class SystemClass
{
public:
	SystemClass();
	SystemClass(const SystemClass&);
	~SystemClass();

	bool Initialize();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();

private:
	LPCWSTR mApplicationName;
	HINSTANCE mHinstance;
	HWND mHwnd;

	InputClass* mInput;
	GraphicsClass* mGraphics;
};

// FUNCTION PROTOTYPES
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// GLOBALS
static SystemClass* ApplicationHandle = 0;

#endif