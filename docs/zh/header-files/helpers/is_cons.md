#### is_cons  
提供于文件[`<elc/helpers>`](./index.md)  
````c++
[[nodiscard]]inline bool is_cons(comn_ptr a){return is_nil(a->type());}
````
更加可读地判断参数是否为cons  

