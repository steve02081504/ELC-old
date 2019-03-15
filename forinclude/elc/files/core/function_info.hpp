//call_info.hpp
/*
未完成的elc解释器core文件
由steve02081504与Alex0125设计、编写
转载时请在不对此文件做任何修改的同时注明出处
项目地址：https://github.com/steve02081504/ELC

注意：
	本文件可能使用了cpp20的新支持或语义，而某些编译器可能并没有支持
	同时，此项目并没有完成
*/
template<class T_>
struct base_function_info{
	typedef ::std::remove_reference_t<T_> T;
	static constexpr bool can_call=
							::std::is_invocable_r_v<setter,T,safe_ptr>||
							::std::is_invocable_r_v<void,T,safe_ptr>||
							::std::is_invocable_r_v<setter,T>||
							::std::is_invocable_r_v<void,T>;
	static constexpr bool can_nothrow_call=
							::std::is_invocable_r_v<setter,T,safe_ptr>?::std::is_nothrow_invocable_r_v<setter,T,safe_ptr>:(
							::std::is_invocable_r_v<void,T,safe_ptr>?::std::is_nothrow_invocable_r_v<void,T,safe_ptr>:(
							::std::is_invocable_r_v<setter,T>?::std::is_nothrow_invocable_r_v<setter,T>:(
							::std::is_invocable_r_v<void,T>?::std::is_nothrow_invocable_r_v<void,T>:
							0)));
	typedef ::std::conditional_t<::std::is_function_v<T>,T*,
			::std::conditional_t<(::std::is_rvalue_reference_v<T_>&&::std::is_move_constructible_v<T>),T,
			::std::conditional_t<::std::is_copy_constructible_v<T>,T,
			::std::nullptr_t>>>
		base_type;
	static constexpr bool can_destruct=::std::is_destructible_v<base_type>;
	static constexpr bool can_nothrow_destruct=::std::is_nothrow_destructible_v<base_type>;
	static constexpr bool can_built=::std::is_function_v<T>?true:
			(can_destruct&&
			((::std::is_rvalue_reference_v<T_>&&::std::is_move_constructible_v<T>)?
			true:
			::std::is_copy_constructible_v<T>));
	static constexpr bool can_nothrow_built=::std::is_function_v<T>?true:
			(can_built&&
			((::std::is_rvalue_reference_v<T_>&&::std::is_move_constructible_v<T>)?
			::std::is_nothrow_move_constructible_v<T>:
			::std::is_nothrow_copy_constructible_v<T>));

	typedef ::std::conditional_t<::std::is_function_v<T>,const T&,
			::std::conditional_t<(::std::is_rvalue_reference_v<T_>&&::std::is_move_constructible_v<T>),T&&,
			::std::conditional_t<::std::is_copy_constructible_v<T>,const T&,
			::std::nullptr_t>>>
		built_type;

	typedef data_t<base_type>
		data_type;
	static void build_up(built_type a,data_type&b)noexcept(can_nothrow_built){
		if constexpr(::std::is_function_v<T>)
			 b.activation(&a);
		else b.activation(::std::forward<built_type>(a));
	}
	static setter call(base_type&func,[[maybe_unused]]safe_ptr args)noexcept(can_nothrow_call){
		if constexpr(::std::is_invocable_r_v<setter,T,safe_ptr>)
			return static_cast<setter>(func(args));
		else if constexpr(::std::is_invocable_r_v<void,T,safe_ptr>){
			func(args);
			return setter();
		}else if constexpr(::std::is_invocable_r_v<setter,T>){
			return static_cast<setter>(func());
		}else if constexpr(::std::is_invocable_r_v<void,T>){
			func();
			return setter();
		} 
	}
	static constexpr bool can_call_and_can_built=can_call&&can_built;
};
template<class T>
using function_info=base_function_info<::std::remove_cv_t<T>>;