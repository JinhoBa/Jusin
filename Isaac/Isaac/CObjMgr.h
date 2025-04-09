#pragma once
#include "CObj.h"

class CObjMgr
{
private:
	CObjMgr();
	CObjMgr(const CObjMgr& rCObjManager) = delete;
	CObjMgr& operator=(CObj& rCObjManager) = delete;
	~CObjMgr();


public:
	CObj* Get_Player() { return m_ObjList[OBJ_PLAYER].front(); }
	CObj* Get_Target(OBJID _eID, CObj* _pObj);
	list<CObj*> Get_ObjList(OBJID _eID) { return m_ObjList[_eID]; }

	void	Add_CObj(OBJID _eID, CObj* _pObj);
	void	Delete_Obj(OBJID _eId);
public:
	void Update();
	void Late_Update();
	void Render(HDC _hDC);
	void Release();
	void Erase_ObjList(OBJID _eObjID)
	{
		m_ObjList[OBJ_ITEM].clear();
		m_ObjList[OBJ_DOOR].clear();
	}

public:
	static CObjMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CObjMgr;
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

private:
	list<CObj*> m_ObjList[OBJ_END];
	static CObjMgr* m_pInstance;
};

