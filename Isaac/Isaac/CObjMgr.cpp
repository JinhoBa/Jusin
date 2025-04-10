#include "pch.h"
#include "CObjMgr.h"

CObjMgr* CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{

}

CObjMgr::~CObjMgr()
{
	Release();
}


CObj* CObjMgr::Get_Target(OBJID _eID, CObj* _pObj)
{
	if (m_ObjList[_eID].empty())
		return nullptr;

	float fDistance(0.f);
	CObj* pTarget = nullptr;

	for (auto& pObj : m_ObjList[_eID])
	{
		if (pObj->Get_Dead())
			continue;

		float fWidth = fabsf(_pObj->Get_Info()->fX + pObj->Get_Info()->fX);
		float fHeight = fabsf(_pObj->Get_Info()->fY + pObj->Get_Info()->fY);

		float fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		if (!pTarget || fDistance > fDiagonal)
		{
			fDistance = fDiagonal;
			pTarget = pObj;
		}

	}

	return pTarget;

}

void CObjMgr::Add_CObj(OBJID _eID, CObj* _pObj)
{
	if (0 > _eID || OBJ_END < _eID || nullptr == _pObj)
		return;

	_pObj->Set_ObjID(_eID);

	m_ObjList[_eID].push_back(_pObj);
}

void CObjMgr::Delete_Obj(OBJID _eId)
{
	for (auto& pObj : m_ObjList[_eId])
	{
		Safe_Delete<CObj*>(pObj);
	}
	m_ObjList[_eId].clear();
}

void CObjMgr::Update()
{
	for (size_t i = 0; i < OBJ_END; i++)
	{
		for (auto iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end();)
		{
			

			int Result = (*iter)->Update();
			if (m_ObjList[i].empty())
				break;
			if (Result == 1)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}
}

void CObjMgr::Late_Update()
{
	for (size_t i = 0; i < OBJ_END; i++)
	{
		for (auto iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end();)
		{

			int Result = (*iter)->Late_Update();

			if (m_ObjList[i].empty())
				break;

			if (Result == 1)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
			{
				++iter;
			}

		}
	}
}

void CObjMgr::Render(HDC _hDC)
{
	for (size_t i = 0; i < OBJ_END; i++)
	{
		for (auto iter = m_ObjList[i].begin();iter != m_ObjList[i].end();++iter)
		{
			if (m_ObjList[i].empty())
				break;
			(*iter)->Render(_hDC);
		}
	}
}

void CObjMgr::Release()
{
	for (size_t i = 0; i < OBJ_END; i++)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}
}
