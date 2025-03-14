#pragma once

#define WINCX	800
#define WINCY	600

#define PI		3.141592f

extern HWND	g_hWnd;

template<typename T>
void Safe_Delete(T& p)
{
	if (p)
	{
		delete p;
		p = nullptr;
	}
};