#pragma once
#include "CScene.h"
class CSceneMgr
{
public:
	enum SCENEID { SC_MENU, SC_TUTORIAL, SC_STAGE1, SC_BOSS, SC_TREASURE, SC_END };

private:
	CSceneMgr();
	~CSceneMgr();

public:
	void Set_SceneState(int _iIndex, int _iState)
	{
		m_vecSceneState[_iIndex] = _iState;
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

