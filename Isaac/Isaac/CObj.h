#pragma once
#include "Define.h"
#include "CAbstractFactory.h"
#include "CSceneMgr.h"
class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	const INFO* Get_Info() { return &m_tInfo; }
	const RECT* Get_Rect() { return &m_tRect; }
	const bool Get_Dead() { return m_bDead; }
	const INFO* Get_Collison() { return &m_tCollisionBox; }
	const STAT* Get_Stat() { return &m_tStat; }
	const OBJID Get_ObjID() { return m_eID; }
	const float Get_Damage() { return m_tStat.fAttack; }

	void Set_Info(float _fX, float _fY, float _fCX, float _fCY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
		m_tInfo.fCX = _fCX;
		m_tInfo.fCY = _fCY;
	}
	void Set_posX(float _fX) { m_tInfo.fX += _fX; }
	void Set_posY(float _fY) { m_tInfo.fX += _fY; }
	void Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	void Set_Dead() { m_bDead = true; }
	void Set_Stat(float _fHp, float _fAttack, float _fIntersection, float _fSpeed)
	{ 
		m_tStat.fHp = _fHp;
		m_tStat.fAttack = _fAttack;
		m_tStat.fIntersection = _fIntersection;
		m_fSpeed = _fSpeed;
	}
	void Set_Hp(float _fAttack) { m_tStat.fHp -= _fAttack; }
	void Set_Frame(int _iStart, int _iEnd, int _iMotion)
	{
		m_tFrame.iStart = _iStart;
		m_tFrame.iEnd = _iEnd;
		m_tFrame.iMotion = _iMotion;
	}
	void Set_FramMotion(int _iMotion) { m_tFrame.iMotion = _iMotion; }
	void Set_FrameKey(const TCHAR* _pFrameKey) { m_pFrameKey = _pFrameKey; }
	void Set_CollisionBoxPos(float _fX, float _fY) 
	{
		m_tCollisionBox.fX = _fX;  
		m_tCollisionBox.fY = _fY;  
	}
	void Set_CollisionBoxSize(float _fCX, float _fCY)
	{
		m_tCollisionBox.fCX = _fCX;
		m_tCollisionBox.fCY = _fCY;
	}
	void Set_ObjID(OBJID _eID) { m_eID = _eID; }

	void Collision_Render(HDC hDC);

public:
	virtual void	Initialize()PURE;
	virtual void	Late_Initialize()PURE;
	virtual int		Update()PURE;
	virtual int		Late_Update()PURE;
	virtual void	Render(HDC hDC)PURE;
	virtual void	Release()PURE;
	virtual void	Collision(CObj* _pObj, HITPOINT _tHitPoint)PURE;
public:
	void Set_Target(CObj* _pTarget) { m_pTarget = _pTarget; }

	template<typename T>
	CObj* Create_Bullet(float _fX, float _fY, float _fCX, float _fCY, float _fAngle, float _fHp, float _fAttack, float _fIntersection, float _fSpeed)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Info(_fX, _fY, _fCX, _fCY);
		pObj->Set_Angle(_fAngle);
		pObj->Set_Stat(_fHp, _fAttack, _fIntersection, _fSpeed);
		pObj->Update_Rect();
		
		return pObj;
	}

	template<typename T>
	CObj* Create_Effect(const TCHAR* _pFileKey, float _fX, float _fY, float _fCX, float _fCY, int _iEnd)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Info(_fX, _fY, _fCX, _fCY);
		pObj->Set_FrameKey(_pFileKey);
		pObj->Set_Frame(0, _iEnd, 0);
		pObj->Update_Rect();

		return pObj;
	}
	
	
public:
	void		Update_Rect();
	void		Move_Frame();
	
protected:
	bool		m_bDead;
	float		m_fSpeed;
	float		m_fAngle;
	
	CObj*		m_pTarget;

	INFO		m_tInfo;
	RECT		m_tRect;
	FRAME		m_tFrame;
	INFO		m_tCollisionBox;
	STAT		m_tStat;

	OBJID		m_eID;

	const TCHAR* m_pFrameKey;

};