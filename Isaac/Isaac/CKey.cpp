#include "pch.h"
#include "CKey.h"
#include "CBmpMgr.h"
#include "CSoundMgr.h"
#include "CTools.h"

CKey::CKey()
{
}

CKey::~CKey()
{
	Release();
}

void CKey::Initialize()
{
	m_eItemID = CItem::ITEM_KEY;

	__super::Set_Frame(0, 2, 0);
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwTime = GetTickCount64();

	Set_CollisionBoxPos(m_tInfo.fX, m_tInfo.fY);
	Set_CollisionBoxSize(0.f, 0.f);


	__super::Initialize();

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Item/Key.bmp", L"Key");
}

void CKey::Late_Initialize()
{
}

int CKey::Update()
{
	if (m_bDead)
		return DEAD;

	__super::Update_Rect();
	__super::Move_Frame();

	return NOEVENT;
}

int CKey::Late_Update()
{
	Spown_Move();
	Set_CollisionBoxPos(m_tInfo.fX, m_tInfo.fY);

	return NOEVENT;
}

void CKey::Render(HDC hDC)
{

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Key");

	GdiTransparentBlt(hDC,/// 복사 받을 dc
		m_tRect.left,		// 복사 받을 위치 좌표 left
		m_tRect.top,					// 복사 받을 위치 좌표 top
		(int)m_tInfo.fCX,				// 복사 받을 가로 사이즈
		(int)m_tInfo.fCY,				// 복사 받을 세로 사이즈
		hMemDC,							// 복사할 이미지 dc
		//m_tFrame.iStart * (int)m_tInfo.fCX + m_tFrame.iStart * 10.f,
		(int)m_tInfo.fCX * m_tFrame.iStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,// * m_tFrame.iMotion,								// 복사할 이미지의 left, top
		(int)m_tInfo.fCX,//(int)m_tInfo.fCX,				// 복사할 이미지의 가로
		(int)m_tInfo.fCY,//(int)m_tInfo.fCY,				// 복사할 이미지의 세로
		RGB(255, 0, 255));
}

void CKey::Release()
{
}

void CKey::Collision(CObj* _pObj, HITPOINT _tHitPoint)
{
	__super::Collision(_pObj, _tHitPoint);

	switch (_pObj->Get_ObjID())
	{
	case OBJ_PLAYER:
		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"pennypickup.mp3", SOUND_EFFECT, 1.f);
		break;
	case OBJ_ITEM:
		__super::Collision(_pObj, _tHitPoint);
		break;
	default:
		break;
	}
}
