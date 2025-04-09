#pragma once

#include "CObj.h"
#include "CUI.h"

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

		return pObj;
	}

	static CUI* Create_UI()
	{
		CUI* pUI = new T;
		pUI->Initialize();

		return pUI;
	}
};

