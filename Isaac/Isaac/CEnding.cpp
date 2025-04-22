#include "pch.h"
#include "CEnding.h"
#include "CBmpMgr.h"
#include "CSoundMgr.h"

CEnding::CEnding() : m_dwTime(GetTickCount64())
{
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}

CEnding::~CEnding()
{
	Release();
}

void CEnding::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/UI/Ending.bmp", L"Ending");
	CSoundMgr::Get_Instance()->PlayBGM(L"EndingBGM.mp3", 0.3f);

	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 5;

	m_tFrame.dwFrameSpeed = 1000;
	m_tFrame.dwTime = GetTickCount64();

}

void CEnding::Update()
{
	if (m_tFrame.iStart != m_tFrame.iEnd)
	{
		if (m_tFrame.dwTime + m_tFrame.dwFrameSpeed < GetTickCount64())
		{
			++m_tFrame.iStart;
			m_tFrame.dwTime = GetTickCount64();
		}
	}
}

void CEnding::Late_Update()
{
	
}

void CEnding::Render(HDC hDC)
{

	RECT rc = { 0, 0, 800, 600 };
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
	FillRect(hDC, &rc, hBrush);
	DeleteObject(hBrush);

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Ending");

	BitBlt(hDC,
		150,
		200,
		500, 250,
		hMemDC,
		500 * m_tFrame.iStart, 0,
		SRCCOPY);
}

void CEnding::Release()
{
	for (int i = 0; i < size(m_ObjList); ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}

	for_each(m_vecTile.begin(), m_vecTile.end(), Safe_Delete<CObj*>);
	m_vecTile.clear();
}
