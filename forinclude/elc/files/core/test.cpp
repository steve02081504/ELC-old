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
#include <evest.h>
#define STEST_ON
#define ST_NOTMAINPART
#include <steve.h>

#include<elc\core>
namespace core_test{
	using namespace elc;
	using namespace elc::core;
	flag a_flag_for_test;
	void set_flag(){a_flag_for_test.set();}
	struct flag_setter{
		~flag_setter(){a_flag_for_test.set();}
		void operator()(){a_flag_for_test.set();}
	};
	void test_desturctor_call_and_make_node_by_function(){
		stest_entryevent("desturctor test");
		a_flag_for_test.unset();
		stest_accert(!a_flag_for_test);
		eval(list(make_node_by_function(set_flag)));
		stest_accert(a_flag_for_test);
		{
			safe_ptr tmp=list(make_node_by_function(flag_setter()));
			stest_accert(a_flag_for_test);
			a_flag_for_test.unset();
			eval(tmp);
			stest_accert(a_flag_for_test);
			a_flag_for_test.unset();
		}
		stest_accert(a_flag_for_test);
		a_flag_for_test.unset();
		{
			safe_ptr a=make_node();
			a->type()=make_node(the_size_type_usually_has);
			destructor_of(a)=make_node_by_function(set_flag);
		}
		stest_accert(a_flag_for_test);
		stest_exitevent();
	}
	void test_ref(){
		stest_entryevent("ref test");
		safe_ptr a=make_node(1),b=make_node(1);
		a->get_ref(rand())=b->arec(rand());
		a->arec(rand())=a;
		stest_accert(b->arec(rand())==a);
		stest_exitevent();
	}
	void test_weak(){
		stest_entryevent("weak test");
		weak_ptr check=&nil;
		safe_ptr a=make_node(1);
		{
			safe_ptr b=make_node(1);
			a->arec(rand()).to_weak();
			check=a->arec(rand())=b;
			stest_accert(!is_nil(check)&&!is_nil(a->arec(0)));
		}
		stest_accert(is_nil(check)&&is_nil(a->arec(0)));
		stest_exitevent();
	}
	void test_gc(){
		stest_entryevent("gc test");
		comn_ptr a=make_node(1);//因为不是safe_ptr所以理应被回收 
		a->arec(rand())=a;//造环
		//（懒得造网，意思一下就行了，反正gc理论上不会有问题） 
		stest_accert(!is_nil(a));
		gc();
		stest_accert(is_nil(a));
		stest_exitevent();
	}
	void test_eval(){
		stest_entryevent("eval test");
		//eval的执行路径有这几个：
		//底层函数调用：test_desturctor_call_and_make_node_by_function里测试过了

		//elc函数调用：elc函数被定义为以t开始、第二个成员为将被设置为参数列表的列表的列表 
		safe_ptr test_func=list(&t,list(),list(make_node_by_function(set_flag)));
		eval(list(test_func));
		//(t () (set_flag))
		
		//elc对象调用：会展开成以对象与参数共同作参数的对对象的call方法所指向的对象的调用 
		a_flag_for_test.unset();
		test_func=make_node();
		test_func->type()=make_node(the_size_type_usually_has);
		call_of(test_func)=make_node_by_function(set_flag);
		eval(list(test_func));
		stest_accert(a_flag_for_test);
		stest_exitevent();
	}
	void test_virtual(){
		a_flag_for_test.unset();
		
		//stest_accert(a_flag_for_test);
	}
	void test(){
		stest_entryevent("core test");
		test_desturctor_call_and_make_node_by_function();
		test_virtual();
		test_weak();
		test_gc();
		test_ref();
		test_eval();
		stest_puts("core测试结束，一切ok");
		stest_exitevent();
	}
}


































