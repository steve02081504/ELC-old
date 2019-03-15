#### is_elfunc  
提供于文件[`<elc/helpers>`](./index.md)  
````c++
[[nodiscard]]inline bool is_elfunc(comn_ptr a){return is_cons(a)&&is_t(car(a));}
````
更加可读的判断节点是否为[elc函数](../../concept/function.md#基础函数)  
