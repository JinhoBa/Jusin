#pragma once
#include "CUI.h"
class CUIMgr
{
private:
	CUIMgr();
	~CUIMgr();

public:
	void Update();
	void Late_Update();
	void Render(HDC _hDC);
	void Release();

public:
	static CUIMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CUIMgr;
		}

		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	void	Add_UI(UIID _eID, CUI* _pObj);
	void	Delete_UI(UIID _eId);

private:
	list<CUI*> m_UIList[UI_END];
	static CUIMgr* m_pInstance;
	
};




