//pools.hpp
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
//因为需要对两个pool相关于特殊值的的构造与析构顺序进行规定，所以取消变量模板memory::pool 
extern inline memory::pool_t<core::node,2048>node_pool;
extern inline memory::pool_t<core::member,4096>member_pool;

//因为cons数目较多，所以member pool的mentsize设为node pool的二倍 

template<typename...args>
[[nodiscard]]inline comn_ptr make_node(args&&...rest)//{auto a=node_pool.get_new(::std::forward<args>(rest)...);stest_eventlog(a);return a;}/*
{return comn_ptr(node_pool.get_new(::std::forward<args>(rest)...));}//*/

template<typename...args>
[[nodiscard]]inline comn_ppr make_member(args&&...rest)//{auto a=member_pool.get_new(::std::forward<args>(rest)...);stest_eventlog(a);return a;}/*
{return comn_ppr(member_pool.get_new(::std::forward<args>(rest)...));}//*/
//辣鸡cpp20
