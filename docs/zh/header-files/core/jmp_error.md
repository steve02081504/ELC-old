#### jmp_error  
提供于文件[`<elc/core>`](./index.md)  
派生于[`elc::exception`](../base_exception/exception.md)  

______

有成员函数：  
````c++ 
~jmp_error()noexcept;
const char*what()noexcept;
````
此异常多出现于在cpp中[`eval`](./eval.md)会产生[jmp动作](./jmp.md)的elc对象时  
 
