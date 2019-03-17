//jmp_t.hpp
//at namespace elc::core
/*
未完成的elc解释器core文件
由steve02081504与Alex0125设计、编写
转载时请在不对此文件做任何修改的同时注明出处
项目地址：https://github.com/steve02081504/ELC

注意：
	本文件可能使用了cpp20的新支持或语义，而某些编译器可能并没有支持
	同时，此项目并没有完成
*/
struct jmp_t:exception_n::jmp_error,non_copyable, non_moveable{
	safe_ptr to;
	flag delaying;
	template<class T,bool=::std::is_constructible_v<safe_ptr,T>>
	jmp_t(T&&a)noexcept(::std::is_nothrow_constructible_v<safe_ptr,T>):to(a){}
	void delay()noexcept{delaying.set();}
	void undelay()noexcept{delaying.unset();}
};
[[noreturn]] inline void jmp(comn_ptr to){throw jmp_t(to);}
inline setter delay_jmp(comn_ptr to_eval){
	try{return setter(eval(to_eval));}
	catch(jmp_t&a){a.delay();throw;} 
}
