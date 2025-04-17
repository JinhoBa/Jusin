#include "pch.h"
#include "CMonsterDeathEffect.h"
#include "CBmpMgr.h"
#include "CTools.h"
#include "CSoundMgr.h"

CMonsterDeathEffect::CMonsterDeathEffect() : m_dwTime(GetTickCount64())
{
}

CMonsterDeathEffect::~CMonsterDeathEffect()
{
	Release();
}

void CMonsterDeathEffect::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Effect/bullet_dead.bmp", L"bullet_death");
	m_tFrame.dwFrameSpeed = 50;

	

	Set_Sound(L"goodeath2.mp3", 0.7f);
}

void CMonsterDeathEffect::Late_Initialize()
{
	m_tFrame.iStart = CTools::Get_RandomNumber(0, 1);
	m_tFrame.iMotion = CTools::Get_RandomNumber(0, 2);
}

int CMonsterDeathEffect::Update()
{
	if (m_bDead)
	{
		CSoundMgr::Get_Instance()->Return_Chennel(m_iSoundChennel);
		return DEAD;
	}

	__super::Update_Rect();

	return NOEVENT;
}

int CMonsterDeathEffect::Late_Update()
{
	//__super::Move_Frame();

	if (m_dwTime + 2000 < GetTickCount64())
		m_bDead = true;

	return NOEVENT;
}

void CMonsterDeathEffect::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,/// 복사 받을 dc
		m_tRect.left-5,		// 복사 받을 위치 좌표 left
		m_tRect.top,					// 복사 받을 위치 좌표 top
		(int)m_tInfo.fCX + 10,				// 복사 받을 가로 사이즈
		(int)m_tInfo.fCY+ 10,				// 복사 받을 세로 사이즈
		hMemDC,							// 복사할 이미지 dc
		(int)m_tInfo.fCX * m_tFrame.iStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,			// 복사할 이미지의 left, top
		(int)m_tInfo.fCX,				// 복사할 이미지의 가로
		(int)m_tInfo.fCY,				// 복사할 이미지의 세로
		RGB(255, 0, 255));
}

void CMonsterDeathEffect::Release()
{
}

void CMonsterDeathEffect::Collision(CObj* _pObj, HITPOINT _tHitPoint)
{
}
