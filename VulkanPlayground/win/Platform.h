#pragma once
#include "../stdafx.h"
#include <string>

//Very thin wrapper around win32 functions

//Informations about the current platform window

struct WindowInfo
{
	float width;
	float height;
};

struct Win32WindowData
{
	HWND window;
	HDC dc;
	HINSTANCE instance;
	WindowInfo windowInfo;
};

class Platform
{
public:
	Platform();
	//Show a message box on screen
	//@fatal if true and the debugger is present it breaks the app, just aborts otherwise 
	void ReportError(LPCWSTR errorString, bool fatal = false) const;
	//Log a string on the console window and on the debugger output if present
	void LogString(const std::string & string) const;
	//Creates a win32 window
	HWND MakeWindow(HINSTANCE hInstance, LPCWSTR winClassName, LPCWSTR winTitleName, WNDPROC WindowProc, const WindowInfo & windowCreationInfo);
	Win32WindowData GetWindowData();
	void DeInit(const TCHAR * winClassName, HINSTANCE hInstance, HWND window);

private :
	HWND window;
	HDC dc;
	WindowInfo currentWindowInfo;
};

extern Platform * platform;