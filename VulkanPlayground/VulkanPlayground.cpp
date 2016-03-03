
#include "stdafx.h"
#include "VulkanPlayground.h"
#include <gl/GL.h>
#include "vk/VulkanAPI.h"
#include "win/Platform.h"

LRESULT CALLBACK WindowProc(_In_ HWND   hwnd, _In_ UINT   uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam);

static  VulkanAPI * vulkan;
int main()
{
	VulkanAPI vkAPI;
	vulkan = &vkAPI;

	HINSTANCE hInstance = GetModuleHandle(NULL);
	STARTUPINFO info;
	GetStartupInfo(&info);

	TCHAR winClassName[] = _T("Vulkan app window");
	TCHAR winTitleName[] = _T("Vulkan Playground");

	HWND window = platform->MakeWindow(hInstance, winClassName, winTitleName, WindowProc, {800, 600});

	vkAPI.Init();
	
	ShowWindow(window, SW_SHOWDEFAULT);
	UpdateWindow(window);

	MSG msg;


	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		RedrawWindow(window, NULL, NULL, RDW_INTERNALPAINT);
	}
	

	platform->DeInit(winClassName, hInstance, window);
	vkAPI.DeInit();
	return 0;

}

LRESULT CALLBACK WindowProc(
	_In_ HWND   hwnd,
	_In_ UINT   msg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
	)
{
	switch (msg)
	{
	case WM_CLOSE:
	{
		DestroyWindow(hwnd);
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}

	case WM_PAINT:
	{
		vulkan->Draw();
		break;
	}
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}
