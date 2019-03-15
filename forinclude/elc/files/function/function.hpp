//function.hpp
/*
未完成的elc解释器function文件
由steve02081504与Alex0125设计、编写
转载时请在不对此文件做任何修改的同时注明出处
项目地址：https://github.com/steve02081504/ELC

注意：
	本文件可能使用了cpp20的新支持或语义，而某些编译器可能并没有支持
	同时，此项目并没有完成
*/
//just for elc func
using elc::core::function_info;
class function{
	struct base_can_call:ref_able<base_can_call>{
		constexpr base_can_call()noexcept=default;
		constexpr base_can_call(special_init_t)noexcept:ref_able<base_can_call>(never_ref_num_zero){}
		[[nodiscard]]virtual setter call(safe_ptr)=0;
		virtual ~base_can_call()=0;
		void ref_num_is_zero()noexcept{this->~base_can_call();memory::free(this);}
		[[nodiscard]]virtual comn_ptr make_node_from_this()=0;
	};
	template<typename T>
	struct can_call final:base_can_call{
		typename function_info<T>::data_type data;
		can_call(typename function_info<T>::built_type a)noexcept(function_info<T>::can_nothrow_built){function_info<T>::build_up(::std::forward<function_info<T>::built_type>(a),data);}
		~can_call()noexcept(function_info<T>::can_nothrow_destruct)override{data.inactivation();}
		[[nodiscard]]setter call(safe_ptr a)noexcept(function_info<T>::can_nothrow_call)final override
		{return setter(function_info<T>::call(*data.get(),a));}
		[[nodiscard]]comn_ptr make_node_from_this()noexcept_as(make_node_by_function(*::std::declval<can_call>().data.get()))override{
			return core::make_node_by_function(*data.get());
		}
	};
	struct elc_call_t final:base_can_call{
		safe_ptr to;
		elc_call_t(comn_ptr a)noexcept:to(a){}
		~elc_call_t()noexcept override=default;
		[[nodiscard]]setter call(safe_ptr a)override{return setter(eval(cons(to,a)));}
		[[nodiscard]]comn_ptr make_node_from_this()noexcept override{return to;}
	};
	struct default_value_t final:base_can_call{
		constexpr default_value_t()noexcept:base_can_call(special_init){}
		~default_value_t()noexcept override=default;
		setter call(safe_ptr a)override{return setter(car(a));}
		comn_ptr make_node_from_this()noexcept override{return&nil;}
	};
	inline static default_value_t default_value;

	comn_p_t<base_can_call>to=&default_value;
public:
	function()noexcept{}
	~function()=default;
	function(const function&a)noexcept:to(a.to){}
	function(function&&a)noexcept:to(a.to){}

	void swap(function&a)noexcept{to.swap(a.to);}
	function&operator=(const function&a)&noexcept{to=a.to;return*this;}
	function&operator=(function&&a)&noexcept{swap(a);return*this;}
	function&operator=(comn_ptr a)&noexcept{
		to=new(memory::alloc<elc_call_t>())elc_call_t(a);
		return*this;
	}
	template<class T,enable_if(function_info<T>::can_call_and_can_built)>
	function&operator=(T&&a)&
	noexcept(function_info<T>::can_nothrow_built){
		to=::new(memory::alloc<can_call<T>>())can_call<T>(::std::forward<T>(a));
		return*this;
	}
	function&operator=(::std::nullptr_t)&noexcept{to=&default_value;return*this;}
	template<class...args>
	setter operator()(args&&...rest)const{return setter(to->call(list(::std::forward<args>(rest)...)));}
	setter call(safe_ptr a)const{return setter(to->call(to_tmp(a)));}

	template<class T,enable_if(::std::is_assignable_v<function,T>)>
	function(T&&a)noexcept(::std::is_nothrow_assignable_v<function,T>):function()
	{operator=(a);}

	[[nodiscard]]comn_ptr make_node_from_this()const{return to->make_node_from_this();}

	[[nodiscard]]explicit operator bool()const noexcept{return to==&default_value;}
};
inline function::base_can_call::~base_can_call(){}
inline void swap(function&a,function&b)noexcept{a.swap(b);}

[[nodiscard]]inline bool operator==(const function&f,::std::nullptr_t)noexcept{return!bool(f);}
[[nodiscard]]inline bool operator==(::std::nullptr_t,const function&f)noexcept{return!bool(f);}
[[nodiscard]]inline bool operator!=(const function&f,::std::nullptr_t)noexcept{return bool(f);}
[[nodiscard]]inline bool operator!=(::std::nullptr_t,const function&f)noexcept{return bool(f);}

BREAK_NAMESPACE
namespace core{
	[[nodiscard]]inline comn_ptr make_node_by_function(function_n::function&a){
		return a.make_node_from_this();
	}
	[[deprecated,nodiscard]]inline comn_ptr make_node_by_function(comn_ptr a){
		return a;
	}
}
INTER_NAMESPACE(function_n)
