#include <iostream>
#include "String.h"
using namespace std;

int main()
{
	String s1;
	String s2;
	String s3;
	String s4;

	s1 = "Lamin";
	s2 = "Yamal";
	s4 = "Yamal";
	s3 = s1 + s2;

	cout << s3.value() << endl;
	if (s2 == s4)
		cout << "일치"<<endl;
	else
		cout << "불일치"<<endl;

	return 0;
}