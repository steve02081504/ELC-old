#### is_nil  
提供于文件[`<elc/helpers>`](./index.md)  
````c++
[[nodiscard]]inline bool is_nil(comn_ptr a)noexcept{return a==&elc::nil;}
````
更加可读地判断参数是否为特殊值[`nil`](../core/nil.md)  
