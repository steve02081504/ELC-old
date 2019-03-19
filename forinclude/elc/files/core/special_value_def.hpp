//special_value_def.hpp
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
namespace special_value_n{
	template<bool logically_equivalent_to_this_value>
	struct special_value:node,non_copyable,non_moveable{
		constexpr special_value()noexcept:node(special_init){}
		~special_value()noexcept=default;
		[[nodiscard]]constexpr explicit operator bool()noexcept override final
		{return logically_equivalent_to_this_value;}
	};
	template class special_value<false>;
	template class special_value<true>;

	struct fail_t final:special_value<false>{
		core::member member;
		typedef exception_n::fail_error error;
	private:
		friend type_info<comn_ppr>;
		comn_ppr to_fail_member=&member;
		struct fail_member_t final:member::base_member{
			~fail_member_t()noexcept override final=default;
			[[nodiscard]]comn_ptr access()noexcept override final{return get_fail_address();}
			[[noreturn]] void set(comn_ptr)override final{throw error();}
			[[noreturn]] void to_weak()override final{throw error();}
			[[noreturn]] void un_weak()override final{throw error();}
			[[noreturn]] void to_virtual()override final{throw error();}
			[[noreturn]] void un_virtual()override final{throw error();}
			[[nodiscard]]comn_ptr get_crude_value()noexcept override final{return get_fail_address();}
		};
	public:
		fail_t(i_know_what_i_do_t)noexcept:member(special_init,type_pack<fail_member_t>){
			base_node::type_data.activation(&member);
			base_node::activable_circulate_array<comn_ppr,eluint>::special_activation(1,&to_fail_member);
			base_node::activable_array<byte,eluint>::activation();
		}
		~fail_t()noexcept{
			base_node::type_data.inactivation();
			base_node::activable_circulate_array<comn_ppr,eluint>::special_inactivation();
			base_node::activable_array<byte,eluint>::inactivation();
		}
		[[noreturn]] void resize(eluint)override final{throw error();}
		[[noreturn]] void data_resize(eluint)override final{throw error();}
		[[noreturn]] void destory()override final{throw error();}

		[[noreturn]] static void for_get_ref(comn_ppr*,comn_ppr){throw error();}
		[[nodiscard]]ref_setter get_ref(eluint a)noexcept override final{return ref_setter(i_know_what_i_do,nullptr,for_get_ref);}
		[[nodiscard]]ref_setter get_type_ref()noexcept override final{return ref_setter(i_know_what_i_do,nullptr,for_get_ref);}
	};
	struct nil_t final:special_value<false>{
		core::member member;
	private:
		comn_ppr to_nil_member=&member;
		struct nil_member_t final:member::base_member{
			~nil_member_t()noexcept override final=default;
			[[nodiscard]]comn_ptr access()noexcept override final{return get_nil_address();}
			void set(comn_ptr)noexcept override final{}
			void to_weak()noexcept override final{}
			void un_weak()noexcept override final{}
			void to_virtual()noexcept override final{}
			void un_virtual()noexcept override final{}
			[[nodiscard]]comn_ptr get_crude_value()noexcept override final{return get_fail_address();}
		};
	public:
		nil_t(i_know_what_i_do_t)noexcept:member(special_init,type_pack<nil_member_t>){
			base_node::type_data.activation(&member);
			base_node::activable_circulate_array<comn_ppr,eluint>::special_activation(1,&to_nil_member);
			base_node::activable_array<byte,eluint>::activation();
		}
		~nil_t()noexcept{
			base_node::type_data.inactivation();
			base_node::activable_circulate_array<comn_ppr,eluint>::special_inactivation();
			base_node::activable_array<byte,eluint>::inactivation();
		}
		void resize(eluint)noexcept override final{}
		void data_resize(eluint)noexcept override final{}
		void destory()noexcept override final{}

		static void for_get_ref(comn_ppr*,comn_ppr)noexcept{}
		[[nodiscard]]ref_setter get_ref(eluint a)noexcept override final{return ref_setter(i_know_what_i_do,nullptr,for_get_ref);}
		[[nodiscard]]ref_setter get_type_ref()noexcept override final{return ref_setter(i_know_what_i_do,nullptr,for_get_ref);}
	};
	struct t_t final:special_value<true>{
		t_t(i_know_what_i_do_t)noexcept{node::activation();}
		~t_t()noexcept{node::inactivation();}

		[[noreturn]] void destory()override final{::std::exit(0);}
	private:
		friend void memory::gc()noexcept;
		void mark_all_can_access()noexcept{node::for_each([](comn_ppr&a)noexcept{call_gc(*a);});}
	};
}
//因为析构顺序，在这里补充定义（而非声明）
inline decltype(member_pool) member_pool;
//特殊值t依赖于member_pool，所以member_pool先于t定义

#if defined(STEST_ED)
	inline struct member_numer{~member_numer(){
		member_pool.for_each([](member&a)noexcept{
			stest_putsf("有一个未释放的member,引用计数%zu,地址%p，其构建时事件记录如下：",a.link_num(),&a);
			stest_printeventlist(stdout,stest_geteventlistfromlog(&a));
		});
		stest_eventclear();
		stest_eventlogclear();
	}}there_was_a_shit_bug;
#endif

#define defspecialvalue(a) \
namespace special_value_n{inline a##_t a(i_know_what_i_do);}\
constexpr node*get_##a##_address()noexcept{return&special_value_n::a;}\
using special_value_n::a

defspecialvalue(fail);
defspecialvalue(nil);
defspecialvalue(t);

#undef defspecialvalue
//继续
inline decltype(node_pool) node_pool;
//之所以不在node_pool析构时遍历是因为后一ment的node析构时可能访问前一ment的node，而那是早已被释放了的
inline struct defore_node_pool_destruct_do_t{
	~defore_node_pool_destruct_do_t()noexcept{
		t.resize(zero);
		t.get_type_ref()=&nil.member;
		//通过对t的操作达到最大化析构调用
		#if defined(STEST_ED)
			gc();
			node_pool.for_each([](node&a)noexcept{
				stest_putsf("有一个未释放的node,强引用计数%zu,地址%p。",a.link_num(),&a);
				stest(is_nil(comn_ptr(&a)));
				puts("其构建时事件记录如下：");
				stest_printeventlist(stdout,stest_geteventlistfromlog(&a));
			});
		#endif
		node_pool.for_each([](node&a)noexcept{a.call_destructor();});
		//保证析构函数调用
		node_pool.for_each([](node&a)noexcept{a.none_destructor_call_destory();});
		//无序地对仍然存在的node析构
	}
}defore_node_pool_destruct_do;

BREAK_NAMESPACE
template<>constexpr core::node* base::type_info<core::node>::null_p()noexcept{return&core::nil;}
template<>constexpr core::member* base::type_info<core::member>::null_p()noexcept{return&core::nil.member;}

template<>constexpr core::comn_ppr* base::type_info<core::comn_ppr>::fail_p()noexcept{return&core::fail.to_fail_member;}
INTER_NAMESPACE(core)