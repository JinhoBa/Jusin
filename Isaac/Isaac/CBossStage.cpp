#include "pch.h"
#include "CBossStage.h"
#include "CObjMgr.h"
#include "CBoss.h"
#include "CAbstractFactory.h"
#include "CDoor.h"
#include "CTileMgr.h"
#include "CUIBar.h"
#include "CUIMgr.h"
#include "CCollisionMgr.h"
#include "CBmpMgr.h"
#include "CBossHp.h"
#include "CSoundMgr.h"

CBossStage::CBossStage() : m_dwTime(GetTickCount64()), m_bFirst(true)
{
}

CBossStage::~CBossStage()
{
	Release();
}

void CBossStage::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Room/Boss_Room.bmp", L"Boss_Room");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Door/Door_nomal.bmp", L"Door_nomal");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Boss/Boss_CutScene.bmp", L"Boss_CutScene");

	CTileMgr::Get_Instance()->Load_Tile(L"../Data/Tile_BossStage.dat");

	CObjMgr::Get_Instance()->Add_CObj(OBJ_MONSTER, 
		CAbstractFactory<CBoss>::Create_Obj(200.f, 300.f, 120.f, 120.f));


	CObj* pDoor = CAbstractFactory<CDoor>::Create_Obj(DOOR_RIGHTX, DOOR_RIGHTY, 64.f, 64.f);
	dynamic_cast<CDoor*>(pDoor)->Set_Door(2, L"Door_Boss", CSceneMgr::SC_STAGE1);
	CObjMgr::Get_Instance()->Add_CObj(OBJ_DOOR, pDoor);
	

	CUIMgr::Get_Instance()->Add_UI(UI_BAR, CAbstractFactory<CUIBar>::Create_UI());
	CUIMgr::Get_Instance()->Add_UI(UI_BOSSHP, CAbstractFactory<CBossHp>::Create_UI());

	CSoundMgr::Get_Instance()->StopSound(SOUND_INTRO);
	CSoundMgr::Get_Instance()->PlaySound(L"bossintro.mp3", SOUND_INTRO, 1.f);

	

	CSceneMgr::Get_Instance()->Set_SceneState(9, 6);

}

void CBossStage::Update()
{
	if (m_bFirst && m_dwTime + 5000 < GetTickCount64())
	{
		m_bFirst = false;
		CSoundMgr::Get_Instance()->PlayBGM(L"BossStageBGM.mp3", 0.3f);
	}

	if(!m_bFirst)
	{
		CTileMgr::Get_Instance()->Update();
		CObjMgr::Get_Instance()->Update();
		CUIMgr::Get_Instance()->Update();
	}
}

void CBossStage::Late_Update()
{
	if (!m_bFirst)
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
		CCollisionMgr::Get_Instance()->Collision_Obj(CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER), CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER));
		CCollisionMgr::Get_Instance()->Collision_Obj(CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER), CObjMgr::Get_Instance()->Get_ObjList(OBJ_EFFECT));
		CCollisionMgr::Get_Instance()->Collision_Obj(CObjMgr::Get_Instance()->Get_ObjList(OBJ_BULLET), CObjMgr::Get_Instance()->Get_ObjList(OBJ_EFFECT));
	}
}

void CBossStage::Render(HDC hDC)
{
	if (!m_bFirst)
	{
		HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Boss_Room");

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
	else
	{
		HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Boss_CutScene");

		BitBlt(hDC,
			0,
			0,
			WINCX, WINCY,
			hMemDC,
			0, 0,
			SRCCOPY);
	}
}

void CBossStage::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), Safe_Delete<CObj*>);
	m_vecTile.clear();
}
