#include "pch.h"
#include "CBox.h"
#include "CBmpMgr.h"
#include "CAbstractFactory.h"
#include "CBomb.h"
#include "CObjMgr.h"
#include "CCoin.h"
#include "CSoulHeart.h"
#include "CHeart.h"
#include "CSoundMgr.h"

CBox::CBox() : m_bOpen(false)
{
}

CBox::~CBox()
{
    Release();
}

void CBox::Initialize()
{
	m_eItemID = CItem::ITEM_BOX;

	__super::Set_Frame(0, 0, 0);
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwTime = GetTickCount64();

	Set_CollisionBoxPos(m_tInfo.fX, m_tInfo.fY);
	Set_CollisionBoxSize(m_tInfo.fCX, m_tInfo.fCY);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Item/Chest.bmp", L"Chest");

	m_vecSpownPos = {
		{50.0f, 50.0f},  // 우상단
		{50.0f, -50.0f}, // 우하단
		{-50.0f, -50.0f}, // 좌하단
		{-50.0f, 50.0f}   // 좌상단
	};
	
}

void CBox::Late_Initialize()
{
}

int CBox::Update()
{
	if (m_bDead)
	{
		return DEAD;
	}

	__super::Update_Rect();

	return NOEVENT;
}

int CBox::Late_Update()
{

	Set_CollisionBoxPos(m_tInfo.fX, m_tInfo.fY);

	return NOEVENT;
}

void CBox::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Chest");

	GdiTransparentBlt(hDC,/// 복사 받을 dc
		m_tRect.left,		// 복사 받을 위치 좌표 left
		m_tRect.top,					// 복사 받을 위치 좌표 top
		50,				// 복사 받을 가로 사이즈
		50,				// 복사 받을 세로 사이즈
		hMemDC,							// 복사할 이미지 dc
		(int)m_tInfo.fCX * m_tFrame.iStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,// * m_tFrame.iMotion,								// 복사할 이미지의 left, top
		(int)m_tInfo.fCX,//(int)m_tInfo.fCX,				// 복사할 이미지의 가로
		(int)m_tInfo.fCY,//(int)m_tInfo.fCY,				// 복사할 이미지의 세로
		RGB(255, 0, 255));
}

void CBox::Release()
{
	CSoundMgr::Get_Instance()->Return_Chennel(m_iSoundChennel);
}

void CBox::Collision(CObj* _pObj, HITPOINT _tHitPoint)
{
	switch (_pObj->Get_ObjID())
	{
	case OBJ_PLAYER:
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
}

void CBox::Drop_Item()
{
	m_tFrame.iStart = 1;
	Set_Sound(L"Chest_Open.mp3", 1.f);
	random_device rd;               // 하드웨어 기반 난수 생성기
	mt19937 gen(rd());              // 메르센 트위스터 엔진 초기화
	uniform_int_distribution<int> dist(0, 10); // 0~99 범위의 난수

	int i = dist(gen);

	if(5 > i)
		CObjMgr::Get_Instance()->Add_CObj(OBJ_ITEM, CAbstractFactory<CCoin>::Create_Obj(m_tInfo.fX + 150.f, m_tInfo.fY, 32.f, 32.f));
	else if(5 <= i && 7 > i)
	{
		CObjMgr::Get_Instance()->Add_CObj(OBJ_ITEM, CAbstractFactory<CBomb>::Create_Obj(m_tInfo.fX + 150.f, m_tInfo.fY, 50.f, 50.f));
	}
	else if (7 <= i && 9 >i)
	{
		CObjMgr::Get_Instance()->Add_CObj(OBJ_ITEM, CAbstractFactory<CHeart>::Create_Obj(m_tInfo.fX + 150.f, m_tInfo.fY , 32.f, 32.f));
	}
	else
	{
		CObjMgr::Get_Instance()->Add_CObj(OBJ_ITEM, CAbstractFactory<CSoulHeart>::Create_Obj(m_tInfo.fX + 150.f, m_tInfo.fY, 32.f, 32.f));
	}
	
}

void CBox::Drop_Item_Boss()
{
	m_tFrame.iStart = 1;
	Set_Sound(L"Chest_Open.mp3", 1.f);
	

	for (int j = 0; j < 4; ++j)
	{
		CObj* pObj;

		random_device rd;               // 하드웨어 기반 난수 생성기
		mt19937 gen(rd());              // 메르센 트위스터 엔진 초기화
		uniform_int_distribution<int> dist(0, 4); // 0~99 범위의 난수

		int i = dist(gen);

		float fAngle(80.f);
		float fX = m_tInfo.fX + m_vecSpownPos[j].first;
		float fY = m_tInfo.fY + m_vecSpownPos[j].second;
		
		if (m_vecSpownPos[j].first < 0.f)
			fAngle = 100.f;

		if (0== i)
		{
			pObj = CAbstractFactory<CCoin>::Create_Obj(fX, fY, 32.f, 32.f);
			pObj->Set_Angle(fAngle);
			CObjMgr::Get_Instance()->Add_CObj(OBJ_ITEM, pObj);
		}
		else if (1 == i)
		{
			pObj = CAbstractFactory<CBomb>::Create_Obj(fX, fY, 50.f, 50.f);
			pObj->Set_Angle(fAngle);
			CObjMgr::Get_Instance()->Add_CObj(OBJ_ITEM, pObj);
		}
		else if (2==i)
		{
			pObj = CAbstractFactory<CHeart>::Create_Obj(fX, fY, 32.f, 32.f);
			pObj->Set_Angle(fAngle);
			CObjMgr::Get_Instance()->Add_CObj(OBJ_ITEM, pObj);
		}
		else
		{
			pObj = CAbstractFactory<CSoulHeart>::Create_Obj(fX, fY, 32.f, 32.f);
			pObj->Set_Angle(fAngle);
			CObjMgr::Get_Instance()->Add_CObj(OBJ_ITEM, pObj);
		}
	}
}
