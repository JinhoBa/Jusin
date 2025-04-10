#pragma once
#include "CObj.h"

class CTile : public CObj
{
public:
	CTile();
	virtual ~CTile();

public:
	int Get_DrawID() { return m_iDrawID; }
	int Get_Option() { return m_iOption; }

	void Set_DrawID(int _iDrawID) { m_iDrawID = _iDrawID; }
	void Set_OptionID(int _iOptionID) { m_iOption = _iOptionID; }

public:
	void	Initialize() override;
	void	Late_Initialize() override;
	int		Update() override;
	int		Late_Update() override;
	void	Render(HDC hDC) override;
	void	Release() override;


private:
	int m_iDrawID;
	int m_iOption;

	// CObj을(를) 통해 상속됨
	void Collision(CObj* _pObj, HITPOINT _tHitPoint) override;
};

