#include "pch.h"
#include "CTile.h"
#include "Define.h"
#include "CBmpMgr.h"
#include "CBullet.h"
#include "CTools.h"
#include "CCoin.h"
#include "CObjMgr.h"
#include "CSoundMgr.h"

CTile::CTile() : m_iDrawID(0), m_iOption(0), m_iIMGCX(0), m_iIMGCY(0)
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
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/MapObj/Wood.bmp", L"Wood");

	

	m_eID = OBJ_TILE;
	Set_Frame(0, 4, 0);

	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwTime = GetTickCount64();
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
		Set_ImageSize(40, 40);
		break;
	case 3:
		m_pFrameKey = L"Fire";
		Set_ImageSize(50, 50);
		__super::Move_Frame();
		break;
	case 4:
		m_pFrameKey = L"Poo";
		Set_ImageSize(48, 48);
		break;
	case 5:
		m_pFrameKey = L"Holl";
		break;
	case 6:
		m_pFrameKey = L"Wood";
		break;
	default:
		break;
	}
	

	return NOEVENT;
}

void CTile::Render(HDC hDC)
{
	if (0 == m_iOption)
	{
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

	/*if (0 == m_iDrawID)
	{
		MoveToEx(hDC, m_tRect.left, m_tRect.top, NULL);
		LineTo(hDC, m_tRect.right, m_tRect.bottom);
		return;
	}*/
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

	/*if (m_iDrawID == 2)
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
	}*/


	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,/// 복사 받을 dc
		m_tRect.left,		// 복사 받을 위치 좌표 left
		m_tRect.top,					// 복사 받을 위치 좌표 top
		(int)m_tInfo.fCX,				// 복사 받을 가로 사이즈
		(int)m_tInfo.fCY,				// 복사 받을 세로 사이즈
		hMemDC,							// 복사할 이미지 dc
		//m_tFrame.iStart * (int)m_tInfo.fCX + m_tFrame.iStart * 10.f,
		m_iIMGCX * m_tFrame.iStart,
		0,// * m_tFrame.iMotion,								// 복사할 이미지의 left, top
		m_iIMGCX,//(int)m_tInfo.fCX,				// 복사할 이미지의 가로
		m_iIMGCY,//(int)m_tInfo.fCY,				// 복사할 이미지의 세로
		RGB(255, 0, 255));
}

void CTile::Release()
{
}

void CTile::Collision(CObj* _pObj, HITPOINT _tHitPoint)
{
	switch (_pObj->Get_ObjID())
	{
	case OBJ_BULLET:
		if (CBullet::BULLET_PLAYER == dynamic_cast<CBullet*>(_pObj)->Get_BulletID() || 
			CBullet::BULLET_LASER == dynamic_cast<CBullet*>(_pObj)->Get_BulletID())
		{
			switch (m_iDrawID)
			{
			case 3:
				m_iDrawID = 6;
				m_iOption = 1;
				Set_Frame(0, 0, 0);
				CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"Firedeath_hiss.mp3", SOUND_EFFECT, 0.5f);
				break;

			case 4:
				if (m_tFrame.iStart < 4)
					++m_tFrame.iStart;
				else
				{
					if(0 == CTools::Get_RandomNumber(0, 1))
					{
						CObj* pObj = CAbstractFactory<CCoin>::Create_Obj(m_tInfo.fX, m_tInfo.fY, 32.f, 32.f);
						dynamic_cast<CItem*>(pObj)->Set_Stop();
						CObjMgr::Get_Instance()->Add_CObj(OBJ_ITEM, pObj);
					}
					m_iOption = 0;
					m_iDrawID = 0;
				}
				break;

			default:
				break;
			}
		}
		else

		break;
	default:
		break;
	}
}

void CTile::Late_Initialize()
{
}

