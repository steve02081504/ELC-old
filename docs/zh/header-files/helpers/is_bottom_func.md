#### is_bottom_func  
提供于文件[`<elc/helpers>`](./index.md)  
````c++
[[nodiscard]]inline bool is_bottom_func(comn_ptr a)noexcept{return is_t(call_of(a));}
````
更加可读的判断节点是否为[副作用节点](../../concept/function.md#副作用节点)  
