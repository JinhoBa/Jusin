#include "pch.h"
#include "CMonster.h"
#include "CBmpMgr.h"

CMonster::CMonster()
{
}

CMonster::~CMonster()
{
    Release();
}

void CMonster::Initialize()
{

	
}

void CMonster::Late_Initialize()
{

}

int CMonster::Update()
{
    if (m_bDead)
        return DEAD;

    __super::Update_Rect();

    return NOEVENT;
}

int CMonster::Late_Update()
{
    return NOEVENT;
}

void CMonster::Render(HDC hDC)
{
	
}

void CMonster::Release()
{
}

void CMonster::Collision(CObj* _pObj, HITPOINT _tHitPoint)
{
}
