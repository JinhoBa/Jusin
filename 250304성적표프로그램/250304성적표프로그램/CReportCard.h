#pragma once

#include "CStudent.h"

class CReportCard
{
public:
	CReportCard();
	~CReportCard();
public:
	void Initialize();
	void Update();
	void Release();
	void Input();
	void Print();
	void Search();
	void Delete();
	void Sort();
	
	
private:
	CStudent* m_pStudent;
	vector<CStudent*> vecStudent;
};

