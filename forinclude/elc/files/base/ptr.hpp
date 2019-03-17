//ptr.hpp
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

//修改自 https://github.com/steve02081504/steve.h/blob/master/files/steve/ref_ptr.hpp

namespace ptr_n{
	//base ptr
	template<class T>
	struct same_ptr_p_t{
		mutable T*to;
		explicit same_ptr_p_t(T*a)noexcept:to(a){}
		same_ptr_p_t(const same_ptr_p_t&)=default;
		[[nodiscard]]T*get()const noexcept{return to;}
	};
	template<class T,typename ref_type>
	struct same_ref_p_t:same_ptr_p_t<T>{
		using same_ptr_p_t<T>::to;
		explicit same_ref_p_t(T*a)noexcept:same_ptr_p_t<T>(a){}
		explicit same_ref_p_t(const same_ptr_p_t<T>&a)noexcept:same_ptr_p_t<T>(a){}

		static void cut_ref(T*a)noexcept{static_cast<ref_type*>(a)->cut_ref();}
		static void add_ref(T*a)noexcept{static_cast<ref_type*>(a)->add_ref();}

		void cut_ref()const noexcept{cut_ref(to);}
		void add_ref()const noexcept{add_ref(to);}

		void swap(same_ref_p_t&a)noexcept{using std::swap;swap(to,a.to);}
	};

	template<class T>constexpr T*get_null_p()noexcept;//{return T::null_p;}

	template<class T,typename ref_type>
	struct ptr_t:same_ref_p_t<T,ref_type>{
		typedef same_ref_p_t<T,ref_type>same_ref;
		typedef same_ptr_p_t<T>same_ptr;
		using same_ref::add_ref;
		using same_ref::cut_ref;
		using same_ref::swap;
		using same_ptr::to;

		explicit ptr_t(T*a,special_init_t)noexcept:same_ref(a){}
		ptr_t(T*a)noexcept:same_ref(a){add_ref();}
		ptr_t(const same_ptr&a)noexcept:same_ref(a){add_ref();}
		ptr_t(ptr_t&a)noexcept:ptr_t((same_ptr&)a){}
		ptr_t(ptr_t&&a)noexcept:ptr_t((same_ptr&)a){}
		ptr_t(::std::nullptr_t=nullptr)noexcept:ptr_t(get_null_p<T>()){}
		~ptr_t()noexcept{cut_ref();}

		void reset(T*a)const noexcept{auto tmp=to;add_ref(to=a);cut_ref(tmp);}
	};

	template<class T>[[nodiscard]]inline bool bool_converter(T*arg)noexcept{return arg!=get_null_p<T>();}
	template<class T>[[nodiscard]]inline bool checker(T*)noexcept{return false;}

	template<class T>[[nodiscard]]inline T*check(T*a)noexcept{if(checker(a))return get_null_p<T>();else return a;}

	template<class T>
	class safe_p_t;
	template<class T>
	using convert_interface_t=ptr_t<::std::remove_cvref_t<T>,ref_able<::std::remove_cvref_t<T>>>;

	namespace compare_n{
		template<class T,class T_>
		class compare_interface_t;
	}
	using compare_n::compare_interface_t;

	template<class T,typename ref_type>
	struct base_p_t:ptr_t<T,ref_type>,compare_interface_t<T,base_p_t<T,ref_type>>{
		typedef ptr_t<T,ref_type>base_t;
		typedef convert_interface_t<T>convert_interface;
		template<class T_>
		using compare_interface=compare_interface_t<T,T_>;
		using typename base_t::same_ref;
		using typename base_t::same_ptr;
		using base_t::reset;
		using same_ref::swap;
		using same_ptr::to;
		using base_t::base_t;

		base_p_t(base_p_t&a)noexcept:base_t(a){}
		base_p_t(base_p_t&&a)noexcept:base_t(::std::move(a)){}

		[[nodiscard]]T*get()const noexcept{
			if(checker(to))[[unlikely]]{
				reset(get_null_p<T>());
				return get_null_p<T>();
			}else[[likely]]return to;
		}

		T*operator->()const noexcept{return get();}
		[[nodiscard]]T&operator*()const noexcept{return*get();}
		[[nodiscard]]explicit operator bool()const noexcept{return bool_converter(get());}
		[[nodiscard]]explicit operator T*()const noexcept{return get();}

