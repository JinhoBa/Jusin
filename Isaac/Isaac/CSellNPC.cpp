#include "pch.h"
#include "CSellNPC.h"
#include "CBmpMgr.h"
#include "CStoreRoom.h"

CSellNPC::CSellNPC()
{
}

CSellNPC::~CSellNPC()
{
	Release();
}

void CSellNPC::Initialize()
{
	m_eItemID = ITEM_NPC;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Item/Seller.bmp", L"Seller");
}

void CSellNPC::Late_Initialize()
{
	m_tInfo.fCX = 80.f;
	m_tInfo.fCY = 60.f;

	Set_CollisionBoxPos(m_tInfo.fX, m_tInfo.fY);
	Set_CollisionBoxSize(m_tInfo.fCX, m_tInfo.fCY);
}

int CSellNPC::Update()
{
	__super::Update_Rect();

	return NOEVENT;
}

int CSellNPC::Late_Update()
{
	return NOEVENT;
}

void CSellNPC::Render(HDC hDC)
{
	//__super::Collision_Render(hDC);
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Seller");

	GdiTransparentBlt(hDC,/// 복사 받을 dc
		m_tRect.left,		// 복사 받을 위치 좌표 left
		m_tRect.top,					// 복사 받을 위치 좌표 top
		100,				// 복사 받을 가로 사이즈
		100,				// 복사 받을 세로 사이즈
		hMemDC,							// 복사할 이미지 dc
		0,
		0,// * m_tFrame.iMotion,								// 복사할 이미지의 left, top
		(int)m_tInfo.fCX,//(int)m_tInfo.fCX,				// 복사할 이미지의 가로
		(int)m_tInfo.fCY,//(int)m_tInfo.fCY,				// 복사할 이미지의 세로
		RGB(255, 0, 255));
	
}

void CSellNPC::Release()
{
}

void CSellNPC::Collision(CObj* _pObj, HITPOINT _tHitPoint)
{
	if (OBJ_PLAYER == _pObj->Get_ObjID())
	{
		dynamic_cast<CStoreRoom*>(CSceneMgr::Get_Instance()->Get_CurScene())->Set_Start();
	}
}
