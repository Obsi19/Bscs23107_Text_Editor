#include "TextEditor.h"
#include<iostream>
#include<conio.h>
#include<time.h>

using namespace std;

void ResetKeys(int& K1, int& K2)
{
	K1 = -1;
	K2 = -1;
}


int main()
{
	TextEditor T;
	T.ControlEditor();
	return 0;
}

