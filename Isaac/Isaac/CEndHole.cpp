#include "pch.h"
#include "CEndHole.h"
#include "CBmpMgr.h"

CEndHole::CEndHole()
{
}

CEndHole::~CEndHole()
{
	Release();
}

void CEndHole::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/MapObj/END_Hole.bmp", L"END_Hole");
}

void CEndHole::Late_Initialize()
{
	Set_CollisionBoxSize(m_tInfo.fCX, m_tInfo.fCY);
}

int CEndHole::Update()
{
	Set_CollisionBoxPos(m_tInfo.fX, m_tInfo.fY);
	__super::Update_Rect();
	return NOEVENT;
}

int CEndHole::Late_Update()
{
	return NOEVENT;
}

void CEndHole::Render(HDC hDC)
{
	//__super::Collision_Render(hDC);
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"END_Hole");

	GdiTransparentBlt(hDC,/// 복사 받을 dc
		m_tRect.left-5,		// 복사 받을 위치 좌표 left
		m_tRect.top-5,					// 복사 받을 위치 좌표 top
		(int)m_tInfo.fCX+10,				// 복사 받을 가로 사이즈
		(int)m_tInfo.fCY+10,				// 복사 받을 세로 사이즈
		hMemDC,							// 복사할 이미지 dc
		0,
		(int)m_tInfo.fCY * m_tFrame.iMotion,								// 복사할 이미지의 left, top
		(int)m_tInfo.fCX,			// 복사할 이미지의 가로
		(int)m_tInfo.fCY,				// 복사할 이미지의 세로
		RGB(255, 0, 255));
}

void CEndHole::Release()
{
}

void CEndHole::Collision(CObj* _pObj, HITPOINT _tHitPoint)
{
	if (OBJ_PLAYER == _pObj->Get_ObjID())
	{
		CSceneMgr::Get_Instance()->Scene_Change(CSceneMgr::SC_ENDING);
	}
}
