#include <iostream>
#include "String.h"

String::String()
	: m_pString(nullptr), m_iSize(0)
{
}

String::String(const char* _pString)
{
	m_iSize = (int)strlen(_pString);
	m_pString = new char[m_iSize + 1];
	strcpy_s(m_pString, m_iSize + 1, _pString);
}

String::String(const String& rhs)
	: m_iSize(rhs.m_iSize)
{
	m_pString = new char[m_iSize + 1];
	strcpy_s(m_pString, m_iSize + 1, rhs.m_pString);
}

String::~String()
{
	Release();
}

const char* String::Get_String()
{
	if (m_pString)
		return m_pString;
	return "";
}

void String::Release()
{
	Safe_Delete_Array(m_pString);
}

String& String::operator=(const char* _pString)
{
	Release();
	m_iSize = (int)strlen(_pString);
	m_pString = new char[m_iSize + 1];
	strcpy_s(m_pString, m_iSize + 1, _pString);

	return *this;
}

String& String::operator=(const String& rhs)
{
	Release();
	m_iSize = (int)strlen(rhs.m_pString);
	m_pString = new char[m_iSize + 1];
	strcpy_s(m_pString, m_iSize+1, rhs.m_pString);

	return *this;
}

String String::operator+(const char* _pString)
{
	int iLength = m_iSize + (int)strlen(_pString);
	char* pString = new char[iLength + 1];
	strcpy_s(pString, iLength + 1, m_pString);
	strcat_s(pString, iLength+1, _pString);

	String Result(pString);
	Safe_Delete_Array(pString);

	return Result;
}

String String::operator+(String& rString)
{
	int iLength = m_iSize + (int)strlen(rString.m_pString);
	char* pString = new char[iLength + 1];
	strcpy_s(pString, iLength + 1, m_pString);
	strcat_s(pString, iLength+1, rString.m_pString);

	String Result(pString);
	Safe_Delete_Array(pString);

	return Result;
}



