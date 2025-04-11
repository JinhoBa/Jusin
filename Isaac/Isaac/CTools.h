#pragma once
#include "CObj.h"

class CTools
{
private:
	CTools() {}
	~CTools() {}

public:
	static float Get_Angle(CObj* _pTarget, INFO* _pInfo)
	{
		float fAngle(0.f);

		float	fWidth = _pTarget->Get_Info()->fX - _pInfo->fX;
		float	fHeight = _pTarget->Get_Info()->fY - _pInfo->fY;

		float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		float	fRadian = acosf(fWidth / fDiagonal);

		fAngle = fRadian * (180.f / PI);

		if (_pTarget->Get_Info()->fY > _pInfo->fY)
			fAngle *= -1.f;

		return fAngle;
	}
	static float Get_Distance(CObj* _pTarget, INFO* _pInfo)
	{

		float	fWidth = _pTarget->Get_Info()->fX - _pInfo->fX;
		float	fHeight = _pTarget->Get_Info()->fY - _pInfo->fY;

		float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		return 	fDiagonal;
	}
};

