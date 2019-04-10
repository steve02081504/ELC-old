//alloc.hpp
//at namespace elc::memory
/*
未完成的elc解释器base文件
由steve02081504与Alex0125设计、编写
转载时请在不对此文件做任何修改的同时注明出处
项目地址：https://github.com/steve02081504/ELC

注意：
	本文件可能使用了cpp20的新支持或语义，而某些编译器可能并没有支持
	同时，此项目并没有完成
*/
using ::std::size_t;
using ::std::nullptr_t;
inline void gc()noexcept;
[[nodiscard]]inline void*alloc(zero_t)noexcept{return nullptr;}
[[nodiscard]]inline void*alloc(size_t size)noexcept{
	if(size){//因为辣鸡c标准没有规定0大小分配的返回值，所以检查
		void*tmp;
		while(!(tmp=::std::malloc(size)))gc();
		return tmp;
	}else return nullptr;
}
[[nodiscard]]inline void*aligned_alloc(size_t,zero_t)noexcept{return nullptr;}
[[nodiscard]]inline void*aligned_alloc(size_t align,size_t size)noexcept{
	if(size){//同上
		void*tmp;
		while(!(tmp=::std::aligned_alloc(align,size)))gc();
		return tmp;
	}else return nullptr;
}
template<class T>
[[nodiscard]]inline T*alloc(zero_t)noexcept{return nullptr;}
template<class T>
[[nodiscard]]inline T*alloc(size_t num=1)noexcept{return::std::assume_aligned<alignof(T)>(reinterpret_cast<T*>(aligned_alloc(alignof(T),sizeof(T)*num)));}

inline void free(nullptr_t)noexcept{}
void inline free(void*p)noexcept{::std::free(p);}//逼 死强 迫
//症
[[nodiscard]]inline void*realloc(nullptr_t,zero_t)noexcept{return nullptr;}
[[nodiscard]]inline void*realloc(void*ptr,zero_t)noexcept{free(ptr);return nullptr;}
[[nodiscard]]inline void*realloc(nullptr_t,size_t size)noexcept{return alloc(size);}
[[nodiscard]]inline void*realloc(void*ptr,size_t nsize)noexcept{
	if(nsize){
		void*tmp;
		while(!(tmp=::std::realloc(ptr,nsize)))gc();
		return tmp;
	}else{
		free(ptr);
		return nullptr;
	}
}

template<class T>[[nodiscard]]inline T*realloc(T*ptr,zero_t)noexcept{return reinterpret_cast<T*>(realloc(reinterpret_cast<void*>(ptr),zero));}
template<class T>[[nodiscard]]inline T*realloc(T*ptr,size_t nsize)noexcept{return reinterpret_cast<T*>(realloc(reinterpret_cast<void*>(ptr),sizeof(T)*nsize));}
