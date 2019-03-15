#### is_fail  
提供于文件[`<elc/helpers>`](./index.md)  
````c++
[[nodiscard]]inline bool is_fail(comn_ptr a)noexcept{return a==&elc::fail;}
````
更加可读地判断参数是否为特殊值[`fail`](../core/fail.md)  
