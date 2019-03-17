//defs.hpp
/*
未完成的elc解释器core文件
由steve02081504与Alex0125设计、编写
转载时请在不对此文件做任何修改的同时注明出处
项目地址：https://github.com/steve02081504/ELC

注意：
	本文件可能使用了cpp20的新支持或语义，而某些编译器可能并没有支持
	同时，此项目并没有完成
*/
//#define use_as_template template<bool=true>
#define often_noexcept
#define noexcept_as(line) noexcept(noexcept(line))

#define floop while(1)

#define enable_if(...) class enable_state= ::std::enable_if_t<__VA_ARGS__>
#define enabled_by_default class enable_state=void
#define disabled_by_default class enable_state= ::std::enable_if_t<false>
#define enable_if_not_ill_form(...) class enable_state= ::std::void_t<decltype(__VA_ARGS__)>
#define enable_flag class enable_state

#define INTER_NAMESPACE(NAMESPACENAME) namespace NAMESPACENAME{
#define BREAK_NAMESPACE }
