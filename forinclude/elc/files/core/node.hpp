//node.hpp
//at namespace elc::core
/*
未完成的elc解释器core文件
由steve02081504与Alex0125设计、编写
转载时请在不对此文件做任何修改的同时注明出处
项目地址：https://github.com/steve02081504/ELC

注意：
	本文件可能使用了cpp20的新支持或语义，而某些编译器可能并没有支持
	同时，此项目并没有完成
*/
struct base_node:non_copyable,non_moveable,
activable_circulate_array<comn_ppr,eluint>,activable_array<byte,eluint>
{
	friend base::type_info<core::node>;
protected:
	data_t<comn_ppr>type_data;
private:
	flag destoryed;
public:
	typedef activable_circulate_array<comn_ppr,eluint> base_t;
	typedef activable_array<byte,eluint> data_array_t;
	constexpr base_node()noexcept=default;
	[[nodiscard]]setter type()noexcept{return setter(*type_data.get());}
protected:
	void activation(eluint size,safe_ppr type,eluint data_size=0)noexcept{
	//	stest_entryevent("type construct");
		type_data.activation(type);
	//	stest_exitevent();
	//	stest_entryevent("common member construct");
		base_t::activation(size);
	//	stest_exitevent();
		data_array_t::activation(data_size);
		destoryed.unset();
	}
	void activation(eluint size=0)noexcept{
	//	stest_entryevent("type construct");
		type_data.activation(make_member());
	//	stest_exitevent();
	//	stest_entryevent("common member construct");
		base_t::activation(size);
	//	stest_exitevent();
		data_array_t::activation();
		destoryed.unset();
	}
	void inactivation()noexcept{
		destoryed.set();
		type_data.inactivation();
		base_t::inactivation();
		data_array_t::inactivation();
	}
	void base_destory()noexcept{
		if(destoryed)return;
		inactivation();
	}
};

struct node:non_copyable,non_moveable,
safe_ref_able<node>,weak_ref_able<node>,base_node,mark_able
{
protected:
	using base_node::activation;
	using base_node::inactivation;
	explicit constexpr node(special_init_t)noexcept:safe_ref_able<node>(never_ref_num_zero),mark_able(marked){}
private:
	flag destructor_called;
	void no_link()noexcept{node_pool.use_end(this);}//对于非comn_node，已保证never_ref_num_zero。

	friend ref_able<node>;
	void ref_num_is_zero()noexcept{destory();if(!has_weak_link())no_link();}
	friend weak_ref_able<node>;
	void weak_ref_num_is_zero()noexcept{if(!has_link())no_link();}

	friend safe_ref_able<node>;
	void gc_method()noexcept{
		if(was_marked())return;//对于非comn_node，已保证marked
		mark();
		base_t::for_each([](comn_ppr&a)noexcept{call_gc(*a);});
	}

	friend decltype(node_pool)::friend_t;
//for pool.
	explicit node(just_init_flag_t)noexcept{}//隐式调用(weak_)ref_able的默认构造函数
	bool was_using()noexcept{return has_link()||has_weak_link();}
	void start_using(eluint size=0)noexcept{destructor_called.unset();activation(size);}
	void start_using(eluint size,safe_ppr type,eluint data_size=0)noexcept{destructor_called.unset();activation(size,type,data_size);}
	void call_destructor()noexcept{
/*
原九度凋(steve_green@qq.com)  21:47:21
[图片]
内核完工了
alex<alex-jas-de-brad@qq.com>  21:48:55
https://github.com/steve02081504/elc-rebuilding/blob/master/files/core/node.hpp#L92

原九度凋(steve_green@qq.com)  21:49:04
？
alex<alex-jas-de-brad@qq.com>  21:49:41
析构递归.
原九度凋(steve_green@qq.com)  21:50:05
。。。。？
alex<alex-jas-de-brad@qq.com>  21:52:27
https://github.com/steve02081504/ELC/blob/master/files/core/elc/atomdef.hpp#L146

原九度凋(steve_green@qq.com)  21:52:38
[图片]？？？？？？
alex<alex-jas-de-brad@qq.com>  21:52:56
.....
list.
构建cons.
cons,析构.
原九度凋(steve_green@qq.com)  21:53:37
[图片]
哦我想起来了
alex<alex-jas-de-brad@qq.com>  21:54:06
√
原九度凋(steve_green@qq.com)  21:54:58
咋整
alex<alex-jas-de-brad@qq.com>  21:55:04
.....
alex<alex-jas-de-brad@qq.com>  21:58:01
if(is_nil(destructor_of(this)))then
	destructor_of(this)(this)
原九度凋(steve_green@qq.com)  21:58:29
[图片]好麻烦
alex<alex-jas-de-brad@qq.com>  21:59:12
最简单的方法了.....
原九度凋(steve_green@qq.com)  21:59:35
[图片]
原九度凋(steve_green@qq.com)  22:06:23
[图片]
。。。。。。
怎么有点怪
alex<alex-jas-de-brad@qq.com>  22:06:47
.....
(注意到了就改过来啊混蛋.)
原九度凋(steve_green@qq.com)  22:07:38
[图片]
*/
		if(destructor_called)return;
		destructor_called.set();
		try{
			comn_ptr tmp=destructor_of(this);//确保只访问一次
			if(!is_false(tmp))eval(list(tmp,this));
		}catch(...){
			//?
		}
	}

	friend class defore_node_pool_destruct_do_t;
	void none_destructor_call_destory()noexcept{
		base_destory();
	}
public:
	~node()noexcept=default;
	using base_t::for_each;
	using base_t::get_size;

	[[nodiscard]]setter arec(eluint a)noexcept{return setter(base_t::arec(a));}
	[[nodiscard]]setter nocheck_arec(eluint a)noexcept{return setter(base_t::nocheck_arec(a));}

	[[nodiscard]]virtual ref_setter get_ref(eluint a)noexcept{return ref_setter(i_know_what_i_do,&base_t::arec(a));}
	[[nodiscard]]virtual ref_setter get_type_ref()noexcept{return ref_setter(i_know_what_i_do,type_data.get());}

	virtual void resize(eluint nsize)often_noexcept{base_t::resize(nsize);}
	virtual void data_resize(eluint nsize)often_noexcept{data_array_t::resize(nsize);}
	[[nodiscard]]byte*get_data()noexcept{return data_array_t::get_begin_addres();}
	template<class T>
	[[nodiscard]]inline T&get_data_as()noexcept{return data_cast<T>(get_data());}
	[[nodiscard]]eluint get_data_size()noexcept{return data_array_t::get_size();}

	virtual void destory()often_noexcept{
		call_destructor();
		base_destory();
	}
	virtual constexpr explicit operator bool()noexcept{return true;}
	constexpr node*operator&()noexcept{return this;}
};

BREAK_NAMESPACE
template<>inline void base::type_info<core::comn_ppr>::initer(core::comn_ppr*a)noexcept{
	new(a)core::comn_ppr(core::make_member());
}

template<>inline bool base::type_info<core::node>::ptr_to_bool_converter(core::node*a)noexcept{
	return a->operator bool();
}
template<>inline bool base::type_info<core::node>::ptr_checker(core::node*a)noexcept{
	return bool(a->destoryed);
}
INTER_NAMESPACE(core)
