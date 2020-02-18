// ConsoleApplication1.cpp : main project file.

#include "stdafx.h"
#include "stdio.h"
#include "windows.h"

using namespace System;

//comment for to add the branch
//second comment for commit to secind_branch

int main()
{
	//int a = 2;
    Console::WriteLine(L"Hello World");
    
	int(*Function_Check_Dll)();
	HMODULE lib1 = LoadLibrary(L"../../ConsoleApplication1/Debug/ClassLibrary1.dll");
	Function_Check_Dll = (int(*) ()) GetProcAddress(lib1, "CheckFunction");
    
	if (lib1 && Function_Check_Dll)
    {	
		//a = Function_Check_Dll();
		printf("DLL here, beacause 2 + 1 = %d", Function_Check_Dll());
    }
    else
    {
    	printf("Huston, we have a problem!\n");
    }
    
    return 0;
}

