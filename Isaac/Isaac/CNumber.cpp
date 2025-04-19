#include "pch.h"
#include "CNumber.h"
#include "CBmpMgr.h"

CNumber::CNumber() 
{
    ZeroMemory(&m_tFrame, sizeof(FRAME));
}

CNumber::~CNumber()
{
    Release();
}

void CNumber::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/UI/NumberUI.bmp", L"NumberUI");
	__super::Update_Rect();
}

void CNumber::Late_Initialize()
{
}

int CNumber::Update()
{
	

    return NOEVENT;
}

int CNumber::Late_Update()
{
    return NOEVENT;
}

void CNumber::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"NumberUI");

	GdiTransparentBlt(hDC,/// 복사 받을 dc
		m_tRect.left,		// 복사 받을 위치 좌표 left
		m_tRect.top,					// 복사 받을 위치 좌표 top
		(int)m_tInfo.fCX,				// 복사 받을 가로 사이즈
		(int)m_tInfo.fCY,				// 복사 받을 세로 사이즈
		hMemDC,							// 복사할 이미지 dc
		(int)m_tInfo.fCX * m_tFrame.iStart,
		(int)m_tInfo.fCY,							// 복사할 이미지의 left, top
		(int)m_tInfo.fCX,//(int)m_tInfo.fCX,				// 복사할 이미지의 가로
		(int)m_tInfo.fCY,//(int)m_tInfo.fCY,				// 복사할 이미지의 세로
		RGB(255, 0, 255));
	if(1 == m_tFrame.iMotion)
	{
		GdiTransparentBlt(hDC,/// 복사 받을 dc
			m_tRect.left - 16,		// 복사 받을 위치 좌표 left
			m_tRect.top,					// 복사 받을 위치 좌표 top
			(int)m_tInfo.fCX,				// 복사 받을 가로 사이즈
			(int)m_tInfo.fCY,				// 복사 받을 세로 사이즈
			hMemDC,							// 복사할 이미지 dc
			(int)m_tInfo.fCX* m_tFrame.iMotion,
			(int)m_tInfo.fCY,							// 복사할 이미지의 left, top
			(int)m_tInfo.fCX,//(int)m_tInfo.fCX,				// 복사할 이미지의 가로
			(int)m_tInfo.fCY,//(int)m_tInfo.fCY,				// 복사할 이미지의 세로
			RGB(255, 0, 255));
	}

}

void CNumber::Release()
{
}
