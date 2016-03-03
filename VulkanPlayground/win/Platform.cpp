#include "stdafx.h"
#include "Platform.h"
#include <iostream>

Platform p;
Platform * platform = &p;

Platform::Platform()
{

}

void Platform::ReportError(LPCWSTR errorString, bool fatal) const
{
	MessageBox(nullptr, errorString, _T("Error"), 0);

	if (fatal)
	{
		if (IsDebuggerPresent())
		{
			DebugBreak();
		}
		else
		{
			abort();
		}
	}
}

void Platform::LogString(const std::string & string) const
{
	printf("%s", string.c_str());

	if (IsDebuggerPresent())
	{
		OutputDebugStringA(string.c_str());
	}
}

HWND Platform::MakeWindow(HINSTANCE hInstance, LPCWSTR winClassName, LPCWSTR winTitleName, WNDPROC WindowProc, const WindowInfo & windowCreationInfo)
{
	WNDCLASSEX wndClassEx;
	ZeroMemory(&wndClassEx, sizeof(WNDCLASSEX));

	wndClassEx.cbSize = sizeof(WNDCLASSEX);
	wndClassEx.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndClassEx.lpfnWndProc = WindowProc;
	wndClassEx.hInstance = hInstance;
	wndClassEx.lpszClassName = winClassName;
	wndClassEx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClassEx.hbrBackground = NULL;
	wndClassEx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);


	if (!RegisterClassEx(&wndClassEx))
	{
		ReportError(_T("Unable to register window class"));
		return nullptr;
	}

	HWND window = CreateWindowEx(WS_EX_APPWINDOW | WS_EX_WINDOWEDGE, winClassName, winTitleName, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, windowCreationInfo.width, windowCreationInfo.height, nullptr, nullptr, hInstance, nullptr);

	if (!window)
	{
		DWORD errorCode = GetLastError();
		HRESULT winErrorCode = HRESULT_FROM_WIN32(errorCode);

		MessageBox(nullptr, _T("Unable to create window"), _T("Error: Windows Creation"), 0);
		return nullptr;
	}

	currentWindowInfo = windowCreationInfo;
	this->window = window;
	dc = GetDC(window);
	return window;
}

Win32WindowData Platform::GetWindowData()
{
	return{window, dc, GetModuleHandle(NULL) ,currentWindowInfo};
}

void Platform::DeInit(const TCHAR * winClassName, HINSTANCE hInstance, HWND window)
{
	if (window)
	{
		DestroyWindow(window);
	}

	if (winClassName)
	{
		UnregisterClass(winClassName, hInstance);
	}
}