		base_p_t&operator=(T*a)&noexcept{reset(a);return*this;}
		base_p_t&operator=(const same_ptr&a)&noexcept{reset(a.to);return*this;}
		base_p_t&operator=(base_p_t&a)&noexcept{reset(a.get());return*this;}
		base_p_t&operator=(same_ref&&a)&noexcept{swap(a);return*this;}
		base_p_t&operator=(::std::nullptr_t)&noexcept{reset(get_null_p<T>());return*this;}

		template<class T_,enable_if(::std::is_convertible_v<T_,convert_interface>)>
		base_p_t&operator=(T_&&a)&noexcept(::std::is_nothrow_convertible_v<T_,convert_interface>){reset(check(static_cast<convert_interface>(::std::forward<T_>(a)).to));return*this;}


		template<class T_,enable_if(::std::is_convertible_v<T_,convert_interface>)>
		base_p_t(T_&&a)noexcept(::std::is_nothrow_convertible_v<T_,convert_interface>):base_p_t(check(static_cast<convert_interface>(::std::forward<T_>(a)).to)){}

		/*
		//会出错,暂时封印.(?)
		template<enable_if_not_ill_form(::std::declval<T>().destroy())>//for delete
		operator decltype(&do_your_fucking_delete)()noexcept_as(::std::declval<T>().destroy()){
			(**this).destroy();
			reset(get_null_p<T>());
			return&do_your_fucking_delete;
		}
		*/
	};

	template<class T,typename ref_type>
	inline void swap(base_p_t<T,ref_type>&a,base_p_t<T,ref_type>&b)noexcept{
		a.swap(b);
	}

	template<class T>
	using comn_p_t=base_p_t<T,ref_able<::std::remove_cvref_t<T>>>;
	template<class T>
	using weak_p_t=base_p_t<T,weak_ref_able<::std::remove_cvref_t<T>>>;
}
namespace ptr_n::compare_n{
	template<class T>
	constexpr bool nothrow_convert()noexcept{return T::nothrow_convert_v;}
	template<class T,class T_>
	[[nodiscard]]inline T*get_p(const T_&a)noexcept(nothrow_convert<T_>()){return a.get();}
	template<class T,class T_>
	class compare_interface_t{
		typedef convert_interface_t<T> convert_interface;
		static constexpr bool nothrow_convert_v=::std::is_convertible_v<T_*,same_ptr_p_t<T>*>?true: ::std::is_nothrow_convertible_v<T_,convert_interface>;

		[[nodiscard]]T*get()const noexcept(nothrow_convert_v){
			if constexpr(::std::is_convertible_v<T_*,same_ptr_p_t<T>*>)
				return check(static_cast<same_ptr_p_t<T>*>(static_cast<T_*>(const_cast<compare_interface_t*>(this)))->get());
			else
				return check(static_cast<convert_interface>(*static_cast<T_*>(const_cast<compare_interface_t*>(this))).get());
		}
	//friends:
		friend constexpr bool nothrow_convert<compare_interface_t>()noexcept;
		friend T*get_p<T,compare_interface_t>(const compare_interface_t&a)noexcept(nothrow_convert<compare_interface_t>());
	};
	template<class T,class T_>
	[[nodiscard]]inline bool operator!=(const compare_interface_t<T,T_>&a,::std::nullptr_t)
	noexcept(nothrow_convert<compare_interface_t<T,T_>>())
	{return bool_converter(get_p<T>(a));}
	template<class T,class T_>
	[[nodiscard]]inline bool operator==(const compare_interface_t<T,T_>&a,::std::nullptr_t)
	noexcept(nothrow_convert<compare_interface_t<T,T_>>())
	{return!(a!=nullptr);}
	template<class T,class T_>
	[[nodiscard]]inline bool operator!=(::std::nullptr_t,const compare_interface_t<T,T_>&a)
	noexcept(nothrow_convert<compare_interface_t<T,T_>>())
	{return a!=nullptr;}
	template<class T,class T_>
	[[nodiscard]]inline bool operator==(::std::nullptr_t,const compare_interface_t<T,T_>&a)
	noexcept(nothrow_convert<compare_interface_t<T,T_>>())
	{return a==nullptr;}

