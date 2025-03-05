#include <iostream>
#include "String.h"
using namespace std;

int main()
{
	String s1 = "Lamin";;
	String s2;
	String s3;
	String s4;

	s2 = "Yamal";
	s3 = (s1 + "df");
	cout << s1.Get_String() << endl;
	cout << s2.Get_String() << endl;
	cout << s3.Get_String() << endl;
	
	/*if (s2 == s4)
		cout << "일치"<< endl;
	else
		cout << "불일치"<< endl;*/

	return 0;
}