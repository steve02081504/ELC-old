#### is_false  
提供于文件[`<elc/helpers>`](./index.md)  
````c++
[[nodiscard]]inline bool is_false(comn_ptr a)noexcept{return !is_true(a);}
````
更加可读地判断参数是否于逻辑上为假  

________

不应使用`a==&nil`替代此判断，因为若`a==&fail`，也会在逻辑上等价于假  
使用`a==nullptr`替代此判断是安全的  
