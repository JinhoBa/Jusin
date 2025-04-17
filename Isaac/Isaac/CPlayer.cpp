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
#include "CSceneMgr.h"
#include "CBox.h"
#include "CDoor.h"
#include "CMonsterBullet.h"
#include "CItemEffect.h"
#include "CSoundMgr.h"
#include "CCoin.h"
#include "CGuidedBullet.h"
#include "CBloodLaser.h"


CPlayer::CPlayer()
	: m_dwTime(NULL), m_bJump(false), m_fTime(0.f), m_MotionTime(NULL), m_eCurState(IDLE), m_ePreState(MS_END), m_fCoolDown(300.f), m_fAttackPos(0.f), m_fSoulHp(0.f),
	m_iHeadSize(50), m_ChargeMoitonTime(NULL), m_ChargeTime(NULL)
{
	ZeroMemory(&m_tBodyInfo, sizeof(INFO));
	ZeroMemory(&m_tBodyFrame, sizeof(FRAME));
	ZeroMemory(&m_tItemInfo, sizeof(ITEMINFO)); 
	m_vecItem.assign(5, false);
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tStat.fMaxHp = 8.f;

	// Test code
	m_fSoulHp = 2.f;

	Set_Stat(6.f, 3.5f, 300.f, 4.f);
	Set_ItemInfo(10, 1, 0);

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
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Player/Player_Head_2.bmp", L"Player_Head_2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Player/Player_Head_2.bmp", L"Player_Head");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Player/Player_Body.bmp", L"Player_Body");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Player/Player_GetItem.bmp", L"Player_GetItem");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Player/Player_Hit.bmp", L"Player_Hit");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Player/Player_Death.bmp", L"Player_Death");

	Set_CollisionBoxPos(m_tInfo.fX, m_tInfo.fY + 10.f);
	Set_CollisionBoxSize(40.f, 45.f);

	m_iSoundChennel = CSoundMgr::Get_Instance()->Get_AvailableChennel();
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
	Set_CollisionBoxPos(m_tInfo.fX, m_tInfo.fY + 5.f);

	if (0 >= m_tStat.fHp)
	{
		Set_CollisionBoxSize(0.f, 0.f);
		m_eCurState = CPlayer::DEATH;
	}
	else
		Key_Input();

	Change_Motion();

	if(CPlayer::ATTACK == m_eCurState)
	{
		if (m_vecItem[2] == true)
		{
			m_tFrame.iStart = 3;
			if (m_dwTime + 800 < GetTickCount64())
				m_eCurState = IDLE;
		}else
		{
			__super::Move_Frame();
			if (m_dwTime + m_fCoolDown < GetTickCount64())
				m_eCurState = IDLE;
		}
	}
	else if (CPlayer::HIT == m_eCurState)
	{
		__super::Move_Frame();
		if (m_MotionTime + 500 < GetTickCount64())
			m_eCurState = IDLE;
	}
	else if (CPlayer::GETITEM == m_eCurState)
	{
		__super::Move_Frame();
		if (m_MotionTime + 1000 < GetTickCount64())
			m_eCurState = IDLE;
	}
	else if (CPlayer::DEATH == m_eCurState)
	{
		__super::Move_Frame();
		if (m_MotionTime + 2000 < GetTickCount64())
			CSceneMgr::Get_Instance()->Scene_Change(CSceneMgr::SC_MENU);
	}
	else if (CPlayer::ATTACK_LASER == m_eCurState)
	{
		
	}

	Move_BodyFrame();

	return NOEVENT;
}


