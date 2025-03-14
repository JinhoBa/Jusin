#include "pch.h"
#include "CObj.h"
#include "Define.h"

CObj::CObj()
{
	m_hDC = NULL;
	m_rc = { 0,0,0,0 };
}

CObj::~CObj()
{
	Release();
}

void CObj::Initialize()
{
	
}

void CObj::Update()
{
}

void CObj::Render()
{
}

void CObj::Release()
{
}
