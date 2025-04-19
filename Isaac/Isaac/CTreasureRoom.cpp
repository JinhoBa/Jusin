#include "pch.h"
#include "CTreasureRoom.h"
#include "CBmpMgr.h"
#include "CAbstractFactory.h"
#include "CObjMgr.h"
#include "CDoor.h"
#include "CTileMgr.h"
#include "CUIMgr.h"
#include "CCollisionMgr.h"
#include "CCyclops.h"
#include "CPassiveItem.h"
#include "CSoundMgr.h"

CTreasureRoom::CTreasureRoom() : m_bFirst(true), m_dwTime(GetTickCount64())
{
}

CTreasureRoom::~CTreasureRoom()
{
	Release();
}

void CTreasureRoom::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Room/BaseMap1.bmp", L"BaseMap1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Door/Door_Gold.bmp", L"Door_Gold");
	CSoundMgr::Get_Instance()->PlaySound(L"TreasureRoomEnter.mp3", SOUND_INTRO, 1.f);
	CObj* pObj;

	pObj = CAbstractFactory<CPassiveItem>::Create_Obj(300.f, 400.f, 50.f, 50.f);
	dynamic_cast<CItem*>(pObj)->Set_Item(L"Item_Spoon", CItem::ITEM_SPOON);
	CObjMgr::Get_Instance()->Add_CObj(OBJ_ITEM, pObj);

	pObj = CAbstractFactory<CPassiveItem>::Create_Obj(500.f, 400.f, 50.f, 50.f);
	dynamic_cast<CItem*>(pObj)->Set_Item(L"Item_Cyclops", CItem::ITEM_CYCLOPS);
	CObjMgr::Get_Instance()->Add_CObj(OBJ_ITEM, pObj);

	pObj = CAbstractFactory<CDoor>::Create_Obj(DOOR_LEFTX, DOOR_LEFTY, 50.f, 50.f);
	dynamic_cast<CDoor*>(pObj)->Set_Door(1, L"Door_Gold", CSceneMgr::SC_STAGE1);
	dynamic_cast<CDoor*>(pObj)->Set_Open();
	CObjMgr::Get_Instance()->Add_CObj(OBJ_DOOR, pObj);

	CTileMgr::Get_Instance()->Load_Tile(L"../Data/Tile_TreasureRoom.dat");

	CSceneMgr::Get_Instance()->Set_SceneState(CSceneMgr::SC_TREASURE, 9, 0);
}

void CTreasureRoom::Update()
{
	if (m_bFirst && m_dwTime + 5000 < GetTickCount64())
	{
		m_bFirst = false;
		
	}
	CObjMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
	CUIMgr::Get_Instance()->Update();
}

void CTreasureRoom::Late_Update()
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

void CTreasureRoom::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BaseMap1");

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

void CTreasureRoom::Release()
{
	for (int i = 0; i < size(m_ObjList); ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}

	for_each(m_vecTile.begin(), m_vecTile.end(), Safe_Delete<CObj*>);
	m_vecTile.clear();
}
