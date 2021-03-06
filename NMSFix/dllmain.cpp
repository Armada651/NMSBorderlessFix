// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "MinHook.h"

LONG(WINAPI* True_SetWindowLongA)(
	HWND     hWnd,
	int      nIndex,
	LONG     dwNewLong
);

BOOL(WINAPI* True_SetWindowPos)(
	HWND hWnd,
	HWND hWndInsertAfter,
	int  X,
	int  Y,
	int  cx,
	int  cy,
	UINT uFlags
);

LONG WINAPI Hook_SetWindowLongA(
	HWND     hWnd,
	int      nIndex,
	LONG     dwNewLong
)
{
	if (nIndex == GWL_STYLE || nIndex == GWL_EXSTYLE)
		hWnd = FindWindowW(L"GLFW30", L"No Man's Sky");
	return True_SetWindowLongA(hWnd, nIndex, dwNewLong);
}

BOOL WINAPI Hook_SetWindowPos(
	HWND hWnd,
	HWND hWndInsertAfter,
	int  X,
	int  Y,
	int  cx,
	int  cy,
	UINT uFlags
)
{
	if (uFlags & SWP_FRAMECHANGED)
		hWnd = FindWindowW(L"GLFW30", L"No Man's Sky");
	return True_SetWindowPos(hWnd, hWndInsertAfter, X, Y, cx, cy, uFlags);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		MH_Initialize();
		MH_CreateHook(SetWindowLongA, Hook_SetWindowLongA, (PVOID*)&True_SetWindowLongA);
		MH_CreateHook(SetWindowPos, Hook_SetWindowPos, (PVOID*)&True_SetWindowPos);
		MH_EnableHook(MH_ALL_HOOKS);
		break;

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

