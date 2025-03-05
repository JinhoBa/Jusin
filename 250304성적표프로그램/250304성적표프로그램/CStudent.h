#pragma once
#include "Define.h"

class CStudent
{
public:
	CStudent();
	~CStudent();
public:
	void Set_Info(string _sName, float _iKorean, float _iEnglish, float _iMath);
	string Get_Name() { return m_tInfo.sName; }
	const float Get_Korean() { return m_tInfo.iKorean; }
	const float Get_English() { return m_tInfo.iEnglish; }
	const float Get_Math() { return m_tInfo.iMath; }
	const float Get_Total() { return m_tInfo.iTotal; }
	const float Get_Average() { return m_tInfo.iAverage; }
	bool operator<(CStudent& rStudent) { return this->Get_Average() > rStudent.Get_Average(); }
private:
	INFO m_tInfo;
};

