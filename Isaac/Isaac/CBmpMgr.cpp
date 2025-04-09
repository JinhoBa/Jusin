#include "pch.h"
#include "CBmpMgr.h"

CBmpMgr* CBmpMgr::pInstance = nullptr;

CBmpMgr::CBmpMgr()
{
	
}

CBmpMgr::~CBmpMgr()
{
	Release();
}

CBmpMgr* CBmpMgr::Get_Instance()
{
	if (!pInstance)
	{
		pInstance = new CBmpMgr;
	}

	return pInstance;
}

void CBmpMgr::Destroy_Instance()
{
	if (pInstance)
	{
		delete pInstance;
		pInstance = nullptr;
	}
}

void CBmpMgr::Insert_Bmp(const TCHAR* _pFilePath, const TCHAR* _pImgKey)
{
	auto iter = find_if(m_mapBit.begin(), m_mapBit.end(), [&](auto& MyPair)->bool
		{return !lstrcmp(_pImgKey, MyPair.first);});

	if (iter == m_mapBit.end())
	{
		CMyBmp* pBmp = new CMyBmp;
		pBmp->Load_Bmp(_pFilePath);

		m_mapBit.insert({ _pImgKey , pBmp });
	}

}

HDC CBmpMgr::Find_Image(const TCHAR* _pImgkey)
{
	auto iter = find_if(m_mapBit.begin(), m_mapBit.end(), [&](auto& MyPair)->bool
		{
			return !lstrcmp(_pImgkey, MyPair.first);
		});

	if (iter == m_mapBit.end())
		return nullptr;

	return iter->second->Get_DC();

}

void CBmpMgr::Release()
{
	for_each(m_mapBit.begin(), m_mapBit.end(), DeleteMap());
	m_mapBit.clear();
}
