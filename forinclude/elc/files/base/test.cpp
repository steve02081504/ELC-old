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
//测试实例
#include <evest.h>
#define STEST_ON
#define ST_NOTMAINPART
#include <steve.h>

#include<elc\base>
namespace base_test{
	using namespace elc;
	using namespace elc::base;
	class tester;
	memory::pool_t<tester,2>tester_pool;
	struct tester:safe_ref_able<tester>,weak_ref_able<tester>{
		inline static unsigned func_call_time=0,constructor_call_time=0,destructor_call_time=0,start_using_time=0,use_end_time=0,gc_time=0;
		int x=233;
		void func(){stest_accert(x==233);func_call_time++;}
		tester(){stest_accert(x==233);constructor_call_time++;}
		~tester(){stest_accert(x==233);destructor_call_time++;}
		static void reset(){destructor_call_time=constructor_call_time=gc_time=func_call_time=use_end_time=start_using_time=0;}
	private:
		friend ref_able<tester>;
		void ref_num_is_zero()noexcept{stest_accert(x==233);if(!has_weak_link()){use_end_time++;tester_pool.use_end(this);}}
	
		friend weak_ref_able<tester>;
		void weak_ref_num_is_zero()noexcept{stest_accert(x==233);if(has_link())return;use_end_time++;tester_pool.use_end(this);}
	
		friend safe_ref_able<tester>;
		void gc_method()noexcept{stest_accert(x==233);gc_time++;}
	
		friend memory::pool_t<tester,2>;
	//for pool.
		explicit tester(just_init_flag_t)noexcept:tester(){}//隐式调用ref_able的默认构造函数
		void start_using()noexcept{stest_accert(x==233);stest_now();start_using_time++;}
		bool was_using()noexcept{stest_accert(x==233);return has_link()||has_weak_link();}
	};
	tester x;
}
template<>constexpr base_test::tester*elc::base::array_n::get_fail_p<base_test::tester>()noexcept{return&base_test::x;}
template<>constexpr base_test::tester*elc::base::ptr_n::get_null_p<base_test::tester>()noexcept{return&base_test::x;}
namespace base_test{
	void test_ptr(){
		tester::reset();
		{
			ptr_n::safe_p_t<tester>a=&x;
			ptr_n::comn_p_t<tester>b=&x;
			b->func();//访问测试
			(*a).func();
			{
				ptr_n::comn_p_t<tester>c=a;
				ptr_n::safe_p_t<tester>d=c;
				d=a;
				a=d;
				swap(c,d);//swap测试
				swap(d,c);
				swap(c,b);
				swap(a,d);
				ptr_n::weak_p_t<tester>e=a;
				memory::root_list<tester>.mark_all_can_access();
			}
			stest_now();
		}
		stest_accert(tester::func_call_time==2);
		stest_accert(tester::use_end_time==1);
		stest_accert(tester::gc_time==2);//有两个safe_p 
		tester::reset();
	}
	
	void test_array(){
		tester::reset();
		{//array测试
			array<tester>a(3);
			stest_now();
			a.resize(2);
			stest_accert(tester::destructor_call_time==1);
			a.for_each([](tester&a)noexcept{a.func();});
		}
		stest_accert(tester::func_call_time==2);
		stest_accert(tester::constructor_call_time==3);
		stest_accert(tester::destructor_call_time==3);
		tester::reset();
		{
			circulate_array<tester>a(0);
			stest_now();
			a.resize(2);
			stest_accert(tester::constructor_call_time==2);
			auto b=&a.arec(9);
			b->func();
			a.for_each([](tester&a)noexcept{a.func();});
		}
		stest_accert(tester::func_call_time==3);
		stest_accert(tester::constructor_call_time==2);
		stest_accert(tester::destructor_call_time==2);
		tester::reset();
	}
	
	void test_pool(){
		tester::reset();
		{
			stest_now(); 
			ptr_n::safe_p_t<tester>a=tester_pool.get_new(),b=tester_pool.get_new(),c=tester_pool.get_new(),d=tester_pool.get_new();
			stest_now();
			stest_accert(tester::constructor_call_time==4);
			stest_accert(tester::destructor_call_time==0);
			stest_accert(tester::start_using_time==4);
			a=tester_pool.get_new();
			stest_accert(tester::use_end_time==1);
			stest_accert(tester::constructor_call_time==6);
			stest_accert(tester::start_using_time==5);
			a=b;
			stest_accert(tester::destructor_call_time==0);
			stest_now();
			tester_pool.for_each([](tester&a)noexcept{a.func();});
			stest_accert(tester::func_call_time==3);
			stest_now();
			stest_accert(tester::use_end_time==2);
			stest_now();
		}
		stest_accert(tester::constructor_call_time==6);
		tester_pool.shrink();
		stest_accert(((base_list&)tester_pool).empty());
		stest_accert(tester::destructor_call_time==6);
		tester::reset();
	}
	void test(){
		stestoutoff(); 
		test_ptr();
		test_array();
		test_pool();
		stestouton(); 
		stest_puts("base测试结束，一切ok");
	}
}

