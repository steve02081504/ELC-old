//array.hpp
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
namespace array_n{
	template<class T,typename size_type>
	struct base_array{
		T*ptr;
		size_type size;
		explicit base_array(size_type s,T*init)noexcept:ptr(init),size(s){}
		explicit base_array(do_nothing_t)noexcept{}
		inline static void construct(T*begin,size_type size)noexcept{
			while(size--)type_info<T>::initer(begin+size);
		}
		inline static void destory(T*begin,size_type size)noexcept{
			if constexpr(!::std::is_trivially_destructible_v<T>)while(size--)begin[size].~T();
		}
		void narrow(zero_t)noexcept{
			destory(ptr,size);
			ptr=memory::realloc(ptr,zero);
			size=zero;
		}
		void narrow(size_type newsize)noexcept{
			destory(ptr+newsize,size-newsize);
			ptr=memory::realloc(ptr,sizeof(T)*newsize);
			size=newsize;
		}
		void expand(size_type newsize)noexcept{
			ptr=memory::realloc(ptr,sizeof(T)*newsize);
			construct(ptr+size,newsize-size);
			size=newsize;
		}
		void build_up(size_type newsize)noexcept{
			ptr=memory::alloc<T>(newsize);
			construct(ptr,size=newsize);
		}
	};
	template<class T,typename size_type=::std::size_t>
	class array:base_array<T,size_type>{
		typedef base_array<T,size_type>base_t;
		using base_t::base_t;
		using base_t::construct;
		using base_t::destory;
		using base_t::narrow;
		using base_t::expand;
		using base_t::build_up;
		using base_t::ptr;
		using base_t::size;
	public:
		constexpr array()noexcept:base_t(zero,nullptr){}
		explicit array(size_type size)noexcept:base_t(do_nothing){build_up(size);}
		explicit array(special_init_t,size_type size,T*init)noexcept:base_t(size,init){}
		void reset_for_special_init(i_know_what_i_do_t){size=zero;ptr=nullptr;}
		~array()noexcept{narrow(zero);}
		[[nodiscard]]T&arec(size_type a)noexcept{return ptr[a];}
		void resize(zero_t)noexcept{narrow(zero);}
		void resize(size_type newsize)noexcept{
			if(!ptr){if(newsize)build_up(newsize);return;}
			if(newsize>size)
				expand(newsize);
			else if(newsize<size){
				narrow(newsize);
			}
		}
		[[nodiscard]]size_type get_size()const noexcept{return size;}
		[[nodiscard]]T*get_begin_addres()noexcept{return ptr;}
		void for_each(void mapper(T&)noexcept)noexcept{
			size_type size=get_size();
			while(size--)mapper(arec(size));
		}
		void for_each(void mapper(T&)){
			size_type size=get_size();
			while(size--)mapper(arec(size));
		}
	};
	template<class T,typename size_type=::std::size_t>
	class circulate_array:base_array<T,size_type>{
		typedef base_array<T,size_type>base_t;
		using base_t::base_t;
		using base_t::construct;
		using base_t::destory;
		using base_t::narrow;
		using base_t::expand;
		using base_t::build_up;
		using base_t::ptr;
		using base_t::size;
		static constexpr T*fail_p=type_info<T>::fail_p();
	public:
		constexpr circulate_array()noexcept:base_t(1,fail_p){}
		explicit circulate_array(size_type size)noexcept:circulate_array(){if(size)build_up(size);}
		explicit circulate_array(special_init_t,size_type size,T*init)noexcept:base_t(size,init){}
		void reset_for_special_init(i_know_what_i_do_t){size=1;ptr=fail_p;}
		~circulate_array()noexcept{if(ptr!=fail_p)narrow(zero);}
		[[nodiscard]]T&nocheck_arec(size_type a)noexcept{return ptr[a];}
		[[nodiscard]]T&arec(size_type a)noexcept{return ptr[a%size];}
		void resize(zero_t)noexcept{narrow(zero);}
		void resize(size_type newsize)noexcept{
			if(ptr==fail_p){if(newsize)build_up(newsize);return;}
			if(newsize>size)
				expand(newsize);
			else if(newsize<size){
				narrow(newsize);
				if(!newsize){ptr=fail_p;size=1;}
			}
		}
		[[nodiscard]]size_type get_size()const noexcept{return ptr==fail_p?0:size;}
		void for_each(void mapper(T&)noexcept)noexcept{
			size_type size=get_size();
			while(size--)mapper(nocheck_arec(size));
		}
		void for_each(void mapper(T&)){
			size_type size=get_size();
			while(size--)mapper(nocheck_arec(size));
		}
	};
}
using array_n::array;
using array_n::circulate_array;

template<class T,typename size_type=::std::size_t>
class activable_array{
	mutable data_t<array<T,size_type>>data;
public:
	constexpr activable_array()noexcept=default;
	void activation()noexcept{data.activation();}
	void activation(size_type size)noexcept{data.activation(size);}
	void special_activation(size_type size,T*begin)noexcept{data.activation(special_init,size,begin);}
	void inactivation()noexcept{data.inactivation();}
	void special_inactivation()noexcept{data.get()->reset_for_special_init(i_know_what_i_do);data.inactivation();}
	//using_all_form(*data.get());
	explicit operator array<T,size_type>()noexcept{return*data.get();}
	[[nodiscard]]T&arec(size_type a)noexcept{return data.get()->arec(a);}
	void resize(zero_t)noexcept{return data.get()->resize(zero);}
	void resize(size_type newsize)noexcept{return data.get()->resize(newsize);}
	[[nodiscard]]size_type get_size()const noexcept{return data.get()->get_size();}
	[[nodiscard]]T*get_begin_addres()noexcept{return data.get()->get_begin_addres();}
	void for_each(void mapper(T&)noexcept)noexcept{data.get()->for_each(mapper);}
	void for_each(void mapper(T&)){data.get()->for_each(mapper);}
};
template<class T,typename size_type=::std::size_t>
class activable_circulate_array{
	mutable data_t<circulate_array<T,size_type>>data;
public:
	constexpr activable_circulate_array()noexcept=default;
	void activation()noexcept{data.activation();}
	void activation(size_type size)noexcept{data.activation(size);}
	void special_activation(size_type size,T*init)noexcept{data.activation(special_init,size,init);}
	void inactivation()noexcept{data.inactivation();}
	void special_inactivation()noexcept{data.get()->reset_for_special_init(i_know_what_i_do);data.inactivation();}
	//using_all_form(*data.get());
	explicit operator circulate_array<T,size_type>()noexcept{return*data.get();}
	[[nodiscard]]T&nocheck_arec(size_type a)noexcept{return data.get()->nocheck_arec(a);}
	[[nodiscard]]T&arec(size_type a)noexcept{return data.get()->arec(a);}
	void resize(zero_t)noexcept{return data.get()->resize(zero);}
	void resize(size_type newsize)noexcept{return data.get()->resize(newsize);}
	[[nodiscard]]size_type get_size()const noexcept{return data.get()->get_size();}
	void for_each(void mapper(T&)noexcept)noexcept{data.get()->for_each(mapper);}
	void for_each(void mapper(T&)){data.get()->for_each(mapper);}
};
