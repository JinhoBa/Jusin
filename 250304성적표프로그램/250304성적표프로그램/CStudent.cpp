#include "pch.h"
#include "CStudent.h"

CStudent::CStudent()
{
	m_tInfo.sName = "";
	m_tInfo.iKorean = 0.f;
	m_tInfo.iEnglish = 0.f;
	m_tInfo.iMath = 0.f;
	m_tInfo.iTotal = 0.f;
	m_tInfo.iAverage = 0.f;
}

CStudent::~CStudent()
{
	
}

void CStudent::Set_Info(string _sName, float _iKorean, float _iEnglish, float _iMath)
{
	m_tInfo.sName = _sName;
	m_tInfo.iKorean = _iKorean;
	m_tInfo.iEnglish = _iEnglish;
	m_tInfo.iMath = _iMath;
	m_tInfo.iTotal = _iKorean + _iEnglish +_iMath;
	m_tInfo.iAverage = m_tInfo.iTotal / 3.f;
}
