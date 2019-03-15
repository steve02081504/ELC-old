//elc-test-build.cpp
#include <stdio.h> 
#include <stdlib.h>
#define c(i,o) puts("build " #o);\
	system("c++ -std=c++2a -c \"" #i "\" -o \"" #o "\" -D__DEBUG__ -g -Wall -I ../forinclude");\
	f=fopen(#o,"r");\
	if(f)fclose(f);else{system("pause");return 0;}
int main(){
	system("chcp 65001 & cls");
	FILE*f;
	c(../forinclude/elc/files/core/test.cpp,../forinclude/elc/files/core/test.o)
	c(../forinclude/elc/files/base/test.cpp,../forinclude/elc/files/base/test.o)
	c(../forinclude/elc/files/helpers/test.cpp,../forinclude/elc/files/helpers/test.o)
	c(test.cpp,test.o)
	system("c++ ../forinclude/elc/files/core/test.o \
	../forinclude/elc/files/base/test.o test.o \
	../forinclude/elc/files/helpers/test.o \
	-o elc-test.exe -static-libgcc -static");
	f=fopen("elc-test.exe","r");\
	if(f)fclose(f);else{system("pause");return 0;}
	system("start start-test.bat");
	system("rm -f ../forinclude/elc/files/core/test.o \
	../forinclude/elc/files/base/test.o \
	test.o \
	../forinclude/elc/files/helpers/test.o");
} 
