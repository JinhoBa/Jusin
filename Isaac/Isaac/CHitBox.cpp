#include "pch.h"
#include "CHitBox.h"

CHitBox::CHitBox()
{
}

CHitBox::~CHitBox()
{
    Release();
}

void CHitBox::Initialize()
{
}

void CHitBox::Late_Initialize()
{
}

int CHitBox::Update()
{
    return NOEVENT;
}

int CHitBox::Late_Update()
{
    return NOEVENT;
}

void CHitBox::Render(HDC hDC)
{
}

void CHitBox::Release()
{
}

void CHitBox::Collision(CObj* _pObj, HITPOINT _tHitPoint)
{

}
