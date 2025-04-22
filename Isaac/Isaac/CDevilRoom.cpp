#include "pch.h"
#include "CDevilRoom.h"
#include "CBmpMgr.h"
#include "CTileMgr.h"
#include "CObjMgr.h"
#include "CUIMgr.h"
#include "CCollisionMgr.h"
#include "CDoor.h"
#include "CCharger.h"
#include "CItem.h"
#include "CPassiveItem.h"
#include "CMulligan.h"

CDevilRoom::CDevilRoom() : m_bClear(false)
{
}

CDevilRoom::~CDevilRoom()
{
	Release();
}

void CDevilRoom::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Room/DevilRoom.bmp", L"DevilRoom");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Door/Door_Devil.bmp", L"Door_Devil");

	CObj* pObj;
	pObj = CAbstractFactory<CCharger>::Create_Obj(87.f, 300.f, 32.f, 30.f);
	dynamic_cast<CCharger*>(pObj)->Set_DIR(8);
	CObjMgr::Get_Instance()->Add_CObj(OBJ_MONSTER, pObj);

	pObj = CAbstractFactory<CCharger>::Create_Obj(203.f, 400.f, 32.f, 30.f);
	dynamic_cast<CCharger*>(pObj)->Set_DIR(2);
	CObjMgr::Get_Instance()->Add_CObj(OBJ_MONSTER, pObj);

	

	pObj = CAbstractFactory<CCharger>::Create_Obj(400.f, 290.f, 32.f, 30.f);
	dynamic_cast<CCharger*>(pObj)->Set_DIR(4);
	CObjMgr::Get_Instance()->Add_CObj(OBJ_MONSTER, pObj);

	pObj = CAbstractFactory<CCharger>::Create_Obj(655.f, 300.f, 32.f, 30.f);
	dynamic_cast<CCharger*>(pObj)->Set_DIR(8);
	CObjMgr::Get_Instance()->Add_CObj(OBJ_MONSTER, pObj);

	pObj = CAbstractFactory<CCharger>::Create_Obj(625.f, 397.f, 32.f, 30.f);
	dynamic_cast<CCharger*>(pObj)->Set_DIR(4);
	CObjMgr::Get_Instance()->Add_CObj(OBJ_MONSTER, pObj);
	



	CObjMgr::Get_Instance()->Add_CObj(OBJ_MONSTER, CAbstractFactory<CMulligan>::Create_Obj(600.f, 500.f, 36.f, 52.f));
	CObjMgr::Get_Instance()->Add_CObj(OBJ_MONSTER, CAbstractFactory<CMulligan>::Create_Obj(87.f, 200.f, 36.f, 52.f));
	//CObjMgr::Get_Instance()->Add_CObj(OBJ_MONSTER, CAbstractFactory<CMulligan>::Create_Obj(400.f, 400.f, 36.f, 52.f));



	CObj* pDoor = CAbstractFactory<CDoor>::Create_Obj(DOOR_BOTTOMX, DOOR_BOTTOMY, 50.f, 50.f);
	pDoor->Set_FramMotion(3);
	pDoor->Set_FrameKey(L"Door_Devil");
	dynamic_cast<CDoor*>(pDoor)->Set_SceneID(CSceneMgr::SC_STAGE2);
	CObjMgr::Get_Instance()->Add_CObj(OBJ_DOOR, pDoor);


	CTileMgr::Get_Instance()->Load_Tile(L"../Data/Tile_DevilRoom.dat");


	CSceneMgr::Get_Instance()->Set_SceneState(CSceneMgr::SC_DEVILROOM, 3, 0);
}

void CDevilRoom::Update()
{
	CObjMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
	CUIMgr::Get_Instance()->Update();
}

void CDevilRoom::Late_Update()
{
	if (!m_bClear && CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER).empty())
	{
		m_bClear = true;
		CObj* pObj = CAbstractFactory<CPassiveItem>::Create_Obj(400.f, 400.f, 50.f, 50.f);
		dynamic_cast<CItem*>(pObj)->Set_Item(L"Item_118", CItem::ITEM_118);
		CObjMgr::Get_Instance()->Add_CObj(OBJ_ITEM, pObj);
	}

	CObjMgr::Get_Instance()->Late_Update();
	CTileMgr::Get_Instance()->Late_Update();
	CUIMgr::Get_Instance()->Late_Update();

	CCollisionMgr::Get_Instance()->Collision_Obj(CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER), CObjMgr::Get_Instance()->Get_ObjList(OBJ_DOOR));
	CCollisionMgr::Get_Instance()->Collision_Tile(CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER), CTileMgr::Get_Instance()->Get_vecTile());
	CCollisionMgr::Get_Instance()->Collision_Tile(CObjMgr::Get_Instance()->Get_ObjList(OBJ_ITEM), CTileMgr::Get_Instance()->Get_vecTile());
	CCollisionMgr::Get_Instance()->Collision_Tile(CObjMgr::Get_Instance()->Get_ObjList(OBJ_BULLET), CTileMgr::Get_Instance()->Get_vecTile());
	CCollisionMgr::Get_Instance()->Collision_Tile(CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER), CTileMgr::Get_Instance()->Get_vecTile());
	CCollisionMgr::Get_Instance()->Collision_Tile(CObjMgr::Get_Instance()->Get_ObjList(OBJ_EFFECT), CTileMgr::Get_Instance()->Get_vecTile());
	CCollisionMgr::Get_Instance()->Collision_Obj(CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER), CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER));
	CCollisionMgr::Get_Instance()->Collision_Obj(CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER), CObjMgr::Get_Instance()->Get_ObjList(OBJ_BULLET));
	CCollisionMgr::Get_Instance()->Collision_Obj(CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER), CObjMgr::Get_Instance()->Get_ObjList(OBJ_ITEM));
	CCollisionMgr::Get_Instance()->Collision_Obj(CObjMgr::Get_Instance()->Get_ObjList(OBJ_ITEM), CObjMgr::Get_Instance()->Get_ObjList(OBJ_ITEM));
	//CCollisionMgr::Get_Instance()->Collision_Obj(CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER), CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER));
	CCollisionMgr::Get_Instance()->Collision_Obj(CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER), CObjMgr::Get_Instance()->Get_ObjList(OBJ_BULLET));
	CCollisionMgr::Get_Instance()->Collision_Obj(CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER), CObjMgr::Get_Instance()->Get_ObjList(OBJ_EFFECT));
	CCollisionMgr::Get_Instance()->Collision_Obj(CObjMgr::Get_Instance()->Get_ObjList(OBJ_BULLET), CObjMgr::Get_Instance()->Get_ObjList(OBJ_EFFECT));

}

void CDevilRoom::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"DevilRoom");

	BitBlt(hDC,
		0,
		0,
		WINCX, WINCY,
		hMemDC,
		0, 0,
		SRCCOPY);
	CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
	CUIMgr::Get_Instance()->Render(hDC);
}

void CDevilRoom::Release()
{
	for (int i = 0; i < size(m_ObjList); ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}

	for_each(m_vecTile.begin(), m_vecTile.end(), Safe_Delete<CObj*>);
	m_vecTile.clear();
}
