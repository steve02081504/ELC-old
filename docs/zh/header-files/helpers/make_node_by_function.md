#### make_node_by_function  
提供于文件[`<elc/helpers>`](./index.md)  
一堆函数与函数模板   
基本上如下：   
````c++ 
template< class T, bool = /*some thing*/ >
[[nodiscard]]inline comn_ptr make_node_by_function( T&& ) noexcept(/*some thing*/);
````
将多数满足[elc可调用要求](../../concept/call_request.md)的类转化为可被[`eval`](../core/eval.md)使用的副作用节点
或仅仅返回参数  
  
实际是将参数复制（或移动）至新建node的[数据段](../../concept/node/data.md)，并进行其他处理   
  
注意：若`std::is_trivially_destructible_v<T>`为`false`，则保证在返回的[`node`](../core/node.md)的[析构函数](../../concept/node/destructor.md)不被修改的前提下，保证在此[`node`](../core/node.md)被[`destory`](../core/node/destory.md)时，调用数据段对象的析构函数  

________________

详细声明如下：  
````c++ 
template<class T,class=std::enable_if_t<elc::function_info<T>::can_call_and_can_built>>
[[nodiscard]]inline comn_ptr make_node_by_function(T&&a)
noexcept(elc::function_info<T>::can_nothrow_built);

[[nodiscard]]inline comn_ptr make_node_by_function(elc::function&a){
	return a.make_node_from_this();
}
[[deprecated,nodiscard]]inline comn_ptr make_node_by_function(comn_ptr a){
	return a;
}
````
 
