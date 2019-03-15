#### node的析构函数  
如同cpp内所有的类都有析构函数，[`node`](../../header-files/core/node.md)也是如此   
通过[`destructor_of`](../../header-files/helpers/destructor_of.md)函数获取或设置[`node`](../../header-files/core/node.md)的析构函数，如  
````c++
auto a=make_node();
a->type()=make_node(the_size_type_usually_has);
destructor_of(a)=make_node_by_function([](){std::cout<<"???"<<std::endl;});
````
若`cout`正常工作，这会令`a`所指的[`node`](../../header-files/core/node.md)在[`destory`](../../header-files/core/node/destory.md)时输出`???`  
  
 <a href="javascript:history.go(-1)">返回上一页</a>  

________________

应当注意的是，析构函数中抛出的异常会被忽略  
详见[`destory`](../../header-files/core/node/destory.md)  

