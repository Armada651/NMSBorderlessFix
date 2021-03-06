#include "stdafx.h"
#include <Xinput.h>

HMODULE GetXInputModule()
{
	static HMODULE library = NULL;
	if (library)
		return library;

	library = LoadLibraryW(L"xinput1_3.dll");
	return library;
}

typedef DWORD(__stdcall* _XInputGetState)(DWORD dwUserIndex, XINPUT_STATE* pState);
DWORD WINAPI XInputGetState(DWORD dwUserIndex, XINPUT_STATE* pState)
{
	static _XInputGetState func = NULL;
	if (!func)
		func = (_XInputGetState)GetProcAddress(GetXInputModule(), "XInputGetState");
	return func(dwUserIndex, pState);
}

typedef DWORD(__stdcall* _XInputSetState)(DWORD dwUserIndex, XINPUT_VIBRATION* pVibration);
DWORD WINAPI XInputSetState(DWORD dwUserIndex, XINPUT_VIBRATION* pVibration)
{
	static _XInputSetState func = NULL;
	if (!func)
		func = (_XInputSetState)GetProcAddress(GetXInputModule(), "XInputSetState");
	return func(dwUserIndex, pVibration);
}
