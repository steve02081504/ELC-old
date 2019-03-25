//memtools.hpp
//at namespace elc::base
/*
未完成的elc解释器base文件
由steve02081504与Alex0125设计、编写
转载时请在不对此文件做任何修改的同时注明出处
项目地址：https://github.com/steve02081504/ELC

注意：
	本文件可能使用了cpp20的新支持或语义，而某些编译器可能并没有支持
	同时，此项目并没有完成
*/
class copy_t;
class construct_t;
class move_t;
class destory_t;
class copy_construct_t;
class move_construct_t;

constexpr struct copy_construct_t{
	template<class T>
	constexpr bool nothrow=::std::is_nothrow_copy_constructible_v<T>;
}copy_construct{};

template<class T>
inline T*copy_construct(T*to,const T*,zero_t)noexcept{return to;}
template<class T>
inline T*copy_construct(T*to,const T*from,size_t size)noexcept(::std::is_nothrow_copy_constructible_v<T>){
	if constexpr(::std::is_trivially_copy_constructible_v<T>)
		return reinterpret_cast<T*>(::std::memcpy(to,from,sizeof(T)*size));
	else{
		while(size--)
			new(to+size)T(from[size]);
		return to;
	}
}

template<class T>
inline void destory(T*to)noexcept{
	if constexpr(!::std::is_trivially_destructible_v<T>)to->~T();
}
template<class T>
inline void destory(T*,zero_t)noexcept{}
template<class T>
inline void destory(T*begin,size_t size)noexcept{
	while(size--)destory(begin+size);
}
