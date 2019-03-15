#### function_info  
提供于文件[`<elc/helpers>`](./index.md)  
简化某些函数定义的类模板  
````c++
template<class T>
struct function_info{
	static constexpr bool can_call;
	static constexpr bool can_nothrow_call;
	static constexpr bool can_built;
	static constexpr bool can_nothrow_built;
	static constexpr bool can_call_and_can_built=can_call&&can_built;
};
````
