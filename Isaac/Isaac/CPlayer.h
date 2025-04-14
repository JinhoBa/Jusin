#pragma once
#include "CObj.h"
class CPlayer : public CObj
{
	enum MSTATE {IDLE, ATTACK, HIT, GETITEM, DEATH, MS_END};
public:
	CPlayer();
	virtual ~CPlayer();

public:	
	void	Set_ItemInfo(int _iCoin, int _iBomb, int _iKey)
	{
		m_tItemInfo.iCoin = _iCoin;
		m_tItemInfo.iBomb = _iBomb;
		m_tItemInfo.iKey = _iKey;
	}
	void	Set_BodyFrame(int _iStart, int _iEnd, int _iMotion)
	{
		m_tBodyFrame.iStart = _iStart;
		m_tBodyFrame.iEnd = _iEnd;
		m_tBodyFrame.iMotion = _iMotion;
	}
	
	ITEMINFO* Get_ItemInfo() { return &m_tItemInfo; }
	void Set_SoulHp(float _fDamage) { m_fSoulHp -= _fDamage; }
	float Get_SoulHp() { return m_fSoulHp; }
	
	bool Open_Obj() 
	{
		if (m_tItemInfo.iKey <= 0)
			return false;
		
		--m_tItemInfo.iKey;
		
		return true;
	}

public:
	void	Initialize() override;
	void	Late_Initialize() override;
	int		Update() override;
	int		Late_Update() override;
	void	 Render(HDC hDC) override;
	void	Release() override;
	void	Collision(CObj* _pObj, HITPOINT _tHitPoint) override;
	
private:
	void	Key_Input();

	template<typename T>
	void	Attack(float _fAngle, bool _bX);

	void	Laser_Attack(float _fAgle, bool _bX);

	void	Change_Motion();
	void	Move_BodyFrame();

	bool m_bJump;
	float m_fTime;
	float m_fCoolDown;

	float m_fAttackPos;
	float m_fSoulHp;

	ULONGLONG m_dwTime;
	ULONGLONG m_ChargeTime;
	ULONGLONG m_MotionTime;

	INFO m_tBodyInfo;
	ITEMINFO m_tItemInfo;

	FRAME m_tBodyFrame;

	MSTATE m_eCurState;
	MSTATE m_ePreState;

	vector <bool> m_vecItem;
};

