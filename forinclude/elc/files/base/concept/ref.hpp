//ref.hpp
/*
未完成的elc解释器base文件
由steve02081504与Alex0125设计、编写
转载时请在不对此文件做任何修改的同时注明出处
项目地址：https://github.com/steve02081504/ELC

注意：
	本文件可能使用了cpp20的新支持或语义，而某些编译器可能并没有支持
	同时，此项目并没有完成
*/
//修改自 https://github.com/steve02081504/steve.h/blob/master/files/steve/ref_ptr.hpp
/*
之所以没有保留void重载并重写了safe_ref_able是因为空间方面的考虑
没有用std::share_ptr等是因为体积与速度的缘故
*/
typedef ::std::size_t link_num_t;
class ref_t:non_copyable,non_moveable{
	mutable link_num_t ref_num=0;
public:
	constexpr ref_t()noexcept=default;
	explicit constexpr ref_t(never_ref_num_zero_t)noexcept:ref_num(1){}
	void add_ref()const noexcept{ref_num++;}
	[[nodiscard]]bool cut_ref()const noexcept{return!--ref_num;}
	[[nodiscard]]operator bool()const noexcept{return ref_num;}
	void set_zero()noexcept{ref_num=0;}
	[[nodiscard]]link_num_t link_num(){return ref_num;}
};
template<class T>//T必须派生于ref_able<T>
class ref_able:non_copyable,non_moveable{
	ref_t ref;
public:
	constexpr ref_able()noexcept=default;
	explicit constexpr ref_able(never_ref_num_zero_t)noexcept:ref(never_ref_num_zero){}
	void add_ref()noexcept{ref.add_ref();}
	void cut_ref()noexcept{
		static_assert(noexcept(::std::declval<T>().ref_num_is_zero()));
		if(ref.cut_ref())static_cast<T*>(this)->ref_num_is_zero();
	}
	[[nodiscard]]bool has_link()noexcept{return ref;}
	[[nodiscard]]link_num_t link_num()noexcept{return ref.link_num();}
	void set_ref_num_zero(i_know_what_i_do_t)noexcept{ref.set_zero();}
};
template<class T>//T必须派生于weak_ref_able<T>
class weak_ref_able:non_copyable,non_moveable{
	ref_t ref;
public:
	constexpr weak_ref_able()noexcept=default;
	explicit constexpr weak_ref_able(never_ref_num_zero_t)noexcept:ref(never_ref_num_zero){}
	void add_ref()noexcept{ref.add_ref();}
	void cut_ref()noexcept{
		static_assert(noexcept(::std::declval<T>().weak_ref_num_is_zero()));
		if(ref.cut_ref())static_cast<T*>(this)->weak_ref_num_is_zero();
	}
	[[nodiscard]]bool has_weak_link()noexcept{return ref;}
	[[nodiscard]]link_num_t weak_link_num()noexcept{return ref.link_num();}
	void set_ref_num_zero(i_know_what_i_do_t)noexcept{ref.set_zero();}
};
//for ptr
template<class T>//同上
struct safe_ref_able:ref_able<T>,non_copyable,non_moveable{
	using ref_able<T>::ref_able;
	template<class wtfyoulike>friend struct safe_ref_able;
	friend inline void memory::gc()noexcept;
private:
	void gc()noexcept{static_cast<T*>(this)->gc_method();}
protected:
	template<class wtfyoulike>
	static void call_gc(wtfyoulike&a)noexcept{static_cast<safe_ref_able<wtfyoulike>*>(&a)->gc();}
public:
	void gc(i_know_what_i_do_t)noexcept{gc();}
};
