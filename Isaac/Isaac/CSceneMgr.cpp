#include "pch.h"
#include "CSceneMgr.h"
#include "CMenu.h"
#include "CTutorial.h"
#include "CStage1.h"
#include "CObjMgr.h"
#include "CTileMgr.h"
#include "CAbstractFactory.h"
#include "CUIMgr.h"
#include "CBossStage.h"
#include "CSoundMgr.h"
#include "CTreasureRoom.h"

CSceneMgr* CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr()
	: m_pScene(nullptr), m_pTutorial(nullptr), m_pStage1(nullptr), m_pTreasureRoom(nullptr), m_eCurScene(SC_MENU), m_ePreScene(SC_END)
{
	m_vecScene.assign(10, nullptr);
	m_vecSceneState.assign(12, 0);
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
		
		
		if(m_pScene && CSceneMgr::SC_MENU != m_eCurScene)
		{
			m_pScene->Save_Data();
			CSoundMgr::Get_Instance()->StopAll();
		}
		if(CSceneMgr::SC_MENU != m_ePreScene)
			CSoundMgr::Get_Instance()->StopAll();

		switch (m_eCurScene)
		{
		case CSceneMgr::SC_MENU:
			//CSoundMgr::Get_Instance()->PlayBGM(L"Danny Baranowsky - The Binding of Isaac - 01 Those Responsible.mp3", 0.3f);
			if(!m_vecScene[SC_MENU])
				m_vecScene[SC_MENU] = CAbstractFactory<CMenu>::Create_Scene();
			else
			{
				for (int i = 1; i < m_vecScene.size(); ++i)
				{
					if (!m_vecScene[i])
						continue;

					if (m_vecScene[i] == m_pScene)
					{
						Safe_Delete<CScene*>(m_vecScene[i]);
						CObjMgr::Get_Instance()->Release();
						CTileMgr::Get_Instance()->Release();
					}
					else if (m_vecScene[i]->Get_bSave())
					{
						Safe_Delete<CScene*>(m_vecScene[i]);
					}
				}
				CUIMgr::Get_Instance()->Release();
				CUIMgr::Get_Instance()->Delete_UI(UI_BAR);
				m_vecScene[SC_MENU]->Initialize();
			}

			m_pScene = m_vecScene[SC_MENU];
			break;

		case CSceneMgr::SC_TUTORIAL:
			CSoundMgr::Get_Instance()->PlayBGM(L"Danny Baranowsky - The Binding of Isaac - 05 Sacrificial.mp3", 0.3f);
			if (!m_vecScene[SC_TUTORIAL])
				m_vecScene[SC_TUTORIAL] = CAbstractFactory<CTutorial>::Create_Scene();
			else
			{
				CSceneMgr::Get_Instance()->Set_SceneState(7, 3);
				CSceneMgr::Get_Instance()->Set_SceneState(10, 2);
				Set_Data(m_vecScene[SC_TUTORIAL]);
			}

			m_pScene = m_vecScene[SC_TUTORIAL];
			break;

		case CSceneMgr::SC_STAGE1:
			CSoundMgr::Get_Instance()->PlayBGM(L"Danny Baranowsky - The Binding of Isaac - 05 Sacrificial.mp3", 0.3f);
			if (!m_vecScene[SC_STAGE1])
				m_vecScene[SC_STAGE1] = CAbstractFactory<CStage1>::Create_Scene();
			else
			{
				CSceneMgr::Get_Instance()->Set_SceneState(10, 3);
				CSceneMgr::Get_Instance()->Set_SceneState(11, 8);
				Set_Data(m_vecScene[SC_STAGE1]);
			}

			m_pScene = m_vecScene[SC_STAGE1];
			break;

		case CSceneMgr::SC_BOSS:
			if (!m_vecScene[SC_BOSS])
				m_vecScene[SC_BOSS] = CAbstractFactory<CBossStage>::Create_Scene();
			else
				Set_Data(m_vecScene[SC_BOSS]);

			m_pScene = m_vecScene[SC_BOSS];
			break;

		case CSceneMgr::SC_TREASURE:
			if (!m_vecScene[SC_TREASURE])
				m_vecScene[SC_TREASURE] = CAbstractFactory<CTreasureRoom>::Create_Scene();
			else
				Set_Data(m_vecScene[SC_TREASURE]);

			m_pScene = m_vecScene[SC_TREASURE];
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
	Safe_Delete<CScene*>(m_vecScene[0]);

	for(int i = 1; i < m_vecScene.size(); ++i)
	{
		if (!m_vecScene[i])
			continue;

		if (m_vecScene[i] == m_pScene)
		{
			Safe_Delete<CScene*>(m_vecScene[i]);
			CObjMgr::Get_Instance()->Release();
			CTileMgr::Get_Instance()->Release();
		}
		else if(m_vecScene[i]->Get_bSave())
		{
			Safe_Delete<CScene*>(m_vecScene[i]);
		}

	}
	CUIMgr::Get_Instance()->Release();
}


void CSceneMgr::Set_Data(CScene* _pScene)
{
	for (auto pObj : _pScene->Get_ObjList(OBJ_ITEM))
		CObjMgr::Get_Instance()->Add_CObj(OBJ_ITEM, pObj);

	for (auto pObj : _pScene->Get_ObjList(OBJ_DOOR))
		CObjMgr::Get_Instance()->Add_CObj(OBJ_DOOR, pObj);

	CTileMgr::Get_Instance()->Set_vecTile(_pScene->Get_VecTile());

	_pScene->Clear_Data();
	
}

