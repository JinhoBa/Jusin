#include "pch.h"
#include "CPassiveItem.h"
#include "CBmpMgr.h"

CPassiveItem::CPassiveItem()
{
}

CPassiveItem::~CPassiveItem()
{
}

void CPassiveItem::Initialize()
{
	__super::Set_Frame(0, 0, 0);
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwTime = GetTickCount64();

	Set_CollisionBoxPos(m_tInfo.fX, m_tInfo.fY);
	Set_CollisionBoxSize(16.f, 16.f);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Item/Item_Cyclops.bmp", L"Item_Cyclops");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Item/Item_Spoon.bmp", L"Item_Spoon");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Item/Item_118.bmp", L"Item_118");
}

void CPassiveItem::Late_Initialize()
{
}

int CPassiveItem::Update()
{
	if (m_bDead)
		return DEAD;

	__super::Update_Rect();

	return NOEVENT;
}

int CPassiveItem::Late_Update()
{
	Set_CollisionBoxPos(m_tInfo.fX, m_tInfo.fY);

	return NOEVENT;
}

void CPassiveItem::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

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

void CPassiveItem::Release()
{
}

void CPassiveItem::Collision(CObj* _pObj, HITPOINT _tHitPoint)
{
}
