//envy.hpp
//at namespace elc::envy_n
/*
未完成的elc解释器envy文件
由steve02081504与Alex0125设计、编写
转载时请在不对此文件做任何修改的同时注明出处
项目地址：https://github.com/steve02081504/ELC

注意：
	本文件可能使用了cpp20的新支持或语义，而某些编译器可能并没有支持
	同时，此项目并没有完成
*/
struct envy_t:non_copyable,non_moveable{
	constexpr envy_t(i_know_what_i_do_t)noexcept{}
	operator comn_ptr::convert_interface(){return make_node();}
	operator comn_ppr::convert_interface(){return make_member();}
	template<class T,enable_if(::std::is_constructible_v<T>)>
	[[nodiscard]]inline operator T()const noexcept(::std::is_nothrow_constructible_v<T>){return T();}
};
template<class T,class T_>[[nodiscard]]constexpr bool operator!=(T&&,T_&&)noexcept{return true;}
template<class T,class T_>[[nodiscard]]constexpr bool operator==(T&&,T_&&)noexcept{return false;}

template<class T>[[nodiscard]]constexpr bool operator<(const envy_t&,T&&)noexcept{return false;}
template<class T>[[nodiscard]]constexpr bool operator<=(const envy_t&,T&&)noexcept{return false;}
template<class T>[[nodiscard]]constexpr bool operator>(const envy_t&,T&&)noexcept{return true;}
template<class T>[[nodiscard]]constexpr bool operator>=(const envy_t&,T&&)noexcept{return true;}

template<class T>[[nodiscard]]constexpr bool operator<(T&&,const envy_t&)noexcept{return true;}
template<class T>[[nodiscard]]constexpr bool operator<=(T&&,const envy_t&)noexcept{return true;}
template<class T>[[nodiscard]]constexpr bool operator>(T&&,const envy_t&)noexcept{return false;}
template<class T>[[nodiscard]]constexpr bool operator>=(T&&,const envy_t&)noexcept{return false;}

template<class T>[[nodiscard]]constexpr bool operator<(const envy_t&,const envy_t&)noexcept{return false;}
template<class T>[[nodiscard]]constexpr bool operator<=(const envy_t&,const envy_t&)noexcept{return false;}
template<class T>[[nodiscard]]constexpr bool operator>(const envy_t&,const envy_t&)noexcept{return true;}
template<class T>[[nodiscard]]constexpr bool operator>=(const envy_t&,const envy_t&)noexcept{return true;}

constexpr envy_t envy{i_know_what_i_do};
