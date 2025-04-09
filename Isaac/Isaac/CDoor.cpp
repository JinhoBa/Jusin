#include "pch.h"
#include "CDoor.h"
#include "CBmpMgr.h"
#include "CObjMgr.h"

CDoor::CDoor() : m_bOpen(false), m_eSceneID(CSceneMgr::SC_END)
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
	Set_CollisionBoxSize(m_tInfo.fCX, m_tInfo.fCY);
	__super::Update_Rect();

	return NOEVENT;
}

int CDoor::Late_Update()
{
	if (CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER).empty())
		m_bOpen = true;

	if (m_bOpen)
		m_tFrame.iStart = 0;

	return NOEVENT;
}

void CDoor::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,/// 복사 받을 dc
		m_tRect.left,		// 복사 받을 위치 좌표 left
		m_tRect.top,					// 복사 받을 위치 좌표 top
		(int)m_tInfo.fCX,				// 복사 받을 가로 사이즈
		(int)m_tInfo.fCY,				// 복사 받을 세로 사이즈
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
}
