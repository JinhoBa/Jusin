#include "pch.h"
#include "CBossHp.h"
#include "CBmpMgr.h"
#include "CObjMgr.h"

CBossHp::CBossHp() : m_bDead(false), m_pBoss(nullptr), m_fBossHp(0.f), m_fMaxBossHp(0.f)
{
}

CBossHp::~CBossHp()
{
    Release();
}

void CBossHp::Initialize()
{
	m_tInfo.fX = 418.f;
	m_tInfo.fY = 150.f;

	m_tInfo.fCX = 400.f;
	m_tInfo.fCY = 57.f;

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/UI/BossHp.bmp", L"BossHp");

	__super::Update_Rect();

	m_pBoss = CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER).back();
	m_fMaxBossHp = m_fBossHp = m_pBoss->Get_Stat()->fHp;
	
}

void CBossHp::Late_Initialize()
{
}

int CBossHp::Update()
{
	if (m_bDead)
		return DEAD;

    return NOEVENT;
}

int CBossHp::Late_Update()
{
	if (m_pBoss)
		m_fBossHp = m_pBoss->Get_Stat()->fHp;
	else
		m_bDead = true;

	if(0 > m_fBossHp)
		m_bDead = true;

    return NOEVENT;
}

void CBossHp::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BossHp");

	GdiTransparentBlt(hDC,/// 복사 받을 dc
		m_tRect.left,		// 복사 받을 위치 좌표 left
		m_tRect.top+10,					// 복사 받을 위치 좌표 top
		(int)m_tInfo.fCX,				// 복사 받을 가로 사이즈
		(int)m_tInfo.fCY,				// 복사 받을 세로 사이즈
		hMemDC,							// 복사할 이미지 dc
		0,
		(int)m_tInfo.fCY,			// 복사할 이미지의 left, top
		(int)m_tInfo.fCX,				// 복사할 이미지의 가로
		(int)m_tInfo.fCY,				// 복사할 이미지의 세로
		RGB(255, 0, 255));

	GdiTransparentBlt(hDC,/// 복사 받을 dc
		m_tRect.left,		// 복사 받을 위치 좌표 left
		m_tRect.top,					// 복사 받을 위치 좌표 top
		((int)m_tInfo.fCX - 35) * int(m_fBossHp) / (int)m_fMaxBossHp + 35,				// 복사 받을 가로 사이즈
		(int)m_tInfo.fCY,				// 복사 받을 세로 사이즈
		hMemDC,							// 복사할 이미지 dc
		0,
		0,			// 복사할 이미지의 left, top
		((int)m_tInfo.fCX - 35) * int(m_fBossHp) / (int)m_fMaxBossHp + 35, // 복사할 이미지의 가로
		(int)m_tInfo.fCY,				// 복사할 이미지의 세로
		RGB(255, 0, 255));
}

void CBossHp::Release()
{
}
