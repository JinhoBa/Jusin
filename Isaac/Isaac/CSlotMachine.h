#pragma once
#include "CItem.h"

class CSlotMachine : public CItem
{
	enum MachineState{ IDLE, MOVE, STOP, BROKEN ,M_END};
public:
	CSlotMachine();
	~CSlotMachine();

public:
	void	Initialize() override;
	void	Late_Initialize() override;
	int		Update() override;
	int		Late_Update() override;
	void	Render(HDC hDC) override;
	void	Release() override;
	void	Collision(CObj* _pObj, HITPOINT _tHitPoint) override;

private:
	void Drop_Item(int i);

private:
	ULONGLONG m_dwTime;
	MachineState m_eCurState;
	MachineState m_eOldState;
};

