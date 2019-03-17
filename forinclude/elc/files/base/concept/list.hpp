//list.hpp
//at namespace elc::base::list_n
/*
未完成的elc解释器base文件
由steve02081504与Alex0125设计、编写
转载时请在不对此文件做任何修改的同时注明出处
项目地址：https://github.com/steve02081504/ELC

注意：
	本文件可能使用了cpp20的新支持或语义，而某些编译器可能并没有支持
	同时，此项目并没有完成
*/
struct base_cons:non_copyable,non_moveable{
private:
	base_cons*before;
	base_cons*next;
public:
	[[nodiscard]]base_cons*get_before()noexcept{return before;}
	[[nodiscard]]base_cons*get_next()noexcept{return next;}
	void set_next(base_cons*a)noexcept{
		next=a;
		a->before=this;
	}
	void set_before(base_cons*a)noexcept{
		before=a;
		a->next=this;
	}
	void next_insert(base_cons*a)noexcept{
		a->next=next;
		a->before=this;
		next=next->before=a;
	}
	void before_insert(base_cons*a)noexcept{
		a->before=before;
		a->next=this;
		before=before->next=a;
	}
	void bind_with(base_cons*a)noexcept{
		set_next(a);
		set_before(a);
	}
	void remove_from_list()noexcept{
		before->next=next;
		next->before=before;
	}
	explicit base_cons(base_cons*b,base_cons*n)noexcept{set_before(b);set_next(n);}
	explicit base_cons(base_cons*a)noexcept:base_cons(a,a){}
	explicit base_cons(do_nothing_t)noexcept{}
};
struct base_list:non_copyable,non_moveable{
	struct iterator{
		base_cons*value;
		iterator()noexcept=default;
		iterator(base_cons*a)noexcept:value(a){}
		bool operator==(base_cons*a)const noexcept{return value==a;}
		bool operator!=(base_cons*a)const noexcept{return!operator==(a);}
		iterator&operator=(base_cons*a)&noexcept{value=a;return*this;}
		iterator&operator++()&noexcept{return*this=value->get_next();}
		iterator&operator--()&noexcept{return*this=value->get_before();}
		iterator operator++(int)&noexcept{auto a=*this;operator++();return a;}
		iterator operator--(int)&noexcept{auto a=*this;operator--();return a;}
		base_cons*operator->()noexcept{return value;}
		base_cons&operator*()noexcept{return*operator->();}
		operator base_cons*()noexcept{return operator->();}
	};
	base_cons head_,end_;
	base_list()noexcept:head_(do_nothing),end_(&head_){}
/*
	constexpr base_list(base_list&&a)noexcept{
		a.head_.next->set_before(&head_);
		a.end_.before->set_next(&end_);
		a.head_.bind_with(&a.end_);
	}
*/
	inline void add(base_cons*a)noexcept{
		end_.before_insert(a);
	}
	[[nodiscard]]iterator begin()noexcept{return head_.get_next();}//这叫头迭代器
	[[nodiscard]]iterator end()noexcept{return&end_;}//这叫超尾迭代器
	[[nodiscard]]iterator head()noexcept{return&head_;}//。。。。这个大概就是超头迭代器了🠀񘰀
	[[nodiscard]]bool empty()noexcept{return head_.get_next()==&end_;}
};
template<class T>
struct cons_t;
template<class T>
[[nodiscard]]inline cons_t<T>*cons_cast(T*a)noexcept{
	if constexpr(::std::is_convertible_v<T*,cons_t<T>*>)
		return a;
	else return&a->get_cons_part();//for private base
}
template<class T>
[[nodiscard]]inline T*un_cons_cast(cons_t<T>*a)noexcept{
	if constexpr(::std::is_convertible_v<T*,cons_t<T>*>)
		return static_cast<T*>(a);
	else return&T::cast_from_cons(a);//two
}
template<class T>
struct cons_t:base_cons{
	using base_cons::base_cons;
	~cons_t()noexcept{remove_from_list();}
	[[nodiscard]]T*get_before()noexcept{return un_cons_cast(static_cast<cons_t*>(base_cons::get_before()));}
	[[nodiscard]]T*get_next()noexcept{return un_cons_cast(static_cast<cons_t*>(base_cons::get_next()));}
	void set_next(T*a)noexcept{base_cons::set_next(cons_cast(a));}
	void set_before(T*a)noexcept{base_cons::set_before(cons_cast(a));}
	void next_insert(T*a)noexcept{base_cons::next_insert(cons_cast(a));}
	void before_insert(T*a)noexcept{base_cons::before_insert(cons_cast(a));}
	void bind_with(T*a)noexcept{base_cons::bind_with(cons_cast(a));}
};
template<class T>
struct list_t:base_list{
	typedef cons_t<T> cons;
	struct iterator{
		T*value;
		iterator()noexcept=default;
		iterator(T*a)noexcept:value(a){}
		bool operator==(T*a)const noexcept{return value==a;}
		bool operator!=(T*a)const noexcept{return!operator==(a);}
		iterator&operator=(T*a)&noexcept{value=a;return*this;}
		iterator&operator++()&noexcept{return*this=cons_cast(value)->get_next();}
		iterator&operator--()&noexcept{return*this=cons_cast(value)->get_before();}
		iterator operator++(int)&noexcept{auto a=*this;operator++();return a;}
		iterator operator--(int)&noexcept{auto a=*this;operator--();return a;}
		T*operator->()noexcept{return value;}
		T&operator*()noexcept{return*operator->();}
		operator T*()noexcept{return operator->();}
	};
	using base_list::base_list;
	inline void add(cons*a)noexcept{base_list::add(a);}
	inline void add(T*a)noexcept{base_list::add(cons_cast(a));}
private:
	inline T*transform(base_list::iterator a)noexcept{return un_cons_cast(static_cast<cons*>(a.value));}
public:
	[[nodiscard]]iterator begin()noexcept{return transform(base_list::begin());}
	[[nodiscard]]iterator end()noexcept{return transform(base_list::end());}
	[[nodiscard]]iterator head()noexcept{return transform(base_list::head());}
};
