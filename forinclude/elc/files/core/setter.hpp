//setter.hpp
/*
未完成的elc解释器core文件
由steve02081504与Alex0125设计、编写
转载时请在不对此文件做任何修改的同时注明出处
项目地址：https://github.com/steve02081504/ELC

注意：
	本文件可能使用了cpp20的新支持或语义，而某些编译器可能并没有支持
	同时，此项目并没有完成
*/
class setter:public comn_ptr::compare_interface<setter>{
	//由于elc的gc只回收node，所以comn_ppr足以保证指向的member不被回收
	comn_ppr to;
	[[nodiscard]]comn_ptr get_value(){return to->access();}
public:
	explicit setter()noexcept=default;
	explicit setter(comn_ppr a)noexcept:to(a){}
	explicit setter(comn_ppr::same_ref&&a)noexcept:to(a){}
	explicit setter(setter&a)noexcept:to(a.to){}
	explicit setter(setter&&a)noexcept:to(a.to){}
	~setter()noexcept=default;

	setter&operator=(comn_ptr a){to->set(a);return*this;}
	operator comn_ptr::convert_interface(){return get_value();}
	comn_ptr operator->(){return get_value();}

	[[nodiscard]]explicit operator comn_ppr(){return to;}
	setter&operator=(setter&a){return operator=(a.get_value());}
	setter&operator=(setter&&a){return operator=(a.get_value());}
	
	void to_weak()noexcept{to->to_weak();}
	void un_weak()noexcept{to->un_weak();}
	void to_virtual()noexcept{to->to_virtual();}
	void un_virtual()noexcept{to->un_virtual();}
};
