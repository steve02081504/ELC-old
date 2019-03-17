//other_decl.hpp
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
namespace eval_n{
	inline setter eval(safe_ptr expr);
}
using eval_n::eval;

[[nodiscard]]inline comn_ptr list()noexcept;
template<class T,class...args>
[[nodiscard]]inline comn_ptr list(T&&a,args&&...rest)noexcept;
[[nodiscard]]inline comn_ptr cons(safe_ptr car,safe_ptr cdr)noexcept;
[[nodiscard]]inline bool is_cons(comn_ptr a);
[[nodiscard]]inline setter car(comn_ptr a);
[[nodiscard]]inline setter cdr(comn_ptr a);

constexpr eluint the_size_type_usually_has=3;
[[nodiscard]]inline setter destructor_of(comn_ptr a);
[[nodiscard]]inline setter call_of(comn_ptr a);
[[nodiscard]]inline setter eval_of(comn_ptr a);

[[nodiscard]]inline bool is_elfunc(comn_ptr a);
[[nodiscard]]inline bool is_bottom_func(comn_ptr a)noexcept;

inline setter pop(comn_ptr&a);
inline void push(comn_ptr&a,comn_ptr b);

[[nodiscard]]inline bool is_true(comn_ptr a)noexcept;
[[nodiscard]]inline bool is_false(comn_ptr a)noexcept;

[[nodiscard]]inline comn_ptr to_tmp(comn_ptr&a);

constexpr eluint the_size_virtual_node_usually_has=3;
[[nodiscard]]inline setter accesser_of_virtual_node(comn_ptr a)noexcept;
[[nodiscard]]inline setter setter_of_virtual_node(comn_ptr a)noexcept;
