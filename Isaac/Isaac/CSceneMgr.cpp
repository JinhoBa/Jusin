#include "pch.h"
#include "CSceneMgr.h"
#include "CMenu.h"
#include "CTutorial.h"
#include "CStage1.h"

CSceneMgr* CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr()
	: m_pScene(nullptr), m_eCurScene(SC_MENU), m_ePreScene(SC_END)
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
		Safe_Delete(m_pScene);

		switch (m_eCurScene)
		{
		case CSceneMgr::SC_MENU:
			m_pScene = new CMenu;
			break;

		case CSceneMgr::SC_TUTORIAL:
			m_pScene = new CTutorial;
			break;

		case CSceneMgr::SC_STAGE1:
			m_pScene = new CStage1;
			break;
		case CSceneMgr::SC_END:
			break;
		}
		m_pScene->Initialize();

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
