#include "pch.h"
#include "CAbstractFactory.h"
#include "CPlayer.h"
#include "CBmpMgr.h"
#include "CKeyMgr.h"
#include "CObjMgr.h"
#include "CBullet.h"
#include "CTile.h"
#include "CPlayerBullet.h"
#include "CBombBullet.h"
#include "CItem.h"


CPlayer::CPlayer()
	: m_dwTime(NULL), m_bJump(false), m_fTime(0.f), m_MotionTime(NULL), m_eCurState(IDLE), m_ePreState(MS_END), m_fCoolDown(300.f), m_fAttackPos(0.f)
{
	ZeroMemory(&m_tBodyInfo, sizeof(INFO));
	ZeroMemory(&m_tBodyFrame, sizeof(FRAME));
	ZeroMemory(&m_tItemInfo, sizeof(ITEMINFO)); 
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_fSpeed = 4.f;

	Set_Stat(50.f, 1.f, 300.f);
	Set_ItemInfo(0, 99, 0);

	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 40.f;

	m_tBodyInfo.fCX = 32;
	m_tBodyInfo.fCY = 13;

	m_dwTime = GetTickCount64();
	
	Set_Frame(0, 1, 0);

	m_tFrame.dwFrameSpeed = 300;
	m_tFrame.dwTime = GetTickCount64();

	m_tBodyFrame.dwFrameSpeed = 70;
	m_tBodyFrame.dwTime = GetTickCount64();
	m_eCurState = IDLE;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Player/Player_Head.bmp", L"Player_Head");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Player/Player_Body.bmp", L"Player_Body");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Player/Player_GetItem.bmp", L"Player_GetItem");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Player/Player_Hit.bmp", L"Player_Hit");

	Set_CollisionBoxPos(m_tInfo.fX, m_tInfo.fY + 10.f);
	Set_CollisionBoxSize(40.f, 50.f);

	m_fAttackPos = 5.f;
}

void CPlayer::Late_Initialize()
{

}

int CPlayer::Update()
{
	__super::Update_Rect();

	return NOEVENT;
}

int CPlayer::Late_Update()
{
	
	Key_Input();
	Set_CollisionBoxPos(m_tInfo.fX, m_tInfo.fY + 10.f);

	Change_Motion();

	if(CPlayer::ATTACK == m_eCurState)
	{
		__super::Move_Frame();
		if (m_dwTime + m_fCoolDown < GetTickCount64())
			m_eCurState = IDLE;
	}
	else if (CPlayer::HIT == m_eCurState)
	{
		__super::Move_Frame();
		if (m_MotionTime + 1000 < GetTickCount64())
			m_eCurState = IDLE;
	}
	else if (CPlayer::GETITEM == m_eCurState)
	{
		__super::Move_Frame();
		if (m_MotionTime + 1000 < GetTickCount64())
			m_eCurState = IDLE;
	}

	Move_BodyFrame();

	return NOEVENT;
}


void CPlayer::Render(HDC hDC)
{
	//__super::Collison_Render(hDC);

	HDC hMemDC;

	if (IDLE == m_eCurState || ATTACK == m_eCurState)
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Player_Body");

		GdiTransparentBlt(hDC,/// 복사 받을 dc
			m_tRect.left + 6,		// 복사 받을 위치 좌표 left
			m_tRect.top + 35,					// 복사 받을 위치 좌표 top
			40,//(int)m_tInfo.fCX,				// 복사 받을 가로 사이즈
			25,//(int)m_tInfo.fCY,				// 복사 받을 세로 사이즈
			hMemDC,							// 복사할 이미지 dc
			//m_tFrame.iStart * (int)m_tInfo.fCX + m_tFrame.iStart * 10.f,
			(int)m_tBodyInfo.fCX * m_tBodyFrame.iStart,
			(int)m_tBodyInfo.fCY * m_tBodyFrame.iMotion,								// 복사할 이미지의 left, top
			(int)m_tBodyInfo.fCX,//(int)m_tInfo.fCX,				// 복사할 이미지의 가로
			(int)m_tBodyInfo.fCY,//(int)m_tInfo.fCY,				// 복사할 이미지의 세로
			RGB(255, 0, 255));			// 제거할 이미지 색상 값

		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Player_Head");

		GdiTransparentBlt(hDC,/// 복사 받을 dc
			m_tRect.left,		// 복사 받을 위치 좌표 left
			m_tRect.top,					// 복사 받을 위치 좌표 top
			50,				// 복사 받을 가로 사이즈
			50,				// 복사 받을 세로 사이즈
			hMemDC,							// 복사할 이미지 dc
			(int)m_tInfo.fCX * m_tFrame.iStart,
			(int)m_tInfo.fCY * m_tFrame.iMotion,			// 복사할 이미지의 left, top
			(int)m_tInfo.fCX,				// 복사할 이미지의 가로
			(int)m_tInfo.fCY,				// 복사할 이미지의 세로
			RGB(255, 0, 255));			// 제거할 이미지 색상 값

	}
	else
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

		GdiTransparentBlt(hDC,/// 복사 받을 dc
			m_tRect.left,		// 복사 받을 위치 좌표 left
			m_tRect.top,					// 복사 받을 위치 좌표 top
			50,				// 복사 받을 가로 사이즈
			70,				// 복사 받을 세로 사이즈
			hMemDC,							// 복사할 이미지 dc
			(int)m_tInfo.fCX * m_tFrame.iStart,
			(int)m_tInfo.fCY * m_tFrame.iMotion,			// 복사할 이미지의 left, top
			(int)m_tInfo.fCX,				// 복사할 이미지의 가로
			50,				// 복사할 이미지의 세로
			RGB(255, 0, 255));
	}
}


