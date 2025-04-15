#pragma once
#include "CScene.h"
class CSceneMgr
{
public:
	enum SCENEID { SC_MENU, SC_TUTORIAL, SC_BOSS, SC_STAGE1, SC_STAGE2, SC_TREASURE, SC_STOREROOM, SC_END };

private:
	CSceneMgr();
	~CSceneMgr();

public:
	void Set_SceneState(SCENEID _eID, int _iState, int _iValue)
	{
		int iIndex(0);
		switch (_eID)
		{
		case CSceneMgr::SC_MENU:
			
			break;
		case CSceneMgr::SC_TUTORIAL:
			iIndex = 7;
			break;
		case CSceneMgr::SC_BOSS:
			iIndex = 9;
			break;
		
		case CSceneMgr::SC_STAGE1:
			iIndex = 10;
			break;
		case CSceneMgr::SC_STAGE2:
			iIndex = 4;
			break;
		case CSceneMgr::SC_TREASURE:
			iIndex = 11;
			break;
		case CSceneMgr::SC_STOREROOM:
			iIndex = 6;
			break;
		case CSceneMgr::SC_END:
			break;
		default:
			break;
		}
		m_vecSceneState[iIndex] = _iState;
	}
	void Set_SceneState(SCENEID _eID, int _iValue)
	{
		int iIndex(0);
		switch (_eID)
		{
		case CSceneMgr::SC_MENU:

			break;
		case CSceneMgr::SC_TUTORIAL:
			iIndex = 7;
			break;
		case CSceneMgr::SC_BOSS:
			iIndex = 9;
			break;
		case CSceneMgr::SC_STAGE1:
			iIndex = 10;
			break;
		case CSceneMgr::SC_STAGE2:
			iIndex = 4;
			break;
		case CSceneMgr::SC_TREASURE:
			iIndex = 11;
			break;
		case CSceneMgr::SC_STOREROOM:
			iIndex = 6;
			break;
		case CSceneMgr::SC_END:
			break;
		default:
			break;
		}
		m_vecSceneState[iIndex] += _iValue;
	}
	vector<int> Get_vecSceneState() { return m_vecSceneState; }

public:
	void		Scene_Change(SCENEID eID);
	void		Update();
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release();

public:
	static CSceneMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CSceneMgr;
		}

		return m_pInstance;
	}

	static void	Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	void	Set_Data(CScene* _pScene);

public:
	static CSceneMgr* m_pInstance;

	CScene* m_pScene;
	CScene* m_pTutorial;
	CScene* m_pStage1;
	CScene* m_pTreasureRoom;

	vector<CScene*> m_vecScene;
	vector<int> m_vecSceneState;

	SCENEID m_eCurScene;
	SCENEID m_ePreScene;
};

