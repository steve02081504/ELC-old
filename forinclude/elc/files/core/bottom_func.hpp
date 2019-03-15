//bottom_func.hpp
/*
未完成的elc解释器core文件
由steve02081504与Alex0125设计、编写
转载时请在不对此文件做任何修改的同时注明出处
项目地址：https://github.com/steve02081504/ELC

注意：
	本文件可能使用了cpp20的新支持或语义，而某些编译器可能并没有支持
	同时，此项目并没有完成
*/
/*
alex 2019/1/11 22:46:42
都说特别重要还行.
alex 2019/1/11 22:47:06
内核有什么问题吗?
原九度凋 2019/1/11 22:47:36
底层接口
function包装器还是函数指针
alex 2019/1/11 22:48:31
小孩子才做选择题.
成年人的我全都要!
(不.)
原九度凋 2019/1/11 22:49:23
[图片]
明白了
好主意
*/
//茗世界第一可爱鸭
//（雾
namespace bottom_function_n{
	typedef ::std::uintptr_t check_t;
	constexpr check_t function_data_begin=check_t(0xE1C);//1llli1l!
	struct abstruct_bottom_function_data:non_copyable,non_moveable{
		check_t begin=function_data_begin;
		virtual ~abstruct_bottom_function_data()=0;
		virtual setter call(safe_ptr)=0;
		bool available(){return begin==function_data_begin;}
	};
	inline abstruct_bottom_function_data::~abstruct_bottom_function_data(){}
	inline struct default_bottom_function_t final:non_copyable,non_moveable,
	abstruct_bottom_function_data{
		~default_bottom_function_t()noexcept final override=default; 
		setter call(safe_ptr a)final override{return setter(car(a));}//nil
	}default_bottom_function;

	template<class T,enable_if(function_info<T>::can_call_and_can_built)>
	struct bottom_function_data final:non_copyable,non_moveable,
	abstruct_bottom_function_data{
	private:
		typename function_info<T>::data_type data;
	public:
		~bottom_function_data()noexcept(function_info<T>::can_nothrow_destruct)final override{data.inactivation();}
		bottom_function_data(typename function_info<T>::built_type a)noexcept(function_info<T>::can_nothrow_built){function_info<T>::build_up(a,data);}
		setter call(safe_ptr a)noexcept(function_info<T>::can_nothrow_call)final override
		{return setter(function_info<T>::call(*data.get(),a));}
	};

	template<class T,enable_if(function_info<T>::can_call_and_can_built)>
	[[nodiscard]]inline comn_ptr make_node_by_function(T&&a)
	noexcept(function_info<T>::can_nothrow_built){
	//	stest_entryevent("construct node by function");
		safe_ptr aret=make_node_by<bottom_function_data<T>>(::std::forward<T>(a));
		call_of(aret)=&t;
	//	stest_exitevent();
		return aret;
	}
	[[nodiscard]]inline abstruct_bottom_function_data&get_bottom_function(comn_ptr a)noexcept{
		if(a->get_data_size()<sizeof(abstruct_bottom_function_data))return default_bottom_function;
		abstruct_bottom_function_data&aret=a->get_data_as<abstruct_bottom_function_data>();
		if(aret.available())return aret;
		else return default_bottom_function;
	}
}
using bottom_function_n::get_bottom_function;
using bottom_function_n::make_node_by_function;
