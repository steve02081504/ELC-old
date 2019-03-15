#### get_data_as  
提供于文件[`<elc/core>`](../index.md)  
类[`node`](../node.md)的成员函数   
````c++
template<class T>
[[nodiscard]]inline T&get_data_as()noexcept{
	return*std::launder(reinterpret_cast<T*>(get_data()));
}
````
使对[数据段](../../../concept/node/data.md)的操作更加可读  
应当注意的是，此函数不对[数据段](../../../concept/node/data.md)大小做出检查  

________

相关函数：[`make_node_by`](../../helpers/make_node_by.md)  
