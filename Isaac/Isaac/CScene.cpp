#include "pch.h"
#include "CScene.h"
#include "CTileMgr.h"
#include "CObjMgr.h"

CScene::CScene()
{
	m_vecTile.reserve(TILEX * TILEY);
}

CScene::~CScene()
{

}

void CScene::Save_Data()
{
	m_ObjList[0].clear();
	m_ObjList[1].clear();
	Set_ObjList(CObjMgr::Get_Instance()->Get_ObjList(OBJ_ITEM), OBJ_ITEM);
	Set_ObjList(CObjMgr::Get_Instance()->Get_ObjList(OBJ_DOOR), OBJ_DOOR);

	CObjMgr::Get_Instance()->Erase_ObjList(OBJ_ITEM);
	CObjMgr::Get_Instance()->Erase_ObjList(OBJ_DOOR);

	Set_VecTile(CTileMgr::Get_Instance()->Get_vecTile());
	CTileMgr::Get_Instance()->Erase_Tile();
}
