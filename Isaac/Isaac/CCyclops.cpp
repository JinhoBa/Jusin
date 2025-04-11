#include "pch.h"
#include "CCyclops.h"
#include "CBmpMgr.h"

CCyclops::CCyclops()
{
}

CCyclops::~CCyclops()
{
    Release();
}

void CCyclops::Initialize()
{
	m_eItemID = CItem::ITEM_CYCLOPS;

	__super::Set_Frame(0, 0, 0);
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwTime = GetTickCount64();

	Set_CollisionBoxPos(m_tInfo.fX, m_tInfo.fY);
	Set_CollisionBoxSize(16.f, 16.f);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Item/Item_Cyclops.bmp", L"Item_Cyclops");
}

void CCyclops::Late_Initialize()
{
}

int CCyclops::Update()
{
	if (m_bDead)
		return DEAD;

	__super::Update_Rect();

	return NOEVENT;
}

int CCyclops::Late_Update()
{
	Set_CollisionBoxPos(m_tInfo.fX, m_tInfo.fY);

	return NOEVENT;

}

void CCyclops::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Item_Cyclops");

	GdiTransparentBlt(hDC,/// 복사 받을 dc
		m_tRect.left,		// 복사 받을 위치 좌표 left
		m_tRect.top,					// 복사 받을 위치 좌표 top
		(int)m_tInfo.fCX,				// 복사 받을 가로 사이즈
		(int)m_tInfo.fCY,				// 복사 받을 세로 사이즈
		hMemDC,							// 복사할 이미지 dc
		(int)m_tInfo.fCX * m_tFrame.iStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,// * m_tFrame.iMotion,								// 복사할 이미지의 left, top
		(int)m_tInfo.fCX,//(int)m_tInfo.fCX,				// 복사할 이미지의 가로
		(int)m_tInfo.fCY,//(int)m_tInfo.fCY,				// 복사할 이미지의 세로
		RGB(255, 0, 255));
}

void CCyclops::Release()
{
}

void CCyclops::Collision(CObj* _pObj, HITPOINT _tHitPoint)
{
}
