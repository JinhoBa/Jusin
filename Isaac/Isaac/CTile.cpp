#include "pch.h"
#include "CTile.h"
#include "Define.h"
#include "CBmpMgr.h"

CTile::CTile() : m_iDrawID(0), m_iOptionID(0)
{
}

CTile::~CTile()
{
	Release();
}

void CTile::Initialize()
{
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/MapObj/Fire.bmp", L"Fire");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/MapObj/Rock.bmp", L"Rock");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/MapObj/Holl.bmp", L"Holl");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/MapObj/Poo.bmp", L"Poo");

	m_eID = OBJ_TILE;
}

int CTile::Update()
{
	__super::Update_Rect();

	return NOEVENT;
}

int CTile::Late_Update()
{
	switch (m_iDrawID)
	{
	case 1:
		m_pFrameKey = L"Rock";
		break;
	case 3:
		m_pFrameKey = L"Fire";
		break;
	case 4:
		m_pFrameKey = L"Poo";
		break;
	case 5:
		m_pFrameKey = L"Holl";
		break;
	default:
		break;
	}

	return NOEVENT;
}

void CTile::Render(HDC hDC)
{
	/*if (0 == m_iOptionID)
	{
		MoveToEx(hDC, m_tRect.left, m_tRect.top, NULL);
		LineTo(hDC, m_tRect.right, m_tRect.bottom);
	}

	else if (1 == m_iOptionID)
	{
		HPEN Blue_Pen = (HPEN)CreatePen(PS_SOLID, 4, RGB(0, 0, 255));
		HPEN Original_Pen = (HPEN)SelectObject(hDC, Blue_Pen);

		MoveToEx(hDC, m_tRect.left, m_tRect.top, NULL);
		LineTo(hDC, m_tRect.right, m_tRect.bottom);

		MoveToEx(hDC, m_tRect.right, m_tRect.top, NULL);
		LineTo(hDC, m_tRect.left, m_tRect.bottom);

		(HPEN)SelectObject(hDC, Original_Pen);
		DeleteObject(Blue_Pen);
	}
	else if (2 == m_iOptionID)
	{
		HPEN Red_Pen = (HPEN)CreatePen(PS_SOLID, 4, RGB(255, 0, 0));
		HPEN Original_Pen = (HPEN)SelectObject(hDC, Red_Pen);

		MoveToEx(hDC, m_tRect.left, m_tRect.top, NULL);
		LineTo(hDC, m_tRect.right, m_tRect.bottom);

		MoveToEx(hDC, m_tRect.right, m_tRect.top, NULL);
		LineTo(hDC, m_tRect.left, m_tRect.bottom);

		(HPEN)SelectObject(hDC, Original_Pen);
		DeleteObject(Red_Pen);
	}*/

	if (0 == m_iDrawID)
	{
		MoveToEx(hDC, m_tRect.left, m_tRect.top, NULL);
		LineTo(hDC, m_tRect.right, m_tRect.bottom);
		return;
	}
	/*
	else if (1 == m_iOptionID)
	{
		HPEN Blue_Pen = (HPEN)CreatePen(PS_SOLID, 4, RGB(0, 0, 255));
		HPEN Original_Pen = (HPEN)SelectObject(hDC, Blue_Pen);

		MoveToEx(hDC, m_tRect.left, m_tRect.top, NULL);
		LineTo(hDC, m_tRect.right, m_tRect.bottom);

		MoveToEx(hDC, m_tRect.right, m_tRect.top, NULL);
		LineTo(hDC, m_tRect.left, m_tRect.bottom);

		(HPEN)SelectObject(hDC, Original_Pen);
		DeleteObject(Blue_Pen);
	}
	if (2 == m_iOptionID)
	{
		HPEN Red_Pen = (HPEN)CreatePen(PS_SOLID, 4, RGB(255, 0, 0));
		HPEN Original_Pen = (HPEN)SelectObject(hDC, Red_Pen);

		MoveToEx(hDC, m_tRect.left, m_tRect.top, NULL);
		LineTo(hDC, m_tRect.right, m_tRect.bottom);

		MoveToEx(hDC, m_tRect.right, m_tRect.top, NULL);
		LineTo(hDC, m_tRect.left, m_tRect.bottom);

		(HPEN)SelectObject(hDC, Original_Pen);
		DeleteObject(Red_Pen);
	}*/

	if (m_iDrawID == 2)
	{
		HPEN Red_Pen = (HPEN)CreatePen(PS_SOLID, 4, RGB(255, 0, 0));
		HPEN Original_Pen = (HPEN)SelectObject(hDC, Red_Pen);

		MoveToEx(hDC, m_tRect.left, m_tRect.top, NULL);
		LineTo(hDC, m_tRect.right, m_tRect.bottom);

		MoveToEx(hDC, m_tRect.right, m_tRect.top, NULL);
		LineTo(hDC, m_tRect.left, m_tRect.bottom);

		(HPEN)SelectObject(hDC, Original_Pen);
		DeleteObject(Red_Pen);
		return;
	}


	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,/// 복사 받을 dc
		m_tRect.left,		// 복사 받을 위치 좌표 left
		m_tRect.top,					// 복사 받을 위치 좌표 top
		(int)m_tInfo.fCX,				// 복사 받을 가로 사이즈
		(int)m_tInfo.fCY,				// 복사 받을 세로 사이즈
		hMemDC,							// 복사할 이미지 dc
		//m_tFrame.iStart * (int)m_tInfo.fCX + m_tFrame.iStart * 10.f,
		0,
		0,// * m_tFrame.iMotion,								// 복사할 이미지의 left, top
		(int)m_tInfo.fCX,//(int)m_tInfo.fCX,				// 복사할 이미지의 가로
		(int)m_tInfo.fCY,//(int)m_tInfo.fCY,				// 복사할 이미지의 세로
		RGB(255, 0, 255));
}

void CTile::Release()
{
}

void CTile::Collision(CObj* _pObj, HITPOINT _tHitPoint)
{
}

void CTile::Late_Initialize()
{
}

