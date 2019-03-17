//ref_setter.hpp
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
class [[nodiscard]] ref_setter:non_copyable,non_moveable{
	static void default_setter(comn_ppr*beset,comn_ppr value)noexcept{*beset=value;}
	void(*func)(comn_ppr*,comn_ppr)often_noexcept; 
	comn_ppr*to;
public:
	explicit ref_setter(i_know_what_i_do_t,ref_setter&&a)noexcept:func(a.func),to(a.to){}
	explicit ref_setter(i_know_what_i_do_t,comn_ppr*a,void(*b)(comn_ppr*,comn_ppr)=&default_setter)noexcept:func(b),to(a){}
	~ref_setter()noexcept=default;
	void operator=(comn_ppr a)often_noexcept{func(to,a);}
};
