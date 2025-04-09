#pragma once

#include "Define.h"


class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void		Late_Initialize();
	void		Initialize();
	void		Update();
	void		Late_Update();
	void		Render();
	void		Release();

private:
	int			m_iFPS;
	TCHAR		m_szFPS[32];

	HDC		m_hDC;
	HDC		m_hMemoryDC;
	RECT	m_rc;
	HBITMAP hBitmap;
	HBITMAP hOldBitmap;

	POINT m_Cursor;
	ULONGLONG		m_dwTime;

};
