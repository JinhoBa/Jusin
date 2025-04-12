#include "pch.h"
#include "CItemEffect.h"
#include "CBmpMgr.h"
#include "CObjMgr.h"
#include "CSoundMgr.h"

CItemEffect::CItemEffect(): m_dwTime(GetTickCount64())
{
}

CItemEffect::~CItemEffect()
{
	Release();
}

void CItemEffect::Initialize()
{
	Set_Frame(0, 0, 0);

	m_pTarget = CObjMgr::Get_Instance()->Get_Player();

	Set_Sound(L"Holy.mp3", 1.f);
}

void CItemEffect::Late_Initialize()
{
	
}

int CItemEffect::Update()
{
	if (m_bDead)
	{
		CSoundMgr::Get_Instance()->Return_Chennel(m_iSoundChennel);
		return DEAD;
	}

	m_tInfo.fX = m_pTarget->Get_Info()->fX;
	m_tInfo.fY = m_pTarget->Get_Info()->fY;

	__super::Update_Rect();

	return NOEVENT;
}

int CItemEffect::Late_Update()
{
	__super::Move_Frame();

	if (m_dwTime + 1000 < GetTickCount64())
		m_bDead = true;

	return NOEVENT;
}

void CItemEffect::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,/// 복사 받을 dc
		m_tRect.left,		// 복사 받을 위치 좌표 left
		m_tRect.top,					// 복사 받을 위치 좌표 top
		(int)m_tInfo.fCX,				// 복사 받을 가로 사이즈
		(int)m_tInfo.fCY,				// 복사 받을 세로 사이즈
		hMemDC,							// 복사할 이미지 dc
		(int)m_tInfo.fCX * m_tFrame.iStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,			// 복사할 이미지의 left, top
		(int)m_tInfo.fCX,				// 복사할 이미지의 가로
		(int)m_tInfo.fCY,				// 복사할 이미지의 세로
		RGB(255, 0, 255));
}

void CItemEffect::Release()
{
}

void CItemEffect::Collision(CObj* _pObj, HITPOINT _tHitPoint)
{
}
