#include "pch.h"
#include "CStage2.h"
#include "CBmpMgr.h"
#include "CTileMgr.h"
#include "CDoor.h"
#include "CObjMgr.h"
#include "CSoundMgr.h"
#include "CUIMgr.h"
#include "CCollisionMgr.h"
#include "CHost.h"

CStage2::CStage2()
{
}

CStage2::~CStage2()
{
	Release();
}

void CStage2::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Room/nomalMap1.bmp", L"nomalMap");
	CTileMgr::Get_Instance()->Load_Tile(L"../Data/Tile_Tutorial.dat");

	CObj* pDoor = CAbstractFactory<CDoor>::Create_Obj(DOOR_BOTTOMX, DOOR_BOTTOMY, 50.f, 50.f);
	dynamic_cast<CDoor*>(pDoor)->Set_Door(3, L"Door_nomal", CSceneMgr::SC_TUTORIAL);
	CObjMgr::Get_Instance()->Add_CObj(OBJ_DOOR, pDoor);


	CObjMgr::Get_Instance()->Add_CObj(OBJ_MONSTER, CAbstractFactory<CHost>::Create_Obj(250.f, 300.f, 36.f, 51.f));
	CObjMgr::Get_Instance()->Add_CObj(OBJ_MONSTER, CAbstractFactory<CHost>::Create_Obj(550.f, 400.f, 36.f, 51.f));
	//CObjMgr::Get_Instance()->Add_CObj(OBJ_MONSTER, CAbstractFactory<CFly>::Create_Obj(150.f, 400.f, 32.f, 30.f));
	

	m_iChennel = CSoundMgr::Get_Instance()->Get_AvailableChennel();
	CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
	CSoundMgr::Get_Instance()->PlaySound(L"Door_Heavy_Close.mp3", SOUND_EFFECT, 1.f);


	CSceneMgr::Get_Instance()->Set_SceneState(CSceneMgr::SC_STAGE2, 3, 0);
	
}

void CStage2::Update()
{
	if (!m_bDoorOpen && CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER).empty())
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"Door_Heavy_Open.mp3", SOUND_EFFECT, 1.f);
		m_bDoorOpen = true;
	}

	CObjMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
	CUIMgr::Get_Instance()->Update();
}

void CStage2::Late_Update()
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

void CStage2::Render(HDC hDC)
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

void CStage2::Release()
{
	for (int i = 0; i < size(m_ObjList); ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}

	for_each(m_vecTile.begin(), m_vecTile.end(), Safe_Delete<CObj*>);
	m_vecTile.clear();
}
