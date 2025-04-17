#include "pch.h"
#include "CEnding.h"
#include "CBmpMgr.h"
#include "CSoundMgr.h"

CEnding::CEnding()
{
}

CEnding::~CEnding()
{
	Release();
}

void CEnding::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/UI/Ending.bmp", L"Ending");
	CSoundMgr::Get_Instance()->PlayBGM(L"EndingBGM.mp3", 05.f);
}

void CEnding::Update()
{
}

void CEnding::Late_Update()
{
	
}

void CEnding::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Ending");

	BitBlt(hDC,
		0,
		0,
		WINCX, WINCY,
		hMemDC,
		0, 0,
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