void CPlayer::Render(HDC hDC)
{
	//__super::Collision_Render(hDC);

	HDC hMemDC;

	if (IDLE == m_eCurState || ATTACK == m_eCurState)
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Player_Body");

		GdiTransparentBlt(hDC,/// 복사 받을 dc
			m_tRect.left + 8,		// 복사 받을 위치 좌표 left
			m_tRect.top + 31,					// 복사 받을 위치 좌표 top
			40,//(int)m_tInfo.fCX,				// 복사 받을 가로 사이즈
			20,//(int)m_tInfo.fCY,				// 복사 받을 세로 사이즈
			hMemDC,							// 복사할 이미지 dc
			//m_tFrame.iStart * (int)m_tInfo.fCX + m_tFrame.iStart * 10.f,
			(int)m_tBodyInfo.fCX * m_tBodyFrame.iStart,
			(int)m_tBodyInfo.fCY * m_tBodyFrame.iMotion,								// 복사할 이미지의 left, top
			(int)m_tBodyInfo.fCX,//(int)m_tInfo.fCX,				// 복사할 이미지의 가로
			(int)m_tBodyInfo.fCY,//(int)m_tInfo.fCY,				// 복사할 이미지의 세로
			RGB(255, 0, 255));			// 제거할 이미지 색상 값

		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
		if (m_vecItem[2])
		{
			GdiTransparentBlt(hDC,/// 복사 받을 dc
				m_tRect.left - 19,		// 복사 받을 위치 좌표 left
				m_tRect.top - 45,					// 복사 받을 위치 좌표 top
				m_iHeadSize+10,				// 복사 받을 가로 사이즈
				m_iHeadSize+10,				// 복사 받을 세로 사이즈
				hMemDC,							// 복사할 이미지 dc
				(int)m_tInfo.fCX * m_tFrame.iStart,
				(int)m_tInfo.fCY * m_tFrame.iMotion,			// 복사할 이미지의 left, top
				(int)m_tInfo.fCX,				// 복사할 이미지의 가로
				(int)m_tInfo.fCY,				// 복사할 이미지의 세로
				RGB(255, 0, 255));
		}
		else
		{
			GdiTransparentBlt(hDC,/// 복사 받을 dc
				m_tRect.left-3,		// 복사 받을 위치 좌표 left
				m_tRect.top-10,					// 복사 받을 위치 좌표 top
				60,				// 복사 받을 가로 사이즈
				55,				// 복사 받을 세로 사이즈
				hMemDC,							// 복사할 이미지 dc
				(int)m_tInfo.fCX * m_tFrame.iStart,
				(int)m_tInfo.fCY * m_tFrame.iMotion,			// 복사할 이미지의 left, top
				(int)m_tInfo.fCX,				// 복사할 이미지의 가로
				(int)m_tInfo.fCY,				// 복사할 이미지의 세로
				RGB(255, 0, 255));			// 제거할 이미지 색상 값
		}

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
		switch (dynamic_cast<CTile*>(_pObj)->Get_Option())
		{
		case 0:
			break;
		case 4:
			m_eCurState = HIT;
			break;
		case 1:
		case 2:
		case 3:
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
		default:
			break;
		}

		break;

	case OBJ_MONSTER:
		if(HIT != m_ePreState)
		{
			if (0 >= m_fSoulHp)
				m_tStat.fHp -= _pObj->Get_Damage();
			else
				m_fSoulHp -= 1.f;
		}
		m_eCurState = HIT;
		
		break;
	case OBJ_BULLET:
		if (dynamic_cast<CBullet*>(_pObj)->Get_BulletID() != CBullet::BULLET_MONSTER)
			break;
		if (HIT != m_ePreState)
		{
			if (0 >= m_fSoulHp)
				m_tStat.fHp -= _pObj->Get_Damage();
			else
				m_fSoulHp -= 1.f;
		}
		m_eCurState = HIT;
		break;
	case OBJ_ITEM:
		switch (dynamic_cast<CItem*>(_pObj)->Get_ItemID())
		{
		case CItem::ITEM_SLOTMACHINE:
			CSoundMgr::Get_Instance()->PlaySound(L"Coin_Slot.mp3", m_iSoundChennel, 1.f);
			break;

		case CItem::ITEM_COIN:
			_pObj->Set_Dead();
			++m_tItemInfo.iCoin;
			break;

		case CItem::ITEM_BOMB:
			_pObj->Set_Dead();
			++m_tItemInfo.iBomb;
			break;

		case CItem::ITEM_KEY:
			_pObj->Set_Dead();
			++m_tItemInfo.iKey;
			break;

		case CItem::ITEM_BOX:
			if( !dynamic_cast<CBox*>(_pObj)->Get_bOpen())
			{
				dynamic_cast<CBox*>(_pObj)->Set_Open();
				dynamic_cast<CBox*>(_pObj)->Drop_Item_Boss();
			}
			break;

		case CItem::ITEM_CYCLOPS:
			m_vecItem[0] = true;
			m_fAttackPos *= 3.f;
			m_eCurState = GETITEM;
			CObjMgr::Get_Instance()->Add_CObj(OBJ_EFFECT, Create_Effect<CItemEffect>(L"Item_Cyclops", m_tInfo.fX, m_tInfo.fY, 50.f, 50.f, 0));
			_pObj->Set_Dead();
			break;

		case CItem::ITEM_SPOON:
			m_vecItem[1] = true;
			m_eCurState = GETITEM;
			CObjMgr::Get_Instance()->Add_CObj(OBJ_EFFECT, Create_Effect<CItemEffect>(L"Item_Spoon", m_tInfo.fX, m_tInfo.fY, 50.f, 50.f, 0));
			_pObj->Set_Dead();
			break;

		case CItem::ITEM_118:
			m_vecItem[2] = true;
			m_eCurState = GETITEM;
			m_iHeadSize = 80;
			CObjMgr::Get_Instance()->Add_CObj(OBJ_EFFECT, Create_Effect<CItemEffect>(L"Item_118", m_tInfo.fX, m_tInfo.fY, 50.f, 50.f, 0));
			m_pFrameKey = L"Player_Head_2";
			Set_Frame(0, 0, 0);
			_pObj->Set_Dead();
			break;

		case CItem::ITEM_HEART:
			if(m_tStat.fHp < m_tStat.fMaxHp)
			{
				_pObj->Set_Dead();
				m_tStat.fHp += 2.f;
				if (m_tStat.fHp > m_tStat.fMaxHp)
					m_tStat.fHp = m_tStat.fMaxHp;
			}
			else
			{
				switch (_tHitPoint.eDirection)
				{
				case DIR_DOWN:
					_pObj->Set_posY(-_tHitPoint.fY);
					break;
				case DIR_UP:
					_pObj->Set_posY(_tHitPoint.fY);
					break;
				case DIR_LEFT:
					_pObj->Set_posX(_tHitPoint.fX);
					break;
				case DIR_RIGHT:
					_pObj->Set_posX(-_tHitPoint.fX);
					break;
				default:
					break;
				}
			}

			break;
		case CItem::ITEM_SOULHEART:
			_pObj->Set_Dead();
			m_fSoulHp += 2.f;
			break;
		default:
			break;
		}
		break;
	case OBJ_DOOR:
		if(dynamic_cast<CDoor*>(_pObj)->Get_bOpen())
		{
			if (!lstrcmp(dynamic_cast<CDoor*>(_pObj)->Get_FrameKey(), L"Door_Devil"))
			{
				m_tStat.fHp -= 1.f;
				m_eCurState = HIT;
			}

			switch (_tHitPoint.eDirection)
			{
			case DIR_DOWN:
				if(0 == _pObj->Get_FrameMotion())
					m_tInfo.fY = 490.f;
				break;
			case DIR_UP:
				if (3 == _pObj->Get_FrameMotion())
					m_tInfo.fY = 170.f;
				break;
			case DIR_LEFT:
				if (2 == _pObj->Get_FrameMotion())
					m_tInfo.fX = 90.f;
				break;
			case DIR_RIGHT:
				if (1 == _pObj->Get_FrameMotion())
					m_tInfo.fX = 710.f;;
				break;
			default:
				break;
			}
		}
		break;
	default:
		break;
	}
	
	Set_CollisionBoxPos(m_tInfo.fX, m_tInfo.fY + 10.f);
}

