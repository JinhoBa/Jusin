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
#include "CFly.h"
#include "CBombFly.h"
#include "CSoundMgr.h"

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
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Door/Door_Gold.bmp", L"Door_Gold");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Door/Door_Boss.bmp", L"Door_Boss");
	CTileMgr::Get_Instance()->Load_Tile(L"../Data/Tile_Stage1.dat");

	CObj* pDoor = CAbstractFactory<CDoor>::Create_Obj(DOOR_TOPX, DOOR_TOPY, 50.f, 50.f);
	dynamic_cast<CDoor*>(pDoor)->Set_Door(0, L"Door_nomal", CSceneMgr::SC_TUTORIAL);
	CObjMgr::Get_Instance()->Add_CObj(OBJ_DOOR, pDoor);

	pDoor = CAbstractFactory<CDoor>::Create_Obj(DOOR_LEFTX, DOOR_LEFTY, 64.f, 64.f);
	dynamic_cast<CDoor*>(pDoor)->Set_Door(1, L"Door_Boss", CSceneMgr::SC_BOSS);
	CObjMgr::Get_Instance()->Add_CObj(OBJ_DOOR, pDoor);

	pDoor = CAbstractFactory<CDoor>::Create_Obj(DOOR_RIGHTX, DOOR_RIGHTY, 50.f, 50.f);
	dynamic_cast<CDoor*>(pDoor)->Set_Door(2, L"Door_Gold", CSceneMgr::SC_TREASURE);
	CObjMgr::Get_Instance()->Add_CObj(OBJ_DOOR, pDoor);


	CObjMgr::Get_Instance()->Add_CObj(OBJ_MONSTER, CAbstractFactory<CFly>::Create_Obj(200.f, 400.f, 32.f, 30.f));
	CObjMgr::Get_Instance()->Add_CObj(OBJ_MONSTER, CAbstractFactory<CFly>::Create_Obj(150.f, 400.f, 32.f, 30.f));
	CObjMgr::Get_Instance()->Add_CObj(OBJ_MONSTER, CAbstractFactory<CFly>::Create_Obj(100.f, 400.f, 32.f, 30.f));
	CObjMgr::Get_Instance()->Add_CObj(OBJ_MONSTER, CAbstractFactory<CBombFly>::Create_Obj(150.f, 400.f, 30.f, 30.f));

	CObjMgr::Get_Instance()->Add_CObj(OBJ_MONSTER, CAbstractFactory<CFly>::Create_Obj(700.f, 400.f, 32.f, 30.f));
	CObjMgr::Get_Instance()->Add_CObj(OBJ_MONSTER, CAbstractFactory<CFly>::Create_Obj(650.f, 400.f, 32.f, 30.f));
	CObjMgr::Get_Instance()->Add_CObj(OBJ_MONSTER, CAbstractFactory<CFly>::Create_Obj(600.f, 400.f, 32.f, 30.f));
	CObjMgr::Get_Instance()->Add_CObj(OBJ_MONSTER, CAbstractFactory<CBombFly>::Create_Obj(650.f, 400.f, 30.f, 30.f));

	m_iChennel = CSoundMgr::Get_Instance()->Get_AvailableChennel();
	CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
	CSoundMgr::Get_Instance()->PlaySound(L"Door_Heavy_Close.mp3", SOUND_EFFECT, 1.f);
                                                                                                                                                                                                                                                                                                          
	CSceneMgr::Get_Instance()->Set_SceneState(9, 4);
	CSceneMgr::Get_Instance()->Set_SceneState(10, 3);
	CSceneMgr::Get_Instance()->Set_SceneState(11, 7);
}

void CStage1::Update()
{
	if (!m_bDoorOpen && CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER).empty() )
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"Door_Heavy_Open.mp3", SOUND_EFFECT, 1.f);
		m_bDoorOpen = true;
	}
	
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

	CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
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
