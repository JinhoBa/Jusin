#pragma once
#include "CScene.h"
class CSceneMgr
{
public:
	enum SCENEID { SC_MENU, SC_TUTORIAL, SC_STAGE1, SC_END };

private:
	CSceneMgr();
	~CSceneMgr();

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
	CScene* m_pStage2;

	vector<CScene*> m_vecScene;

	SCENEID m_eCurScene;
	SCENEID m_ePreScene;
};