void CPlayer::Key_Input()
{
	if (CKeyMgr::Get_Instance()->Key_Press(VK_BACK))
	{
		CSceneMgr::Get_Instance()->Scene_Change(CSceneMgr::SC_MENU);
	}

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
	

	if (HIT != m_eCurState)
		{
			if(m_vecItem[2])
			{
				if (CKeyMgr::Get_Instance()->Key_Press(VK_RIGHT)|| 
					CKeyMgr::Get_Instance()->Key_Press(VK_LEFT)||
					CKeyMgr::Get_Instance()->Key_Press(VK_UP)||
					CKeyMgr::Get_Instance()->Key_Press(VK_DOWN))
					Move_ChargeFrame();
				else
				{
					m_tFrame.iStart = 0;
				}

				if (CKeyMgr::Get_Instance()->Key_Down(VK_RIGHT))
				{
					m_ChargeTime = GetTickCount64();
					m_ChargeMoitonTime = GetTickCount64();
					
				}
				if (CKeyMgr::Get_Instance()->Key_Up(VK_RIGHT))
				{
					if (m_ChargeTime + 1000 < GetTickCount64())
					{
						Laser_Attack(0.f, false);
					}
				}

				if (CKeyMgr::Get_Instance()->Key_Down(VK_LEFT))
				{
					m_ChargeTime = GetTickCount64();
					m_ChargeMoitonTime = GetTickCount64();
					
				}
				if (CKeyMgr::Get_Instance()->Key_Up(VK_LEFT))
				{
					if (m_ChargeTime + 1000 < GetTickCount64())
					{
						Laser_Attack(180.f, false);
					}
				}

				if (CKeyMgr::Get_Instance()->Key_Down(VK_UP))
				{
					m_ChargeTime = GetTickCount64();
					m_ChargeMoitonTime = GetTickCount64();
					
				}
				if (CKeyMgr::Get_Instance()->Key_Up(VK_UP))
				{
					if (m_ChargeTime + 1000 < GetTickCount64())
					{
						Laser_Attack(90.f, true);
					}
				}

				if (CKeyMgr::Get_Instance()->Key_Down(VK_DOWN))
				{
					m_ChargeTime = GetTickCount64();
					m_ChargeMoitonTime = GetTickCount64();
				}
				if (CKeyMgr::Get_Instance()->Key_Up(VK_DOWN))
				{
					if (m_ChargeTime + 1000 < GetTickCount64())
					{
						Laser_Attack(270.f, true);
					}
				}
			}

			else
			{
				if (CKeyMgr::Get_Instance()->Key_Press(VK_LEFT))
				{
					if (m_tFrame.iMotion != 3)
					{
						Set_Frame(1, 1, 3);
					}

					if (m_vecItem[1])
						Attack<CGuidedBullet>(180.f, false);
					else
						Attack<CPlayerBullet>(180.f, false);
				}
				else if (CKeyMgr::Get_Instance()->Key_Press(VK_RIGHT))
				{
					if (m_tFrame.iMotion != 1)
					{
						Set_Frame(1, 1, 1);
					}

					if (m_vecItem[1])
						Attack<CGuidedBullet>(0.f, false);
					else
						Attack<CPlayerBullet>(0.f, false);

				}
				else if (CKeyMgr::Get_Instance()->Key_Press(VK_DOWN))
				{
					if (m_tFrame.iMotion != 0)
					{
						Set_Frame(1, 1, 0);
					}

					if (m_vecItem[1])
						Attack<CGuidedBullet>(270.f, true);
					else
						Attack<CPlayerBullet>(270.f, true);

				}
				else if (CKeyMgr::Get_Instance()->Key_Press(VK_UP))
				{
					if (m_tFrame.iMotion != 2)
					{
						Set_Frame(1, 1, 2);
					}

					if(m_vecItem[1])
						Attack<CGuidedBullet>(90.f, true);
					else
						Attack<CPlayerBullet>(90.f, true);
				}
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
			CObj::Create_Bullet<CBombBullet>(m_tInfo.fX, m_tInfo.fY, 50.f, 50.f, m_fAngle, m_tStat.fHp, m_tStat.fAttack, m_tStat.fIntersection, 0.f)
		);
		--m_tItemInfo.iBomb;
	}

	if (GetAsyncKeyState(VK_RBUTTON))
	{
		//CObjMgr::Get_Instance()->Add_CObj(OBJ_BULLET, Create_Bullet<CMissile>(m_fAngle));
	}

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		//Attack<CBloodLaser>(0.f, false);
		/*CObjMgr::Get_Instance()->Add_CObj(
			OBJ_BULLET,
			CObj::Create_Bullet<CBloodLaser>(m_tInfo.fX+250.f, m_tInfo.fY, 500.f, 75.f, 0.f, m_tStat.fHp, m_tStat.fAttack, m_tStat.fIntersection, 5.f));*/
		//CObjMgr::Get_Instance()->Add_CObj(OBJ_BULLET, Create_Bullet<CMonsterBullet>(
		//	m_tInfo.fX + 50.f, m_tInfo.fY,
		//	34.f, 34.f,
		//	0 * 3, 0.f, 2, 300.f));
		//CObjMgr::Get_Instance()->Add_CObj(OBJ_BULLET, Create_Bullet<CGrenadeBullet>(m_fAngle));
		//m_dwTime = GetTickCount64();
		//CObjMgr::Get_Instance()->Add_CObj(OBJ_ITEM, CAbstractFactory<CCoin>::Create_Obj(m_tInfo.fX+100.f, m_tInfo.fY, 32.f, 32.f));
	}

}

