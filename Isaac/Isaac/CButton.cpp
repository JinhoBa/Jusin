#include "pch.h"
#include "CButton.h"
#include "CBmpMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"

CButton::CButton()
{
}

CButton::~CButton()
{
	Release();
}

void CButton::Initialize()
{
	m_tInfo.fX = 375.f;
	m_tInfo.fY = 480.f;
	m_tInfo.fCX = 150.f;
	m_tInfo.fCY = 60.f;
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/UI/MainButton.bmp", L"MainButton");
}

void CButton::Late_Initialize()
{
}

int CButton::Update()
{
	__super::Update_Rect();

    return NOEVENT;
}

int CButton::Late_Update()
{
	POINT		ptMouse{};
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	if (PtInRect(&m_tRect, ptMouse))
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			CSceneMgr::Get_Instance()->Scene_Change(CSceneMgr::SC_TUTORIAL);
			return DEAD;
		}
		m_iDrawID = 1;
	}
	else
		m_iDrawID = 0;

    return NOEVENT;
}

void CButton::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"MainButton");

	GdiTransparentBlt(hDC,/// 복사 받을 dc
		m_tRect.left,		// 복사 받을 위치 좌표 left
		m_tRect.top,					// 복사 받을 위치 좌표 top
		(int)m_tInfo.fCX,				// 복사 받을 가로 사이즈
		(int)m_tInfo.fCY,				// 복사 받을 세로 사이즈
		hMemDC,							// 복사할 이미지 dc
		m_iDrawID * (int)m_tInfo.fCX,
		0,								// 복사할 이미지의 left, top
		(int)m_tInfo.fCX,				// 복사할 이미지의 가로
		(int)m_tInfo.fCY,				// 복사할 이미지의 세로
		RGB(255, 255, 255));
}

void CButton::Release()
{
}
