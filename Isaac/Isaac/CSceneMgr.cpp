#include "pch.h"
#include "CSceneMgr.h"
#include "CMenu.h"
#include "CTutorial.h"
#include "CStage1.h"
#include "CObjMgr.h"
#include "CTileMgr.h"

CSceneMgr* CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr()
	: m_pScene(nullptr), m_pTutorial(nullptr), m_pStage1(nullptr), m_eCurScene(SC_MENU), m_ePreScene(SC_END)
{
}

CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Scene_Change(SCENEID eID)
{
	m_eCurScene = eID;

	if (m_eCurScene != m_ePreScene)
	{
		if(m_pScene)
			m_pScene->Release();

		switch (m_eCurScene)
		{
		case CSceneMgr::SC_MENU:
			m_pScene = new CMenu;
			m_pScene->Initialize();
			break;

		case CSceneMgr::SC_TUTORIAL:
			if (!m_pTutorial)
			{
				m_pTutorial = new CTutorial;
				m_pTutorial->Initialize();
			}
			else
			{
				Set_Obj(m_pTutorial);
				Set_Tile(m_pTutorial);
			}
		
			m_pScene = m_pTutorial;
			break;

		case CSceneMgr::SC_STAGE1:
			if (!m_pStage1)
			{
				m_pStage1 = new CStage1;
				m_pStage1->Initialize();
			}
			else
			{
				Set_Obj(m_pStage1);
				Set_Tile(m_pStage1);
			}

			m_pScene = m_pStage1;
			break;
		case CSceneMgr::SC_END:
			break;
		}
		

		m_ePreScene = m_eCurScene;
	}

}

void CSceneMgr::Update()
{
	m_pScene->Update();
}

void CSceneMgr::Late_Update()
{
	m_pScene->Late_Update();
}

void CSceneMgr::Render(HDC hDC)
{
	m_pScene->Render(hDC);
}

void CSceneMgr::Release()
{
	m_pScene->Release();
	Safe_Delete<CScene*>(m_pScene);
}

void CSceneMgr::Set_Obj(CScene* _pScene)
{
	for (auto pObj : _pScene->Get_ObjList(OBJ_ITEM))
		CObjMgr::Get_Instance()->Add_CObj(OBJ_ITEM, pObj);

	for (auto pObj : _pScene->Get_ObjList(OBJ_DOOR))
		CObjMgr::Get_Instance()->Add_CObj(OBJ_DOOR, pObj);
}

void CSceneMgr::Set_Tile(CScene* _pScene)
{
	CTileMgr::Get_Instance()->Set_vecTile(_pScene->Get_VecTile());
}
