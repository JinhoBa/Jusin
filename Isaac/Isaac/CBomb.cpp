#include "pch.h"
#include "CBomb.h"
#include "CBmpMgr.h"

CBomb::CBomb()
{
}

CBomb::~CBomb()
{
    Release();
}

void CBomb::Initialize()
{
	m_eItemID = CItem::ITEM_BOMB;

	__super::Set_Frame(0, 0, 0);
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwTime = GetTickCount64();

	Set_CollisionBoxPos(m_tInfo.fX, m_tInfo.fY);
	Set_CollisionBoxSize(m_tInfo.fCX , m_tInfo.fCY);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Item/bomb.bmp", L"bomb");
}

void CBomb::Late_Initialize()
{
}

int CBomb::Update()
{
	if (m_bDead)
		return DEAD;

	__super::Update_Rect();

	return NOEVENT;
}

int CBomb::Late_Update()
{
	Set_CollisionBoxPos(m_tInfo.fX, m_tInfo.fY);

	return NOEVENT;
}

void CBomb::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"bomb");

	GdiTransparentBlt(hDC,/// 복사 받을 dc
		m_tRect.left,		// 복사 받을 위치 좌표 left
		m_tRect.top,					// 복사 받을 위치 좌표 top
		32,				// 복사 받을 가로 사이즈
		32,				// 복사 받을 세로 사이즈
		hMemDC,							// 복사할 이미지 dc
		//m_tFrame.iStart * (int)m_tInfo.fCX + m_tFrame.iStart * 10.f,
		(int)m_tInfo.fCX * m_tFrame.iStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,// * m_tFrame.iMotion,								// 복사할 이미지의 left, top
		(int)m_tInfo.fCX,//(int)m_tInfo.fCX,				// 복사할 이미지의 가로
		(int)m_tInfo.fCY,//(int)m_tInfo.fCY,				// 복사할 이미지의 세로
		RGB(255, 0, 255));
}

void CBomb::Release()
{
}

void CBomb::Collision(CObj* _pObj, HITPOINT _tHitPoint)
{
}
