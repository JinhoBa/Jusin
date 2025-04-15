#include "pch.h"
#include "CStoreRoom.h"
#include "CBmpMgr.h"
#include "CAbstractFactory.h"
#include "CSoundMgr.h"
#include "CPassiveItem.h"
#include "CObjMgr.h"
#include "CDoor.h"
#include "CTileMgr.h"
#include "CUIMgr.h"
#include "CCollisionMgr.h"
#include "CSlotMachine.h"

CStoreRoom::CStoreRoom()
{
}

CStoreRoom::~CStoreRoom()
{
	Release();
}

void CStoreRoom::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Room/StoreMap.bmp", L"StoreMap");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Door/Door_nomal.bmp", L"Door_nomal");
	//CSoundMgr::Get_Instance()->PlaySound(L"TreasureRoomEnter.mp3", SOUND_INTRO, 1.f);

	CObj* pObj = CAbstractFactory<CDoor>::Create_Obj(DOOR_RIGHTX, DOOR_RIGHTY, 50.f, 50.f);
	dynamic_cast<CDoor*>(pObj)->Set_Door(2, L"Door_nomal", CSceneMgr::SC_TUTORIAL);
	dynamic_cast<CDoor*>(pObj)->Set_Open();
	CObjMgr::Get_Instance()->Add_CObj(OBJ_DOOR, pObj);

	//pObj = CAbstractFactory<CPassiveItem>::Create_Obj(400.f, 400.f, 50.f, 50.f);
	//dynamic_cast<CItem*>(pObj)->Set_Item(L"Item_Spoon", CItem::ITEM_SPOON);
	//CObjMgr::Get_Instance()->Add_CObj(OBJ_ITEM, pObj);

	CObjMgr::Get_Instance()->Add_CObj(OBJ_ITEM, CAbstractFactory<CSlotMachine>::Create_Obj(320.f, 370.f, 50.f, 50.f));

	

	


	CTileMgr::Get_Instance()->Load_Tile(L"../Data/Tile_TreasureRoom.dat");

	CSceneMgr::Get_Instance()->Set_SceneState(CSceneMgr::SC_STOREROOM, 12, 0);
}

void CStoreRoom::Update()
{
	CObjMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
	CUIMgr::Get_Instance()->Update();
}

void CStoreRoom::Late_Update()
{
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
	CCollisionMgr::Get_Instance()->Collision_Obj(CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER), CObjMgr::Get_Instance()->Get_ObjList(OBJ_BULLET));
	CCollisionMgr::Get_Instance()->Collision_Obj(CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER), CObjMgr::Get_Instance()->Get_ObjList(OBJ_EFFECT));
	CCollisionMgr::Get_Instance()->Collision_Obj(CObjMgr::Get_Instance()->Get_ObjList(OBJ_BULLET), CObjMgr::Get_Instance()->Get_ObjList(OBJ_EFFECT));
}

void CStoreRoom::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"StoreMap");

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

void CStoreRoom::Release()
{
	for (int i = 0; i < size(m_ObjList); ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}

	for_each(m_vecTile.begin(), m_vecTile.end(), Safe_Delete<CObj*>);
	m_vecTile.clear();
}
