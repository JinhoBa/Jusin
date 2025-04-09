#include "pch.h"
#include "CMyBmp.h"
#include "Define.h"

CMyBmp::CMyBmp() : m_MemDC(nullptr), m_curBitMap(nullptr), m_oldBitMap(nullptr)
{
}

CMyBmp::~CMyBmp()
{
	Release();
}

void CMyBmp::Load_Bmp(const TCHAR* pFilePath)
{
	HDC hDC = GetDC(g_hWnd);

	m_MemDC = CreateCompatibleDC(hDC);

	m_curBitMap = (HBITMAP)LoadImage(
		NULL,
		pFilePath,
		IMAGE_BITMAP,
		0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	m_oldBitMap = (HBITMAP)SelectObject(m_MemDC, m_curBitMap);
}

void CMyBmp::Release()
{
	SelectObject(m_MemDC, m_oldBitMap);
	DeleteObject(m_curBitMap);
	DeleteDC(m_MemDC);
}
