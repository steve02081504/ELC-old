//make_node_by_object.hpp
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
namespace make_node_by_object_n{
	template<class T>
	inline void class_destructor(safe_ptr a)noexcept(::std::is_nothrow_destructible_v<T>)
	{car(a)->get_data_as<T>().~T();}

	template<class T,class...args,enable_if(::std::is_constructible_v<T,args...>)>
	[[nodiscard]]inline comn_ptr make_node_by(args&&...rest)
	noexcept(::std::is_nothrow_constructible_v<T,args...>){
		safe_ptr aret=make_node();
		aret->data_resize(sizeof(T));
		new(aret->get_data())T(::std::forward<args>(rest)...);
		aret->type()=make_node(the_size_type_usually_has);
		if constexpr(!::std::is_trivially_destructible_v<T>)
			destructor_of(aret)=make_node_by_function(class_destructor<T>);
		return aret;
	}
}
using make_node_by_object_n::make_node_by;
