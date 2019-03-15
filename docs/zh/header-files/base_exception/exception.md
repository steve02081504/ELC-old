#### exception  
提供于文件[`<elc/base_exception>`](./index.md)  
不确保此类是否派生于`std::exception`  
确保有成员函数：  
````c++
virtual ~base_exception()noexcept=0;
virtual const char*what()noexcept;
````
派生类：
- [`fail_error`](../core/fail_error.md)  
- [`jmp_error`](../core/jmp_error.md)  
