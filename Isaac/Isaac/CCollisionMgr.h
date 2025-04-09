#pragma once
#include "pch.h"
#include "CObj.h"

class CCollisionMgr
{
private:
	CCollisionMgr();
	~CCollisionMgr();
public:
	static CCollisionMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CCollisionMgr;
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
	void	Collision_Obj(list<CObj*> DstList, list<CObj*> SrcList);
	bool	Check_Obj(CObj* pDst, CObj* pSrc, float* pWidth, float* pHeight);

	void	Collision_Tile(list<CObj*> DstList, vector<CObj*> vecSrc);
	bool	Check_Tile(CObj* pDst, CObj* pTile, float* pWidth, float* pHeight);

public:
	static	CCollisionMgr* m_pInstance;
	list<CObj*> m_HitBoxList;
};

