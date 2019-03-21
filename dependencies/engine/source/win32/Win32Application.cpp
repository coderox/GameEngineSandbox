// WindowsProject2.cpp : Defines the entry point for the application.
//
#include <Windows.h>
#include "GameLoop.h"
#include <memory>

#include "glwrapper.h"

#define MAX_LOADSTRING				100
#define IDS_APP_TITLE				103
#define IDM_EXIT					105
#define IDI_WINDOWSPROJECT2			107
#define IDI_SMALL					108
#define IDC_WINDOWSPROJECT2			109

namespace
{
	std::unique_ptr<Engine::GameLoop> g_gameLoop;
};

// Global Variables:
HINSTANCE hInst;                                // current instance
HDC hDC;			 // Private GDI Device Context
EGLSurface mEglSurface;
EGLDisplay mEglDisplay;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

void StartWin32Application()
{
	HINSTANCE hInstance = GetModuleHandle(NULL);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance))
	{
		return;
	}
	g_gameLoop = std::make_unique<Engine::GameLoop>();
	int width, height;
	g_gameLoop->GetDefaultSize(width, height);
	g_gameLoop->OnWindowSizeChanged(width, height);

	MSG msg = {};
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			g_gameLoop->Tick();
			eglSwapBuffers(mEglDisplay, mEglSurface);
		}
	}

	g_gameLoop.reset();
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT2));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT2);
	wcex.lpszClassName = L"GAME_ENGINE_SANDBOX";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance)
{
	hInst = hInstance; // Store instance handle in our global variable

	// Create window
	int w, h;
	g_gameLoop->GetDefaultSize(w, h);
	RECT rc = { 0, 0, static_cast<LONG>(w), static_cast<LONG>(h) };

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	HWND hWnd = CreateWindowEx(0, "GAME_ENGINE_SANDBOX", "Game Engine Sandbox", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
		nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(g_gameLoop.get()));

	static PIXELFORMATDESCRIPTOR pfd = // pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR), // Size Of This Pixel Format Descriptor
		1,							   // Version Number
		PFD_DRAW_TO_WINDOW |		   // Format Must Support Window
			PFD_SUPPORT_OPENGL |	   // Format Must Support OpenGL
			PFD_DOUBLEBUFFER,		   // Must Support Double Buffering
		PFD_TYPE_RGBA,				   // Request An RGBA Format
		(BYTE)16,					   // Select Our Color Depth
		0,
		0, 0, 0, 0, 0,  // Color Bits Ignored
		0,				// No Alpha Buffer
		0,				// Shift Bit Ignored
		0,				// No Accumulation Buffer
		0, 0, 0, 0,		// Accumulation Bits Ignored
		16,				// 16Bit Z-Buffer (Depth Buffer)
		8,				// No Stencil Buffer
		0,				// No Auxiliary Buffer
		PFD_MAIN_PLANE, // Main Drawing Layer
		0,				// Reserved
		0, 0, 0			// Layer Masks Ignored
	};

	hDC = GetDC(hWnd);
	if (!hDC) {
		//KillGLWindow(fullscreen);
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	//if (mMSAASupported) {
	//	pixelFormat = mMSAAPixelFormat;
	//}
	//else {
	//	pixelFormat = ChoosePixelFormat(hDC, &pfd);
	//}

	//if (!pixelFormat) {
	//	KillGLWindow(fullscreen);
	//	MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
	//	return false;
	//}
	auto pixelFormat = ChoosePixelFormat(hDC, &pfd);
	if (!SetPixelFormat(hDC, pixelFormat, &pfd)) {
		//KillGLWindow(fullscreen);
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}


	const EGLint configAttributes[] =
	{
		EGL_RED_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_BLUE_SIZE, 8,
		EGL_ALPHA_SIZE, 8,
		EGL_DEPTH_SIZE, 8,
		EGL_STENCIL_SIZE, 8,
		EGL_NONE
	};

	const EGLint surfaceAttributes[] =
	{
		EGL_NONE
	};

	const EGLint contextAttibutes[] =
	{
		EGL_CONTEXT_CLIENT_VERSION, 2,
		EGL_NONE
	};

	const EGLint displayAttributes[] =
	{
		EGL_PLATFORM_ANGLE_TYPE_ANGLE, EGL_PLATFORM_ANGLE_TYPE_D3D11_ANGLE,
		EGL_NONE,
	};

	EGLConfig config = 0;

	// eglGetPlatformDisplayEXT is an alternative to eglGetDisplay. It allows us to specifically request D3D11 instead of D3D9.
	PFNEGLGETPLATFORMDISPLAYEXTPROC eglGetPlatformDisplayEXT = reinterpret_cast<PFNEGLGETPLATFORMDISPLAYEXTPROC>(eglGetProcAddress("eglGetPlatformDisplayEXT"));
	if (!eglGetPlatformDisplayEXT)
	{
		OutputDebugStringW(L"Failed to get function eglGetPlatformDisplayEXT");
	}

	mEglDisplay = eglGetPlatformDisplayEXT(EGL_PLATFORM_ANGLE_ANGLE, hDC, displayAttributes);
	if (mEglDisplay == EGL_NO_DISPLAY)
	{
		OutputDebugStringW(L"Failed to get requested EGL display");
		//CleanupEGL();
		return false;
	}

	if (eglInitialize(mEglDisplay, NULL, NULL) == EGL_FALSE)
	{
		OutputDebugStringW(L"Failed to initialize EGL");
		//CleanupEGL();
		return false;
	}

	EGLint numConfigs;
	if ((eglChooseConfig(mEglDisplay, configAttributes, &config, 1, &numConfigs) == EGL_FALSE) || (numConfigs == 0))
	{
		OutputDebugStringW(L"Failed to choose first EGLConfig");
		//CleanupEGL();
		return false;
	}

	mEglSurface = eglCreateWindowSurface(mEglDisplay, config, hWnd, surfaceAttributes);
	if (mEglSurface == EGL_NO_SURFACE)
	{
		OutputDebugStringW(L"Failed to create EGL fullscreen surface");
		//CleanupEGL();
		return false;
	}

	if (eglGetError() != EGL_SUCCESS)
	{
		OutputDebugStringW(L"eglGetError has reported an error");
		//CleanupEGL();
		return false;
	}

	auto mEglContext = eglCreateContext(mEglDisplay, config, NULL, contextAttibutes);
	if (mEglContext == EGL_NO_CONTEXT)
	{
		OutputDebugStringW(L"Failed to create EGL context");
		//CleanupEGL();
		return false;
	}

	if (eglMakeCurrent(mEglDisplay, mEglSurface, mEglSurface, mEglContext) == EGL_FALSE)
	{
		OutputDebugStringW(L"Failed to make EGLSurface current");
		//CleanupEGL();
		return false;
	}

	ShowWindow(hWnd, 5);
	UpdateWindow(hWnd);

	//if (glewInit() != GLEW_OK) { // Enable GLEW
	//	MessageBox(NULL, "GLEW Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
	//	return false;
	//}

	//GetClientRect(hWnd, &rc);
	//g_gameLoop->OnWindowSizeChanged(rc.right - rc.left, rc.bottom - rc.top);

	//g_gameLoop->Initialize(hWnd, rc.right - rc.left, rc.bottom - rc.top);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	auto game = reinterpret_cast<Engine::GameLoop*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
		if (game)
		{
			game->Tick();
		}
		else
		{
			PAINTSTRUCT ps;
			HDC hdc;
			hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
