//member.hpp
/*
未完成的elc解释器core文件
由steve02081504与Alex0125设计、编写
转载时请在不对此文件做任何修改的同时注明出处
项目地址：https://github.com/steve02081504/ELC

注意：
	本文件可能使用了cpp20的新支持或语义，而某些编译器可能并没有支持
	同时，此项目并没有完成
*/
struct member final:non_copyable,non_moveable,
safe_ref_able<member>{
public:
	struct base_member{
		virtual ~base_member()noexcept=0;
		[[nodiscard]]virtual comn_ptr access()=0;
		virtual void set(comn_ptr)=0;
		virtual void to_weak()often_noexcept=0;
		virtual void un_weak()often_noexcept=0;
		virtual void to_virtual()often_noexcept=0;
		virtual void un_virtual()often_noexcept=0;
		[[nodiscard]]virtual comn_ptr get_crude_value()noexcept=0;
		template<class T,typename...args,enable_if(::std::is_constructible_v<T,args...>)>
		void convert(args&&...rest)noexcept(::std::is_nothrow_constructible_v<T,args...>){this->~base_member();new(this)T(::std::forward<args>(rest)...);}
	};
private:
	static void call_setter(comn_ptr to,safe_ptr value);
	static comn_ppr call_accesser(comn_ptr to);
	static comn_ptr make_virtual(safe_ptr to);

	struct not_weak_member:base_member{
		comn_ptr to;
		explicit not_weak_member(comn_ptr a)noexcept:to(a){}
		~not_weak_member()noexcept override=default;
		[[nodiscard]]comn_ptr get_crude_value()noexcept override{return to;}
	};
	struct weak_member:base_member{
		weak_ptr to;
		explicit weak_member(comn_ptr a)noexcept:to(a){}
		~weak_member()noexcept override=default;
		[[nodiscard]]comn_ptr get_crude_value()noexcept override{return to;}
	};

	template<class T>class was_virtual;
	template<class T>class not_virtual;

	template<class T>struct was_virtual final:T{
		explicit was_virtual(comn_ptr a)noexcept:T(a){}
		virtual~was_virtual()noexcept override final=default;
		template<class A>void convert()noexcept{comn_ptr tmp=T::to;this->~was_virtual();new(this)A(tmp);}
		[[nodiscard]]virtual comn_ptr access()override final{return call_accesser(T::to)->access();}
		virtual void set(comn_ptr a)override final{call_setter(T::to,a);}
		virtual void to_weak()noexcept override final{if constexpr(::std::is_same_v<not_weak_member,T>)convert<was_virtual<weak_member>>();}
		virtual void un_weak()noexcept override final{if constexpr(::std::is_same_v<weak_member,T>)convert<was_virtual<not_weak_member>>();}
		virtual void to_virtual()noexcept override final{call_accesser(T::to)->to_virtual();}
		virtual void un_virtual()noexcept override final{convert<not_virtual<T>>();}
	};
	template<class T>struct not_virtual final:T{
		explicit not_virtual(comn_ptr a)noexcept:T(a){}
		virtual~not_virtual()noexcept override final=default;
		template<class A>void convert()noexcept{comn_ptr tmp=T::to;this->~not_virtual();new(this)A(tmp);}
		[[nodiscard]]virtual comn_ptr access()override final{return T::to;}
		virtual void set(comn_ptr a)override final{T::to=a;}
		virtual void to_weak()noexcept override final{if constexpr(::std::is_same_v<not_weak_member,T>)convert<not_virtual<weak_member>>();}
		virtual void un_weak()noexcept override final{if constexpr(::std::is_same_v<weak_member,T>)convert<not_virtual<not_weak_member>>();}
		virtual void to_virtual()noexcept override final{convert<was_virtual<T>>();}
		virtual void un_virtual()noexcept override final{T::to=make_virtual(T::to);}
	};
public:
	typedef not_virtual<not_weak_member> not_weak_not_virtual_member;
	typedef not_virtual<weak_member    > weak_not_virtual_member;
	typedef was_virtual<not_weak_member> not_weak_virtual_member;
	typedef was_virtual<weak_member    > weak_virtual_member;
private:
	mutable data_t<not_weak_not_virtual_member,weak_not_virtual_member,not_weak_virtual_member,weak_virtual_member>data;
	[[nodiscard]]base_member*get()noexcept{return data.get<base_member>();}
	void inactivation(){data.inactivation<base_member>();}

public:
	[[nodiscard]]comn_ptr access(){return get()->access();}
	void set(comn_ptr a){get()->set(a);}
	void to_weak()noexcept{get()->to_weak();}
	void un_weak()noexcept{get()->un_weak();}
	void to_virtual()noexcept{get()->to_virtual();}
	void un_virtual()noexcept{get()->un_virtual();}
	[[nodiscard]]comn_ptr get_crude_value(i_know_what_i_do_t)noexcept{return get()->get_crude_value();}


	template<typename special_t>
	explicit member(special_init_t,type_pack_t<special_t>):safe_ref_able<member>(never_ref_num_zero){
		//你必须知道你在干什么
		static_assert(sizeof(special_t)<=sizeof(data),"size error");
		static_assert(alignof(special_t)<=alignof(decltype(data)),"align error");
		static_assert(::std::is_base_of_v<base_member,special_t>);
		data.activation<special_t>();
	}

private:
	friend ref_able<member>;
	void ref_num_is_zero()noexcept{inactivation();member_pool.use_end(this);}

	friend safe_ref_able<member>;
	inline void gc_method()noexcept;

	friend decltype(member_pool)::friend_t;
//for pool.
	explicit member(just_init_flag_t)noexcept{}//隐式调用ref_able的默认构造函数
	[[nodiscard]]bool was_using()noexcept{return has_link();}
	void start_using(comn_ptr a=get_nil_address())noexcept{data.activation(a);}
public:
	~member()noexcept=default;
};
inline member::base_member::~base_member()noexcept{}
