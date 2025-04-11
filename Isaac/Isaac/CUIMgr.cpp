#include "pch.h"
#include "CUIMgr.h"

CUIMgr* CUIMgr::m_pInstance = nullptr;

CUIMgr::CUIMgr()
{
}

CUIMgr::~CUIMgr()
{
	Release();
}

void CUIMgr::Update()
{
	for (size_t i = 0; i < UI_END; i++)
	{
		for (auto iter = m_UIList[i].begin();
			iter != m_UIList[i].end();)
		{
			int Result = (*iter)->Update();
			if (Result == 1)
			{
				Safe_Delete<CUI*>(*iter);
				iter = m_UIList[i].erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}
}

void CUIMgr::Late_Update()
{
	for (size_t i = 0; i < UI_END; i++)
	{
		for (auto iter = m_UIList[i].begin();
			iter != m_UIList[i].end();)
		{
			

			int Result = (*iter)->Late_Update();
			if (Result == 1)
			{
				Safe_Delete<CUI*>(*iter);
				iter = m_UIList[i].erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}
}

void CUIMgr::Render(HDC _hDC)
{
	for (size_t i = 0; i < UI_END; i++)
	{
		for (auto iter = m_UIList[i].begin();
			iter != m_UIList[i].end();++iter)
		{
			(*iter)->Render(_hDC);
		}
	}
}

void CUIMgr::Release()
{
	for (size_t i = 0; i < UI_END; i++)
	{
		for_each(m_UIList[i].begin(), m_UIList[i].end(), Safe_Delete<CUI*>);
		m_UIList[i].clear();
	}
}

void CUIMgr::Add_UI(UIID _eID, CUI* _pUI)
{
	if (0 > _eID || UI_END < _eID || nullptr == _pUI)
		return;

	m_UIList[_eID].push_back(_pUI);
}

void CUIMgr::Delete_UI(UIID _eId)
{
	for (auto& pUI : m_UIList[_eId])
	{
		Safe_Delete<CUI*>(pUI);
	}
	m_UIList[_eId].clear();
}
