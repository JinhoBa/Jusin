#include "pch.h"
#include "CStage1.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CTileMgr.h"
#include "CUIMgr.h"
#include "CCollisionMgr.h"
#include "CBmpMgr.h"
#include "CKey.h"
#include "CDoor.h"
#include "CBoss.h"

CStage1::CStage1()
{
}

CStage1::~CStage1()
{
	Release();
}

void CStage1::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Room/nomalMap1.bmp", L"nomalMap");
	//CObjMgr::Get_Instance()->Add_CObj(OBJ_ITEM, CAbstractFactory<CKey>::Create_Obj(400.f, 400.f, 42.f, 42.f));
	CObjMgr::Get_Instance()->Add_CObj(OBJ_MONSTER, CAbstractFactory<CBoss>::Create_Obj(600.f, 300.f, 120.f, 120.f));

	CTileMgr::Get_Instance()->Load_Tile(L"../Data/Tile_Tutorial2.dat");

	CObj* pDoor = CAbstractFactory<CDoor>::Create_Obj(WINCX * 0.5f, WINCY - 25.f, 50.f, 50.f);
	pDoor->Set_FramMotion(3);
	pDoor->Set_FrameKey(L"Door_nomal");
	dynamic_cast<CDoor*>(pDoor)->Set_SceneID(CSceneMgr::SC_TUTORIAL);
	CObjMgr::Get_Instance()->Add_CObj(OBJ_DOOR, pDoor);
}

void CStage1::Update()
{
	CObjMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
	CUIMgr::Get_Instance()->Update();
}

void CStage1::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	CTileMgr::Get_Instance()->Late_Update();
	CUIMgr::Get_Instance()->Late_Update();

	
	CCollisionMgr::Get_Instance()->Collision_Tile(CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER), CTileMgr::Get_Instance()->Get_vecTile());
	CCollisionMgr::Get_Instance()->Collision_Tile(CObjMgr::Get_Instance()->Get_ObjList(OBJ_BULLET), CTileMgr::Get_Instance()->Get_vecTile());
	CCollisionMgr::Get_Instance()->Collision_Tile(CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER), CTileMgr::Get_Instance()->Get_vecTile());
	CCollisionMgr::Get_Instance()->Collision_Tile(CObjMgr::Get_Instance()->Get_ObjList(OBJ_EFFECT), CTileMgr::Get_Instance()->Get_vecTile());
	CCollisionMgr::Get_Instance()->Collision_Obj(CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER), CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER));
	CCollisionMgr::Get_Instance()->Collision_Obj(CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER), CObjMgr::Get_Instance()->Get_ObjList(OBJ_BULLET));
	CCollisionMgr::Get_Instance()->Collision_Obj(CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER), CObjMgr::Get_Instance()->Get_ObjList(OBJ_ITEM));
	CCollisionMgr::Get_Instance()->Collision_Obj(CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER), CObjMgr::Get_Instance()->Get_ObjList(OBJ_BULLET));
	CCollisionMgr::Get_Instance()->Collision_Obj(CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER), CObjMgr::Get_Instance()->Get_ObjList(OBJ_EFFECT));
	CCollisionMgr::Get_Instance()->Collision_Obj(CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER), CObjMgr::Get_Instance()->Get_ObjList(OBJ_DOOR));
}

void CStage1::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"nomalMap");

	BitBlt(hDC,
		0,
		0,
		WINCX, WINCY,
		hMemDC,
		0, 0,
		SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);
	CTileMgr::Get_Instance()->Render(hDC);
	CUIMgr::Get_Instance()->Render(hDC);
}

void CStage1::Release()
{
	for(int i = 0; i < size(m_ObjList); ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}

	for_each(m_vecTile.begin(), m_vecTile.end(), Safe_Delete<CObj*>);
	m_vecTile.clear();
}
