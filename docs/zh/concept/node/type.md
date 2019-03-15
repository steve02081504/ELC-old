#### node的类型  
尽管所有的[`node`](../../header-files/core/node.md)都是[`node`](../../header-files/core/node.md)，但[`node`](../../header-files/core/node.md)仍然有类型信息   
通过[`type`](../../header-files/core/node/type.md)成员函数获取或设置[`node`](../../header-files/core/node.md)的类型，如  
````c++
auto a=make_node();
a->type()=make_node(the_size_type_usually_has);
````
同时，类型中有[`node`](../../header-files/core/node.md)的
[析构](./destructor.md)、[被求值](./eval.md)、[被调用](./call.md) 
方法，可以通过对应的函数进行设置  

 <a href="javascript:history.go(-1)">返回上一页</a>  
