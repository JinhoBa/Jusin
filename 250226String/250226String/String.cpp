#include <iostream>
#include "String.h"

String::String()
{
	memset(&m_szString, 0, sizeof(m_szString));
}

String::String(const char _szString[])
{
	strcpy_s(m_szString, sizeof(m_szString), _szString);
}

String::~String()
{
}

void String::operator=(const char _szString[])
{
	strcpy_s(m_szString, sizeof(m_szString), _szString);	
}

String String::operator+(String& _String)
{
	String Temp;
	strcat_s(Temp.m_szString, m_szString);
	strcat_s(Temp.m_szString, _String.m_szString);

	return Temp;
}

bool String::operator==(String& _String)
{
	if(!strcmp(m_szString, _String.m_szString))
		return true;

	return false;
}
