//node.hpp
//at namespace elc::raii
/*
未完成的elc解释器raii文件
由steve02081504与Alex0125设计、编写
转载时请在不对此文件做任何修改的同时注明出处
项目地址：https://github.com/steve02081504/ELC

注意：
	本文件可能使用了cpp20的新支持或语义，而某些编译器可能并没有支持
	同时，此项目并没有完成
*/
class node{
	safe_ptr rua;
public:
	template<class T_=T,typename...args,enable_if(::std::is_invocable_v<core::make_node,args...>)>
	node(args&&...rest)noexcept(::std::is_nothrow_invocable_v<core::make_node,args...>):
	rua(core::make_node(::std::forward<args>(rest)...)){}
	~node()noexcept{rua->destroy();}
	comn_ptr operator&()noexcept{return rua;}
	operator core::node&()noexcept{return*rua;}

	using core::setter;
	using core::ref_setter;

	[[nodiscard]]setter type()noexcept{return setter(rua->type());}
	[[nodiscard]]setter arec(eluint a)noexcept{return setter(rua->arec(a));}
	[[nodiscard]]setter nocheck_arec(eluint a)noexcept{return setter(rua->nocheck_arec(a));}

	[[nodiscard]]ref_setter get_ref(eluint a)noexcept{return ref_setter(i_know_what_i_do,rua->get_ref(a));}
	[[nodiscard]]ref_setter get_type_ref()noexcept{return ref_setter(i_know_what_i_do,rua->get_type_ref());}

	void resize(eluint nsize)noexcept{rua->resize(nsize);}
	void data_resize(eluint nsize)noexcept{rua->data_resize(nsize);}
	[[nodiscard]]byte*get_data()noexcept{return rua->get_data();}
	template<class T>
	[[nodiscard]]inline T&get_data_as()noexcept{return data_cast<T>(get_data());}
	[[nodiscard]]eluint get_size()noexcept{return rua->get_size();}
	[[nodiscard]]eluint get_data_size()noexcept{return rua->get_data_size();}

	void destory()noexcept{rua->destory();}
}
