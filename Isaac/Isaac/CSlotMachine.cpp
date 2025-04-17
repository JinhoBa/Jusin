#include "pch.h"
#include "CSlotMachine.h"
#include "CBmpMgr.h"
#include "CSoundMgr.h"
#include "CTools.h"
#include "CPlayer.h"
#include "CObjMgr.h"
#include "CHeart.h"
#include "CBomb.h"
#include "CCoin.h"
#include "CKey.h"

CSlotMachine::CSlotMachine() : m_dwTime(NULL), m_eCurState(M_END), m_eOldState(M_END)
{
}

CSlotMachine::~CSlotMachine()
{
	Release();
}

void CSlotMachine::Initialize()
{
	m_eItemID = CItem::ITEM_SLOTMACHINE;
	m_eCurState = IDLE;

	__super::Set_Frame(0, 3, 0);
	m_tFrame.dwFrameSpeed = 50;
	m_tFrame.dwTime = GetTickCount64();

	Set_CollisionBoxPos(m_tInfo.fX, m_tInfo.fY);
	Set_CollisionBoxSize(50, 50);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Item/SlotMachine.bmp", L"SlotMachine");


	
	//m_vecSpownPos = {
	//	{50.0f, 50.0f},  // 우상단
	//	{50.0f, -50.0f}, // 우하단
	//	{-50.0f, -50.0f}, // 좌하단
	//	{-50.0f, 50.0f}   // 좌상단
	//};
}

void CSlotMachine::Late_Initialize()
{
}

int CSlotMachine::Update()
{
	if (m_bDead)
	{
		return DEAD;
	}

	__super::Update_Rect();

	return NOEVENT;
}

int CSlotMachine::Late_Update()
{
	switch (m_eCurState)
	{
	case IDLE:
		m_dwTime = GetTickCount64();
		break;

	case MOVE:
		if (m_dwTime + 1000 < GetTickCount64())
		{
			m_eCurState = STOP;
			int iTmp = CTools::Get_RandomNumber(0, 4);
			
			if (0 < iTmp && iTmp < 5)
			{
				Drop_Item(iTmp);
				m_tFrame.iMotion = iTmp;
				m_tFrame.iStart = 0;
			}
			else
			{
				m_tFrame.iMotion = 0;
				m_tFrame.iStart = CTools::Get_RandomNumber(0, 3);
			}

			m_dwTime = GetTickCount64();
		}
		else
			__super::Move_Frame();
		break;

	case STOP:
		CSoundMgr::Get_Instance()->Return_Chennel(m_iSoundChennel);
		if (m_dwTime + 1000 < GetTickCount64())
		{
			m_eCurState = IDLE;
			m_dwTime = GetTickCount64();
		}
		break;
	case BROKEN:
		m_tFrame.iMotion = 5;
		break;
	default:
		break;
	}


	Set_CollisionBoxPos(m_tInfo.fX, m_tInfo.fY);

	return NOEVENT;
}

void CSlotMachine::Render(HDC hDC)
{
	

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"SlotMachine");

	GdiTransparentBlt(hDC,/// 복사 받을 dc
		m_tRect.left -20,		// 복사 받을 위치 좌표 left
		m_tRect.top -35,					// 복사 받을 위치 좌표 top
		100,				// 복사 받을 가로 사이즈
		100,				// 복사 받을 세로 사이즈
		hMemDC,							// 복사할 이미지 dc
		(int)m_tInfo.fCX * m_tFrame.iStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,// * m_tFrame.iMotion,								// 복사할 이미지의 left, top
		(int)m_tInfo.fCX,//(int)m_tInfo.fCX,				// 복사할 이미지의 가로
		(int)m_tInfo.fCY,//(int)m_tInfo.fCY,				// 복사할 이미지의 세로
		RGB(255, 0, 255));
	//__super::Collision_Render(hDC);
}

void CSlotMachine::Release()
{
	CSoundMgr::Get_Instance()->Return_Chennel(m_iSoundChennel);
}

void CSlotMachine::Collision(CObj* _pObj, HITPOINT _tHitPoint)
{
	switch (_pObj->Get_ObjID())
	{
	case OBJ_PLAYER:
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
		if (m_eCurState == IDLE && 0 < dynamic_cast<CPlayer*>(_pObj)->Get_ItemInfo()->iCoin  )
		{
			dynamic_cast<CPlayer*>(_pObj)->Set_Coin(-1);
			m_iSoundChennel = CSoundMgr::Get_Instance()->Get_AvailableChennel();
			CSoundMgr::Get_Instance()->PlayLoop(L"slottouched.mp3", m_iSoundChennel, 1.f);
			m_eCurState = MOVE;
			m_tFrame.iMotion = 0;

		}
		break;
	case OBJ_BULLET:
		m_eCurState = BROKEN;
		_pObj->Set_Dead();
	case OBJ_EFFECT:
		m_eCurState = BROKEN;
		break;
	default:
		break;
	}
}

void CSlotMachine::Drop_Item(int i)
{
	if(0<i && i <5)
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"slotspawn2.mp3", SOUND_EFFECT, 1.f);
	}
	switch (i)
	{
	case 1: // 하트
		CObjMgr::Get_Instance()->Add_CObj(OBJ_ITEM, CAbstractFactory<CHeart>::Create_Obj(m_tInfo.fX, m_tInfo.fY, 32.f, 32.f));
		break;

	case 2: // 폭탄
		CObjMgr::Get_Instance()->Add_CObj(OBJ_ITEM, CAbstractFactory<CBomb>::Create_Obj(m_tInfo.fX, m_tInfo.fY, 64.f, 64.f));
		break;

	case 3: // 열쇠
		CObjMgr::Get_Instance()->Add_CObj(OBJ_ITEM, CAbstractFactory<CKey>::Create_Obj(m_tInfo.fX, m_tInfo.fY, 42.f, 42.f));
		break;

	case 4:  // 동전
	for(int j=0; j < 10; ++j)
	{
		CObjMgr::Get_Instance()->Add_CObj(OBJ_ITEM, CAbstractFactory<CCoin>::Create_Obj(m_tInfo.fX, m_tInfo.fY, 32.f, 32.f));
	}
		break;

	default:
		break;
	}
	
}
