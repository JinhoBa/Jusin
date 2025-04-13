#pragma once
#include "Define.h"
class CObj;

class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual void	Initialize()PURE;
	virtual	void	Update()PURE;
	virtual void	Late_Update()PURE;
	virtual void	Render(HDC hDC)PURE;
	virtual void	Release()PURE;

public:
	void Save_Data();
	void Set_ObjList(list<CObj*> _ObjList, OBJID _eObjID)
	{
		int i(0);

		if (OBJ_DOOR == _eObjID)
			i = 1;

		for (auto iter = _ObjList.begin();
			iter != _ObjList.end();++iter)
		{
			if (_ObjList.empty())
				break;

			m_ObjList[i].push_back((*iter));
		}
		
	}
	void Set_VecTile(vector<CObj*> _vecTile)
	{
		m_vecTile = _vecTile;
	}

	list<CObj*> Get_ObjList(OBJID _eObjID)
	{
		int i(0);

		if(OBJ_DOOR == _eObjID)
			i = 1;

		return m_ObjList[i];
	}
	vector<CObj*> Get_VecTile()
	{
		return m_vecTile;
	}
	bool Get_bSave() { return m_bSave; }

	void Clear_Data()
	{
		m_ObjList[0].clear();
		m_ObjList[1].clear();
		m_vecTile.clear();
	}

protected:
	list<CObj*>		m_ObjList[2];
	vector<CObj*>	m_vecTile;
	bool			m_bSave;
	bool			m_bDoorOpen;
	int				m_iChennel;
};

