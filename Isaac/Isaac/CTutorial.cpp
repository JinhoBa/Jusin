#include "pch.h"
#include "CTutorial.h"
#include "CBmpMgr.h"
#include "CPlayer.h"
#include "CAbstractFactory.h"
#include "CObjMgr.h"
#include "CTileMgr.h"
#include "CCollisionMgr.h"
#include "CFly.h"
#include "CBombFly.h"
#include "CUIMgr.h"
#include "CUIBar.h"
#include "CCoin.h"
#include "CKey.h"
#include "CDoor.h"
#include "CSoulHeart.h"
#include "CBomb.h"
#include "CBox.h"
#include "CBoss.h"
#include "CHeart.h"
#include "CCyclops.h"

CTutorial::CTutorial()
{
}

CTutorial::~CTutorial()
{
	Release();
}

void CTutorial::Initialize()
{

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Room/BaseMap.bmp", L"Tutorial");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Door/Door_nomal.bmp", L"Door_nomal");

	CObjMgr::Get_Instance()->Add_CObj(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create_Obj(400.f, 300.f, 50.f, 40.f));
	//CObjMgr::Get_Instance()->Add_CObj(OBJ_MONSTER, CAbstractFactory<CFly>::Create_Obj(600.f, 200.f, 32.f, 30.f));
	//CObjMgr::Get_Instance()->Add_CObj(OBJ_MONSTER, CAbstractFactory<CBombFly>::Create_Obj(200.f, 200.f, 30.f, 30.f));
	//CObjMgr::Get_Instance()->Add_CObj(OBJ_MONSTER, CAbstractFactory<CBoss>::Create_Obj(600.f, 300.f, 120.f, 120.f));

	//CObjMgr::Get_Instance()->Add_CObj(OBJ_ITEM, CAbstractFactory<CCoin>::Create_Obj(200.f, 230.f, 32.f, 32.f));
	//CObjMgr::Get_Instance()->Add_CObj(OBJ_ITEM, CAbstractFactory<CHeart>::Create_Obj(250.f, 230.f, 32.f, 32.f));
	//CObjMgr::Get_Instance()->Add_CObj(OBJ_ITEM, CAbstractFactory<CHeart>::Create_Obj(300.f, 230.f, 32.f, 32.f));
	//CObjMgr::Get_Instance()->Add_CObj(OBJ_ITEM, CAbstractFactory<CHeart>::Create_Obj(350.f, 230.f, 32.f, 32.f));
	//CObjMgr::Get_Instance()->Add_CObj(OBJ_ITEM, CAbstractFactory<CHeart>::Create_Obj(400.f, 230.f, 32.f, 32.f));
	//CObjMgr::Get_Instance()->Add_CObj(OBJ_ITEM, CAbstractFactory<CBox>::Create_Obj(200.f, 300.f, 32.f, 32.f));
	CObjMgr::Get_Instance()->Add_CObj(OBJ_ITEM, CAbstractFactory<CCyclops>::Create_Obj(200.f, 300.f, 50.f, 50.f));



	CObj* pDoor = CAbstractFactory<CDoor>::Create_Obj(DOOR_BOTTOMX, DOOR_BOTTOMY, 50.f, 50.f);
	pDoor->Set_FramMotion(3);
	pDoor->Set_FrameKey(L"Door_nomal");
	dynamic_cast<CDoor*>(pDoor)->Set_SceneID(CSceneMgr::SC_STAGE1);
	CObjMgr::Get_Instance()->Add_CObj(OBJ_DOOR, pDoor);


	CTileMgr::Get_Instance()->Load_Tile(L"../Data/Tile_Tutorial.dat");


	CUIMgr::Get_Instance()->Add_UI(UI_BAR, CAbstractFactory<CUIBar>::Create_UI());
}

void CTutorial::Update()
{
	CObjMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
	CUIMgr::Get_Instance()->Update();
}

void CTutorial::Late_Update()
{

	CObjMgr::Get_Instance()->Late_Update();
	CTileMgr::Get_Instance()->Late_Update();
	CUIMgr::Get_Instance()->Late_Update();

	CCollisionMgr::Get_Instance()->Collision_Obj(CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER), CObjMgr::Get_Instance()->Get_ObjList(OBJ_DOOR));
	CCollisionMgr::Get_Instance()->Collision_Tile(CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER), CTileMgr::Get_Instance()->Get_vecTile());
	CCollisionMgr::Get_Instance()->Collision_Tile(CObjMgr::Get_Instance()->Get_ObjList(OBJ_BULLET), CTileMgr::Get_Instance()->Get_vecTile());
	CCollisionMgr::Get_Instance()->Collision_Tile(CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER), CTileMgr::Get_Instance()->Get_vecTile());
	CCollisionMgr::Get_Instance()->Collision_Tile(CObjMgr::Get_Instance()->Get_ObjList(OBJ_EFFECT), CTileMgr::Get_Instance()->Get_vecTile());
	CCollisionMgr::Get_Instance()->Collision_Obj(CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER), CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER));
	CCollisionMgr::Get_Instance()->Collision_Obj(CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER), CObjMgr::Get_Instance()->Get_ObjList(OBJ_BULLET));
	CCollisionMgr::Get_Instance()->Collision_Obj(CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER), CObjMgr::Get_Instance()->Get_ObjList(OBJ_ITEM));
	CCollisionMgr::Get_Instance()->Collision_Obj(CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER), CObjMgr::Get_Instance()->Get_ObjList(OBJ_BULLET));
	CCollisionMgr::Get_Instance()->Collision_Obj(CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER), CObjMgr::Get_Instance()->Get_ObjList(OBJ_EFFECT));
	CCollisionMgr::Get_Instance()->Collision_Obj(CObjMgr::Get_Instance()->Get_ObjList(OBJ_BULLET), CObjMgr::Get_Instance()->Get_ObjList(OBJ_EFFECT));

	
}

void CTutorial::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Tutorial");

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

void CTutorial::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), Safe_Delete<CObj*>);
	m_vecTile.clear();
}

