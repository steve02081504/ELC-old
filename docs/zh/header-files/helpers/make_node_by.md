#### make_node_by  
提供于文件[`<elc/helpers>`](./index.md)  
更加可读的构造有数据节点
````c++ 
template<class T,class...args,class=enable_if_t<std::is_constructible_v<T,args...>>>
[[nodiscard]]inline comn_ptr make_node_by(args&&...rest)
noexcept(std::is_nothrow_constructible_v<T,args...>);
````
构造一[`node`](../core/node.md)，之后以参数于已构造[`node`](../core/node.md)的[数据段](../../concept/node/data.md)构造T类型对象  
  
保证返回[`node`](../core/node.md)的[`type`](../core/node/type.md)指向大小为[`the_size_type_usually_has`](../core/the_size_type_usually_has.md)的新构造[`node`](../core/node.md)  
  
注意：若`std::is_trivially_destructible_v<T>`为`false`，则保证在返回的[`node`](../core/node.md)的[析构函数](../../concept/node/destructor.md)不被修改的前提下，保证在此[`node`](../core/node.md)被[`destory`](../core/node/destory.md)时，调用数据段对象的析构函数  
  
________________

相关函数：[`get_data_as`](../core/node/get_data_as.md)  
