//test.cpp
/*
未完成的elc解释器test文件
由steve02081504与Alex0125设计、编写
转载时请在不对此文件做任何修改的同时注明出处
项目地址：https://github.com/steve02081504/ELC

注意：
	本文件可能使用了cpp20的新支持或语义，而某些编译器可能并没有支持
	同时，此项目并没有完成
*/
#include<time.h>
#include <evest.h>
#define STEST_ON
#include <steve.h>
//多文件编译的理由：
//1.检验是否符合纯头文件库定义
//2.强迫自己在编译时放松一下
#include<elc/all>
namespace base_test{void test();}
namespace core_test{void test();}
namespace helper_test{void test();}
namespace shit_test{
	void test(){
		stest_entryevent("shit test");
		using namespace elc;
		{
			comn_ptr a=&nil,b=&fail;
			stest_accert(a==nullptr);
			stest_accert(nullptr==b);
			stest_accert(a!=b);
		}
		stest_puts("狗屎特性测试结束，一切ok");
		stest_exitevent();
	}
}
int ste::stst(){
	srand(time(0));
	shit_test::test();
	base_test::test();
	core_test::test();
	helper_test::test();
	ret 0;
}