	template<class T,class T_,class T__,enable_if(::std::is_convertible_v<T__,T*>)>
	[[nodiscard]]inline bool operator==(const compare_interface_t<T,T_>&a,const T__&b)
	noexcept(nothrow_convert<compare_interface_t<T,T_>>()&&::std::is_nothrow_convertible_v<T__,T*>)
	{return get_p<T>(a)==check(static_cast<T*>(b));}
	template<class T,class T_,class T__,enable_if(::std::is_convertible_v<T__,T*>)>
	[[nodiscard]]inline bool operator!=(const compare_interface_t<T,T_>&a,const T__&b)
	noexcept(nothrow_convert<compare_interface_t<T,T_>>()&&::std::is_nothrow_convertible_v<T__,T*>)
	{return!(a==b);}
	template<class T,class T_,class T__,enable_if(::std::is_convertible_v<T__,T*>)>
	[[nodiscard]]inline bool operator==(const T__&b,const compare_interface_t<T,T_>&a)
	noexcept(nothrow_convert<compare_interface_t<T,T_>>()&&::std::is_nothrow_convertible_v<T__,T*>)
	{return a==b;}
	template<class T,class T_,class T__,enable_if(::std::is_convertible_v<T__,T*>)>
	[[nodiscard]]inline bool operator!=(const T__&b,const compare_interface_t<T,T_>&a)
	noexcept(nothrow_convert<compare_interface_t<T,T_>>()&&::std::is_nothrow_convertible_v<T__,T*>)
	{return a!=b;}

	template<class T,class T_1,class T_2>
	[[nodiscard]]inline bool operator==(const compare_interface_t<T,T_1>&a,const compare_interface_t<T,T_2>&b)
	noexcept(nothrow_convert<compare_interface_t<T,T_1>>()&&nothrow_convert<compare_interface_t<T,T_2>>())
	{return get_p<T>(a)==get_p<T>(b);}

	template<class T,class T_1,class T_2>
	[[nodiscard]]inline bool operator!=(const compare_interface_t<T,T_1>&a,const compare_interface_t<T,T_2>&b)
	noexcept(nothrow_convert<compare_interface_t<T,T_1>>()&&nothrow_convert<compare_interface_t<T,T_2>>())
	{return!(a==b);}
}

BREAK_NAMESPACE
namespace memory{
	namespace root_n{
		template<class T>class root_list_t;
		template<class T>root_list_t<T>root_list;
		template<class T>
		struct root_list_t final:non_copyable,non_moveable,list_t<ptr_n::safe_p_t<T>>{
			typedef list_t<ptr_n::safe_p_t<T>> list;
			struct cons:cons_t<ptr_n::safe_p_t<T>>{
				cons():cons_t<ptr_n::safe_p_t<T>>(do_nothing){root_list<T>.add(this);}
				~cons()=default;
			};
			root_list_t()noexcept{}
			void mark_all_can_access()noexcept{
				auto i=list::head(),e=list::end();
				while(++i!=e)
					i->do_mark();
			}
		};
	}
	using root_n::root_list;
	using root_n::root_list_t;
}
INTER_NAMESPACE(base)
namespace ptr_n{
	template<class T>
	struct safe_p_t:comn_p_t<T>,private memory::root_list_t<T>::cons{
		typedef comn_p_t<T>base_t;
		using typename base_t::convert_interface;
		using typename base_t::same_ref;
		using typename base_t::same_ptr;
		using base_t::base_t;

		safe_p_t(safe_p_t&a)noexcept:base_t(a){}
		safe_p_t(safe_p_t&&a)noexcept:base_t(a){}
		~safe_p_t()noexcept=default;

		safe_p_t&operator=(safe_p_t&a)&noexcept{base_t::operator=(a);return*this;}
		safe_p_t&operator=(safe_p_t&&a)&noexcept{base_t::operator=(::std::move(a));return*this;}
		template<class T_,enable_if(::std::is_assignable_v<base_t,T_>)>
		safe_p_t&operator=(T_&&a)&noexcept(::std::is_nothrow_assignable_v<base_t,T_>){base_t::operator=(::std::forward<T_>(a));return*this;}
	private:
		friend class memory::root_list_t<T>;
		void do_mark()noexcept{static_cast<safe_ref_able<T>*>(base_t::get())->gc(i_know_what_i_do);}
		typedef cons_t<safe_p_t> cons;
		friend cons*list_n::cons_cast<safe_p_t>(safe_p_t*)noexcept;
		cons&get_cons_part()noexcept{return*this;}
		friend safe_p_t*list_n::un_cons_cast<safe_p_t>(cons*)noexcept;
		static safe_p_t&cast_from_cons(cons*a)noexcept{return*static_cast<safe_p_t*>(a);}
	};
	template<class T>
	inline void swap(safe_p_t<T>&a,safe_p_t<T>&b)noexcept{
		a.swap(b);
	}
}
using ptr_n::comn_p_t;
using ptr_n::weak_p_t;
using ptr_n::safe_p_t;
