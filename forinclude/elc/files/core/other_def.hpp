//other_def.hpp
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
//这些是杂项定义
[[nodiscard]]inline comn_ptr list()noexcept{return&nil;}
template<class T,class...args>
[[nodiscard]]inline comn_ptr list(T&&a,args&&...rest)noexcept{
	return cons(a,list(::std::forward<args>(rest)...));
}
[[nodiscard]]inline comn_ptr cons(safe_ptr car,safe_ptr cdr)noexcept{
//	stest_entryevent("cons construct");
	comn_ptr aret=make_node(2,&nil.member);
//	stest_exitevent();
	aret->nocheck_arec(0)=car;
	aret->nocheck_arec(1)=cdr;
	return aret;
}
[[nodiscard]]inline bool is_cons(comn_ptr a){return is_nil(a->type());}
[[nodiscard]]inline setter car(comn_ptr a){return setter(a->arec(0));}
[[nodiscard]]inline setter cdr(comn_ptr a){return setter(a->arec(1));}
/*
type:
	destructor
	call
	eval
*/
//constexpr eluint the_size_type_usually_has=3;
[[nodiscard]]inline setter destructor_of(comn_ptr a){return setter(a->type()->arec(0));}
[[nodiscard]]inline setter call_of(comn_ptr a){return setter(a->type()->arec(1));}
[[nodiscard]]inline setter eval_of(comn_ptr a){return setter(a->type()->arec(2));}


[[nodiscard]]inline bool is_elfunc(comn_ptr a){return is_cons(a)&&is_t(car(a));}
[[nodiscard]]inline bool is_bottom_func(comn_ptr a)noexcept{return is_t(call_of(a));}

inline setter pop(comn_ptr&a){comn_ppr aret(car(a));a=cdr(a);return setter(aret);}
inline void push(comn_ptr&a,comn_ptr b){a=cons(b,a);}

[[nodiscard]]inline bool is_true(comn_ptr a)noexcept{return bool(*a);}
[[nodiscard]]inline bool is_false(comn_ptr a)noexcept{return!is_true(a);}

[[nodiscard]]inline comn_ptr to_tmp(comn_ptr&a){auto b=a;a=&nil;return b;}

//接下来是补充定义
/*
alex<alex-jas-de-brad@qq.com> 2019/1/15 12:22:27
bug?
alex<alex-jas-de-brad@qq.com> 2019/1/15 12:26:18
.....凋,call_setter定义错了.
alex<alex-jas-de-brad@qq.com> 2019/1/15 12:27:37
virtual setter的意义在于让member知道被赋的值,并自己做决定.
原九度凋(steve_green@qq.com)  12:35:27
已经被修好的bug
[图片]如果那样的话make_virtual会让人死掉的
太困难了。。。
alex<alex-jas-de-brad@qq.com>  12:37:00
嘛,也没办法.
不如不优化.
原九度凋(steve_green@qq.com)  12:37:23
[图片]
alex<alex-jas-de-brad@qq.com>  12:37:40
就简单多了对吧?
应该也没人会去un_virtual一个not virtual member.
原九度凋(steve_green@qq.com)  12:38:53
[图片]那样做了也是自作自受？
alex<alex-jas-de-brad@qq.com>  12:39:09
√
原九度凋(steve_green@qq.com)  12:39:53
[图片]
*/
/*
whatever it's type is
virtual node:
	whatever it is
	accesser
	setter
*/
//constexpr eluint the_size_virtual_node_usually_has=3;
[[nodiscard]]inline setter accesser_of_virtual_node(comn_ptr a)noexcept{return setter(a->arec(1));}
[[nodiscard]]inline setter setter_of_virtual_node(comn_ptr a)noexcept{return setter(a->arec(2));}
inline void member::call_setter(comn_ptr to,safe_ptr value){
	value=list(to,value);
	push(value,setter_of_virtual_node(to));
	eval(to_tmp(value)); 
	//即eval(list(setter_of_virtual_node(to),to,value));
	//因为要规定求值顺序所以拆开
}
inline comn_ppr member::call_accesser(comn_ptr to){
	safe_ptr tmp=list(to);
	push(tmp,accesser_of_virtual_node(to));
	return comn_ppr(eval(to_tmp(tmp)));
	//即return comn_ppr(eval(list(accesser_of_virtual_node(to),to)));
	//因为要规定求值顺序所以拆开
}
inline setter default_setter_for_make_virtual(safe_ptr args){
	setter tmp(pop(args)->arec(0));
	tmp=pop(args);
	return setter();
}
inline setter default_accesser_for_make_virtual(safe_ptr args){
	return setter(car(args)->arec(0));
}
inline comn_ptr member::make_virtual(safe_ptr to){
	{
		auto tmp=make_node(the_size_virtual_node_usually_has);
		tmp->arec(0)=to;
		to=tmp;
	}
	accesser_of_virtual_node(to)=make_node_by_function(default_accesser_for_make_virtual);
	setter_of_virtual_node(to)=make_node_by_function(default_setter_for_make_virtual);
	return to;
}

inline void member::gc_method()noexcept{call_gc(*get()->get_crude_value());}