void CPlayer::Release()
{

}

void CPlayer::Collision(CObj* _pObj, HITPOINT _tHitPoint)
{
	switch (_pObj->Get_ObjID())
	{
	case OBJ_TILE:
		if (0 != dynamic_cast<CTile*>(_pObj)->Get_Option())
		{
			switch (_tHitPoint.eDirection)
			{
			case DIR_DOWN:
				m_tInfo.fY += _tHitPoint.fY;
				break;
			case DIR_UP:
				m_tInfo.fY -= _tHitPoint.fY;
				break;
			case DIR_LEFT:
				m_tInfo.fX -= _tHitPoint.fX;
				break;
			case DIR_RIGHT:
				m_tInfo.fX += _tHitPoint.fX;
				break;
			default:
				break;
			}
		}
		break;

	case OBJ_MONSTER:
		if(HIT != m_ePreState)
			m_tStat.fHp -= _pObj->Get_Damage();
		m_eCurState = HIT;
		switch (_tHitPoint.eDirection)
		{
		case DIR_DOWN:
			m_tInfo.fY += _tHitPoint.fY;
			break;
		case DIR_UP:
			m_tInfo.fY -= _tHitPoint.fY;
			break;
		case DIR_LEFT:
			m_tInfo.fX -= _tHitPoint.fX;
			break;
		case DIR_RIGHT:
			m_tInfo.fX += _tHitPoint.fX;
			break;
		default:
			break;
		}
		break;
	case OBJ_BULLET:
		break;
	case OBJ_ITEM:
		switch (dynamic_cast<CItem*>(_pObj)->Get_ItemID())
		{
		case CItem::ITEM_COIN:
			_pObj->Set_Dead();
			++m_tItemInfo.iCoin;
			break;
		case CItem::ITEM_KEY:
			m_eCurState = GETITEM;
			_pObj->Set_Dead();
			++m_tItemInfo.iKey;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	
	Set_CollisionBoxPos(m_tInfo.fX, m_tInfo.fY + 10.f);
}




void CPlayer::Key_Input()
{
	
	if (CKeyMgr::Get_Instance()->Key_Press('A'))
	{
		if (CKeyMgr::Get_Instance()->Key_Press('W'))
		{
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
		}
		else if (CKeyMgr::Get_Instance()->Key_Press('S'))
		{
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
		}
		else
			m_tInfo.fX -= m_fSpeed;

		if (2 != m_tBodyFrame.iMotion) {
			Set_BodyFrame(0, 9, 2);
		}
		
	}
	else if (CKeyMgr::Get_Instance()->Key_Press('D'))
	{
		if (CKeyMgr::Get_Instance()->Key_Press('W'))
		{
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
		}
		else if (CKeyMgr::Get_Instance()->Key_Press('S'))
		{
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
		}
		else
			m_tInfo.fX += m_fSpeed;

		if (3 != m_tBodyFrame.iMotion) {
			Set_BodyFrame(0, 9, 3);
		}
		
	}
	else if (CKeyMgr::Get_Instance()->Key_Press('W'))
	{
		if (1 != m_tBodyFrame.iMotion) {
			Set_BodyFrame(0, 9, 1);
		}
		m_tInfo.fY -= m_fSpeed;
	}
	else if (CKeyMgr::Get_Instance()->Key_Press('S'))
	{
		if (1 != m_tBodyFrame.iMotion) {
			Set_BodyFrame(0, 9, 1);
		}
		m_tInfo.fY += m_fSpeed;
	}
	else
	{
		Set_BodyFrame(0, 0, 0);
	}

	if(HIT != m_eCurState)
	{
		if (CKeyMgr::Get_Instance()->Key_Press(VK_LEFT))
		{
			if (m_tFrame.iMotion != 3)
			{
				Set_Frame(1, 1, 3);
			}

			Attack(270.f, false);
		}
		else if (CKeyMgr::Get_Instance()->Key_Press(VK_RIGHT))
		{
			if (m_tFrame.iMotion != 1)
			{
				Set_Frame(1, 1, 1);
			}

			Attack(90.f, false);
		}
		else if (CKeyMgr::Get_Instance()->Key_Press(VK_DOWN))
		{
			if (m_tFrame.iMotion != 0)
			{
				Set_Frame(1, 1, 0);
			}

			Attack(180.f, true);
		}
		else if (CKeyMgr::Get_Instance()->Key_Press(VK_UP))
		{
			if (m_tFrame.iMotion != 2)
			{
				Set_Frame(1, 1, 2);
			}
			Attack(0.f, true);

		}
	}
	

	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		++m_tStat.fAttack;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('E') && 0 < m_tItemInfo.iBomb)
	{
		CObjMgr::Get_Instance()->Add_CObj(
			OBJ_BULLET,
			CObj::Create_Bullet<CBombBullet>(m_tInfo.fX, m_tInfo.fY, 50.f, 50.f, m_fAngle, m_tStat.fHp, m_tStat.fAttack, m_tStat.fIntersection)
		);
		--m_tItemInfo.iBomb;
	}

	if (GetAsyncKeyState(VK_RBUTTON))
	{
		//CObjMgr::Get_Instance()->Add_CObj(OBJ_BULLET, Create_Bullet<CMissile>(m_fAngle));
	}

	if (GetAsyncKeyState(VK_LBUTTON) && m_dwTime + 500 < GetTickCount64())
	{
		
		//CObjMgr::Get_Instance()->Add_CObj(OBJ_BULLET, Create_Bullet<CGrenadeBullet>(m_fAngle));
		//m_dwTime = GetTickCount64();
	}

}

void CPlayer::Attack(float _fAngle, bool _bX)
{
	if(m_dwTime + m_fCoolDown < GetTickCount64())
	{
		float fX = m_tInfo.fX;
		float fY = m_tInfo.fY;

		if (_bX)
			fX += m_fAttackPos;
		else
			fY += m_fAttackPos;

		CObjMgr::Get_Instance()->Add_CObj(
			OBJ_BULLET,
			CObj::Create_Bullet<CPlayerBullet>(fX, fY, 50.f, 50.f, _fAngle, m_tStat.fHp, m_tStat.fAttack, m_tStat.fIntersection)
		);
		m_fAttackPos *= -1.f;
		m_dwTime = GetTickCount64();
		m_eCurState = CPlayer::ATTACK;
	}
}

void CPlayer::Move_BodyFrame()
{
	if (0 == m_tBodyFrame.iMotion)
		return;
	if (m_tBodyFrame.dwTime + m_tBodyFrame.dwFrameSpeed < GetTickCount64())
	{
		m_tBodyFrame.iStart++;
		m_tBodyFrame.dwTime = GetTickCount64();

		if (m_tBodyFrame.iStart > m_tBodyFrame.iEnd)
			m_tBodyFrame.iStart = 0;
	}
}


void CPlayer::Change_Motion()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case CPlayer::IDLE:
			m_pFrameKey = L"Player_Head";
			Set_Frame(0, 1, 0);
			m_tFrame.dwFrameSpeed = 300;
			m_tFrame.dwTime = GetTickCount64();
			break;
		case CPlayer::ATTACK:
			m_pFrameKey = L"Player_Head";
			m_tFrame.iStart = 1;
			m_tFrame.dwFrameSpeed = 300;
			m_tFrame.dwTime = GetTickCount64();
			m_MotionTime = GetTickCount64();
			break;
		case CPlayer::HIT:
			m_pFrameKey = L"Player_Hit";
			Set_Frame(0, 1, 0);
			m_tFrame.dwFrameSpeed = 30;
			m_tFrame.dwTime = GetTickCount64();
			m_MotionTime = GetTickCount64();
			break;
		case CPlayer::GETITEM:
			m_pFrameKey = L"Player_GetItem";
			Set_Frame(0, 0, 0);
			m_tFrame.dwFrameSpeed = 300;
			m_tFrame.dwTime = GetTickCount64();
			m_MotionTime = GetTickCount64();
			break;
		case CPlayer::DEATH:
			break;
		case CPlayer::MS_END:
			break;
		default:
			break;
		}

		m_ePreState = m_eCurState;
	}
		
}