template<typename T>
void CPlayer::Attack(float _fAngle, bool _bX)
{
	if(m_dwTime + m_fCoolDown < GetTickCount64())
	{
		float fX = m_tInfo.fX;
		float fY = m_tInfo.fY;
		float fAngle(10.f);
		if (_fAngle > 170.f)
			fAngle *= -1.f;
		if (_bX)
		{
			fX += m_fAttackPos;
		}
		else
			fY += m_fAttackPos;

		if(!m_vecItem[0])
		{
			if (_bX)
				fX += m_fAttackPos;
			else
				fY += m_fAttackPos;

			CObjMgr::Get_Instance()->Add_CObj(
				OBJ_BULLET,
				CObj::Create_Bullet<T>(fX, fY, 50.f, 50.f, _fAngle, m_tStat.fHp, m_tStat.fAttack, m_tStat.fIntersection, 5.f)
			);
			m_fAttackPos *= -1.f;
		}
		else
		{
			m_fAttackPos = 1.f;
			CObjMgr::Get_Instance()->Add_CObj(
				OBJ_BULLET,
				CObj::Create_Bullet<T>(fX, fY, 50.f, 50.f, _fAngle + fAngle, m_tStat.fHp, m_tStat.fAttack, m_tStat.fIntersection, 5.f)
			);

			if (_bX)
				fX -= m_fAttackPos;
			else
				fY -= m_fAttackPos;

			CObjMgr::Get_Instance()->Add_CObj(
				OBJ_BULLET,
				CObj::Create_Bullet<T>(fX, fY, 50.f, 50.f, _fAngle, m_tStat.fHp, m_tStat.fAttack, m_tStat.fIntersection, 5.f)
			);
			if (_bX)
				fX -= m_fAttackPos;
			else
				fY -= m_fAttackPos;
			CObjMgr::Get_Instance()->Add_CObj(
				OBJ_BULLET,
				CObj::Create_Bullet<T>(fX, fY, 50.f, 50.f, _fAngle- fAngle, m_tStat.fHp, m_tStat.fAttack, m_tStat.fIntersection, 5.f)
			);
		}
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

void CPlayer::Move_ChargeFrame()
{
	if(m_ChargeTime + 2000 < GetTickCount64())
	{
		m_tFrame.iStart = 2;
	}
	else
	{
		if (m_ChargeMoitonTime + 300 < GetTickCount64())
		{
			if (m_tFrame.iStart == 1)
				++m_tFrame.iStart;
			else
				m_tFrame.iStart = 1;
			m_ChargeMoitonTime = GetTickCount64();
		}
	}
}


void CPlayer::Laser_Attack(float _fAngle, bool _bX)
{
	if (m_dwTime + m_fCoolDown < GetTickCount64())
	{
		if (!_bX)
		{
			CObjMgr::Get_Instance()->Add_CObj(
				OBJ_BULLET,
				CObj::Create_Bullet<CBloodLaser>(m_tInfo.fX, m_tInfo.fY, 800.f, 50.f, _fAngle, m_tStat.fHp, m_tStat.fAttack, m_tStat.fIntersection, 5.f));

			m_dwTime = GetTickCount64();
			m_eCurState = CPlayer::ATTACK;
		}
		else
		{
			CObjMgr::Get_Instance()->Add_CObj(
				OBJ_BULLET,
				CObj::Create_Bullet<CBloodLaser>(m_tInfo.fX, m_tInfo.fY, 50.f, 800.f, _fAngle, m_tStat.fHp, m_tStat.fAttack, m_tStat.fIntersection, 5.f));

			m_dwTime = GetTickCount64();
			m_eCurState = CPlayer::ATTACK;
		}
	}

}

void CPlayer::Change_Motion()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case CPlayer::IDLE:
			if(!m_vecItem[2])
			{
				m_pFrameKey = L"Player_Head";
				Set_Frame(0, 1, 0);
			}
			else
			{
				m_pFrameKey = L"Player_Head_2";
				Set_Frame(0, 0, 0);
			}
			m_tFrame.dwFrameSpeed = 300;
			m_tFrame.dwTime = GetTickCount64();
			break;

		case CPlayer::ATTACK:
			if (!m_vecItem[2])
			{
				m_pFrameKey = L"Player_Head";
				m_tFrame.iStart = 1;
			}
			else
			{
				m_pFrameKey = L"Player_Head_2";
				m_tFrame.iStart = 3;
			}
			
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
			CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"Isaac_Hurt_Grunt0.mp3", SOUND_EFFECT, 1.f);
			break;

		case CPlayer::GETITEM:
			m_pFrameKey = L"Player_GetItem";
			Set_Frame(0, 0, 0);
			m_tFrame.dwFrameSpeed = 300;
			m_tFrame.dwTime = GetTickCount64();
			m_MotionTime = GetTickCount64();
			break;

		case CPlayer::DEATH:
			m_pFrameKey = L"Player_Death";
			Set_Frame(0, 0, 0);
			m_tFrame.dwFrameSpeed = 300;
			m_tFrame.dwTime = GetTickCount64();
			m_MotionTime = GetTickCount64();
			break;
		case CPlayer::MS_END:
			break;
		default:
			break;
		}

		m_ePreState = m_eCurState;
	}
		
}
