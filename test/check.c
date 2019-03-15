//elc-test-build.cpp
#include <stdio.h> 
#include <stdlib.h>
#define c(i) puts("check " #i);\
	system("c++ -std=c++2a -c \"" #i "\" -fsyntax-only -D__DEBUG__ -g -Wall -I ../forinclude");
int main(){
	system("chcp 65001 & cls");
	c(../forinclude/elc/files/core/test.cpp)
	c(../forinclude/elc/files/base/test.cpp)
	c(../forinclude/elc/files/helpers/test.cpp)
	c(test.cpp)
	system("pause");
} 
