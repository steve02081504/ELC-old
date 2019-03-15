//gc.hpp
/*
未完成的elc解释器core文件
由steve02081504与Alex0125设计、编写
转载时请在不对此文件做任何修改的同时注明出处
项目地址：https://github.com/steve02081504/ELC

注意：
	本文件可能使用了cpp20的新支持或语义，而某些编译器可能并没有支持
	同时，此项目并没有完成
*/
BREAK_NAMESPACE
inline void memory::gc()noexcept{
	using namespace core; 
	//mark部分
	//所有的通过所有的safe_ptr可达的node
	root_list<node>.mark_all_can_access();
	//所有的通过所有的safe_ppr可达的node
	root_list<member>.mark_all_can_access();
	//所有的通过t可达的node
	t.mark_all_can_access();
	//mark完毕
	core::node_pool.for_each([](node&a)noexcept{
		if(a.was_marked())
			a.unmark();
		else
			a.destory();
	});
	core::node_pool.shrink();
	core::member_pool.shrink();
}
INTER_NAMESPACE(core)
