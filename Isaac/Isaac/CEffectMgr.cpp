#include "pch.h"
#include "CEffectMgr.h"
#include "CBmpMgr.h"
#include "CEffect.h"

CEffectMgr* CEffectMgr::m_pInstance = nullptr;

CEffectMgr::CEffectMgr()
{
}

CEffectMgr::~CEffectMgr()
{
	Release();
}

void CEffectMgr::Initialize()
{
	
}

void CEffectMgr::Update()
{
}

void CEffectMgr::Late_Update()
{
}

void CEffectMgr::Render(HDC hDC)
{
}

void CEffectMgr::Release()
{
}

void CEffectMgr::Add_Effect(TCHAR* _pFileKey, float _fX, float _fY, float _fCX, float _fCY)
{
	CObj* pObj = new CEffect;
	pObj->Initialize();
	pObj->Set_Info(_fX, _fY, _fCX, _fCY);
	pObj->Set_FrameKey(_pFileKey);

	m_EffectList.push_back(pObj);
}
