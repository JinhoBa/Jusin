#pragma once
#include "CMyBmp.h"
#include "Define.h"

class CBmpMgr
{
private:
	CBmpMgr();
	~CBmpMgr();
public:
	static CBmpMgr* Get_Instance();
	static void Destroy_Instance();

public:
	void Insert_Bmp(const TCHAR* _pFilePath, const TCHAR* _pImgKey);
	HDC Find_Image(const TCHAR* _pImgkey);
	void Release();

public:
	static CBmpMgr* pInstance;
	map<const TCHAR*, CMyBmp*> m_mapBit;
};



