#include "pch.h"
#include "CSoulHeart.h"
#include "CBmpMgr.h"

CSoulHeart::CSoulHeart()
{
}

CSoulHeart::~CSoulHeart()
{
	Release();
}

void CSoulHeart::Initialize()
{
	m_eItemID = CItem::ITEM_SOULHEART;

	__super::Set_Frame(0, 0, 0);
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwTime = GetTickCount64();

	Set_CollisionBoxPos(m_tInfo.fX, m_tInfo.fY);
	Set_CollisionBoxSize(32.f, 32.f);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Item/SoulHeart.bmp", L"SoulHeart");
}

void CSoulHeart::Late_Initialize()
{
}

int CSoulHeart::Update()
{
	if (m_bDead)
		return DEAD;

	__super::Update_Rect();;

	return NOEVENT;
}

int CSoulHeart::Late_Update()
{
	Set_CollisionBoxPos(m_tInfo.fX, m_tInfo.fY);

	return NOEVENT;
}

void CSoulHeart::Render(HDC hDC)
{
	//__super::Collision_Render(hDC);

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"SoulHeart");

	GdiTransparentBlt(hDC,/// 복사 받을 dc
		m_tRect.left,		// 복사 받을 위치 좌표 left
		m_tRect.top,					// 복사 받을 위치 좌표 top
		(int)m_tInfo.fCX - 10,				// 복사 받을 가로 사이즈
		(int)m_tInfo.fCY - 10,				// 복사 받을 세로 사이즈
		hMemDC,							// 복사할 이미지 dc
		//m_tFrame.iStart * (int)m_tInfo.fCX + m_tFrame.iStart * 10.f,
		(int)m_tInfo.fCX * m_tFrame.iStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,// * m_tFrame.iMotion,								// 복사할 이미지의 left, top
		(int)m_tInfo.fCX,//(int)m_tInfo.fCX,				// 복사할 이미지의 가로
		(int)m_tInfo.fCY,//(int)m_tInfo.fCY,				// 복사할 이미지의 세로
		RGB(255, 0, 255));
}

void CSoulHeart::Release()
{
}

void CSoulHeart::Collision(CObj* _pObj, HITPOINT _tHitPoint)
{
}
