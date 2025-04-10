#pragma once
#include "CItem.h"

class CBox : public CItem
{
public:
	CBox();
	~CBox();
	
public:
	void Initialize() override;
	void Late_Initialize() override;
	int Update() override;
	int Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void Collision(CObj* _pObj, HITPOINT _tHitPoint) override;

public:
	void Set_Open() { m_bOpen = true; }
	bool Get_bOpen() { return m_bOpen; }
	void Drop_Item();
private:
	bool m_bOpen;
};

