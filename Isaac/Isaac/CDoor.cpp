#include "pch.h"
#include "CDoor.h"
#include "CBmpMgr.h"
#include "CObjMgr.h"
#include "CSoundMgr.h"
#include "CPlayer.h"

CDoor::CDoor() : m_bOpen(false), m_eSceneID(CSceneMgr::SC_END), m_iImgCX(0), m_iImgCY(0)
{
	m_tFrame.iStart = 1;
}

CDoor::~CDoor()
{
	Release();
}

void CDoor::Initialize()
{
	__super::Update_Rect();

	
}

void CDoor::Late_Initialize()
{
}

int CDoor::Update()
{
	Set_CollisionBoxPos(m_tInfo.fX, m_tInfo.fY);
	Set_CollisionBoxSize(m_tInfo.fCX+10, m_tInfo.fCY+10);
	__super::Update_Rect();

	return NOEVENT;
}

int CDoor::Late_Update()
{
	if (CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER).empty() && 0 != lstrcmp(L"Door_Gold", m_pFrameKey))
		m_bOpen = true;

	if (m_bOpen)
	{
		m_tFrame.iStart = 0;
	}

	if (0 == m_tFrame.iMotion || 3 == m_tFrame.iMotion)
	{
		m_iImgCX = 30 + (int)m_tInfo.fCX;
		m_iImgCY = 10 + (int)m_tInfo.fCY;
	}
	else if(1 == m_tFrame.iMotion || 2 == m_tFrame.iMotion)
	{
		m_iImgCX = 10 + (int)m_tInfo.fCX;
		m_iImgCY = 30 + (int)m_tInfo.fCY;
	}

	return NOEVENT;
}

void CDoor::Render(HDC hDC)
{
	//__super::Collision_Render(hDC);
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);


	int left = (m_iImgCX - (int)m_tInfo.fCX) *0.5;
	int top = (m_iImgCY - (int)m_tInfo.fCY) * 0.5;

	GdiTransparentBlt(hDC,/// 복사 받을 dc
		m_tRect.left- left,		// 복사 받을 위치 좌표 left
		m_tRect.top - top,					// 복사 받을 위치 좌표 top
		m_iImgCX,				// 복사 받을 가로 사이즈
		m_iImgCY,				// 복사 받을 세로 사이즈
		hMemDC,							// 복사할 이미지 dc
		(int)m_tInfo.fCX* m_tFrame.iStart,
		(int)m_tInfo.fCY* m_tFrame.iMotion,								// 복사할 이미지의 left, top
		(int)m_tInfo.fCX,			// 복사할 이미지의 가로
		(int)m_tInfo.fCY,				// 복사할 이미지의 세로
		RGB(255, 0, 255));
}

void CDoor::Release()
{
}

void CDoor::Collision(CObj* _pObj, HITPOINT _tHitPoint)
{
	if(m_bOpen)
	{
		switch (_pObj->Get_ObjID())
		{
		case OBJ_PLAYER:
			CSceneMgr::Get_Instance()->Scene_Change(m_eSceneID);
			break;
		default:
			break;
		}
	}
	else
	{
		switch (_pObj->Get_ObjID())
		{
		case OBJ_PLAYER:
			if (CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER).empty() && dynamic_cast<CPlayer*>(_pObj)->Open_Obj())
				m_bOpen = true;
			break;
		default:
			break;
		}
	}

}
