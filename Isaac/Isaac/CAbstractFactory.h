#pragma once

#include "CObj.h"
#include "CUI.h"
#include "CScene.h"
#include "CImage.h"

template<typename T>
class CAbstractFactory
{
public:
	CAbstractFactory() {}
	~CAbstractFactory() {}
public:
	static CObj* Create_Obj(float _fX, float _fY, float _fCX, float _fCY)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Info(_fX, _fY, _fCX, _fCY);
		pObj->Late_Initialize();

		return pObj;
	}


	static CUI* Create_UI(float _fX, float _fY, float _fCX, float _fCY)
	{
		CUI* pUI = new T;
		pUI->Set_Info(_fX, _fY, _fCX, _fCY);
		pUI->Initialize();

		return pUI;
	}

	static CScene* Create_Scene()
	{
		CScene* pScene = new T;
		pScene->Initialize();

		return pScene;
	}

};

