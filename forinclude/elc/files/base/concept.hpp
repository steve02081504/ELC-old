//concept.hpp
/*
未完成的elc解释器base文件
由steve02081504与Alex0125设计、编写
转载时请在不对此文件做任何修改的同时注明出处
项目地址：https://github.com/steve02081504/ELC

注意：
	本文件可能使用了cpp20的新支持或语义，而某些编译器可能并没有支持
	同时，此项目并没有完成
*/

/*
原九度凋 2019/2/11 0:15:52
。。。[图片]

原九度凋 2019/2/11 0:16:01
还能不能让人愉快的偷懒。。。

夏の幻 2019/2/11 0:16:16
？？

夏の幻 2019/2/11 0:16:19
你是真的没写啊

原九度凋 2019/2/11 0:16:38
反正delete干嘛要写。。。

夏の幻 2019/2/11 0:16:40
一般都是认不出的

夏の幻 2019/2/11 0:17:01
然而就是要写，你可以写一个noncopyable然后继承这个

夏の幻 2019/2/11 0:17:07
就不用每个都手动写了

原九度凋 2019/2/11 0:17:13
好主意

原九度凋 2019/2/11 0:17:19
学到了

原九度凋 2019/2/11 0:17:22
谢谢

*/
struct non_copyable{
	constexpr non_copyable()=default;
	constexpr non_copyable(non_copyable&)=delete;
	constexpr non_copyable(non_copyable&&)=default;
	non_copyable& operator=(non_copyable&)&noexcept=delete;
	non_copyable& operator=(non_copyable&&)&noexcept=default;
};
struct non_moveable{
	constexpr non_moveable()=default;
	constexpr non_moveable(non_moveable&)=default;
	constexpr non_moveable(non_moveable&&)=delete;
	non_moveable& operator=(non_moveable&)&noexcept=default;
	non_moveable& operator=(non_moveable&&)&noexcept=delete;
};

#define defspecflag(name)\
struct name##_t{};\
constexpr name##_t name{}

defspecflag(do_nothing);
defspecflag(just_init_flag);
defspecflag(special_init);
defspecflag(never_ref_num_zero);
defspecflag(i_know_what_i_do);

#undef defspecflag

template<class T>
struct type_pack_t{typedef T type;};
template<class T>
constexpr type_pack_t<T> type_pack{};

struct zero_t{
	template<class T,enable_if(::std::is_convertible_v<decltype(0),T>)>
	operator T()const noexcept(::std::is_nothrow_convertible_v<decltype(0),T>){return 0;}
};
constexpr zero_t zero{};

struct do_your_fucking_delete_t{
	static void operator delete(void*)noexcept{}
};
constexpr do_your_fucking_delete_t do_your_fucking_delete{};

using ::std::byte;
template<class T>
[[nodiscard]]inline T&data_cast(byte*p){return*::std::launder(reinterpret_cast<T*>(p));}

namespace ref_n{
	#include"concept/ref.hpp"
}
using ref_n::ref_able;
using ref_n::weak_ref_able;
using ref_n::safe_ref_able;

namespace list_n{
	#include"concept/list.hpp"
}
using list_n::base_list;
using list_n::base_cons;
using list_n::list_t;
using list_n::cons_t;

enum set_type:bool{seted=true,not_set=false};
class flag{
	bool _;
public:
	explicit constexpr flag(set_type a=not_set)noexcept:_(a){}
	[[nodiscard]]explicit operator bool()const noexcept{return _;}
	flag(flag&a)noexcept:_((bool)a){}
	flag(flag&&a)noexcept:_((bool)a){}
	void operator=(flag&)&noexcept=delete;
	void operator=(flag&&)&noexcept=delete;
	void set()noexcept{_=true;}
	void unset()noexcept{_=false;}
};

enum mark_type:bool{marked=true,not_mark=false};
class mark_able:non_copyable,non_moveable{
	mutable flag m;
public:
	explicit constexpr mark_able(mark_type a=not_mark)noexcept:m(a==not_mark?not_set:seted){};
	void mark()const noexcept{m.set();}
	void unmark()const noexcept{m.unset();}
	[[nodiscard]]bool was_marked()const noexcept{return(bool)m;}
};

template<class T,class...other>
class data_t:non_copyable,non_moveable{
	alignas(::std::max({alignof(T),alignof(other)...}))
	byte data[::std::max({sizeof(T),sizeof(other)...})];
public:
	constexpr data_t()noexcept{}
	[[nodiscard]]byte*get_data()noexcept{return data;}
	template<class T_=T,typename...args,enable_if(::std::is_constructible_v<T_,args...>)>
	void activation(args&&...rest)noexcept(::std::is_nothrow_constructible_v<T_,args...>){new(&data)T_(::std::forward<args>(rest)...);}
	template<class T_=T>
	[[nodiscard]]T_*get()noexcept{return&data_cast<T_>(data);}
	template<class T_=T,class func_t,enable_if(::std::is_invocable_r_v<void,func_t,T_*>)>
	void activation_by(func_t&&activator)
	noexcept(::std::is_nothrow_invocable_v<func_t,T_*>)
	{activator(get<T_>());}
	template<class T_=T>
	void inactivation()noexcept(::std::is_nothrow_destructible_v<T_>){get<T_>()->~T_();}
};
