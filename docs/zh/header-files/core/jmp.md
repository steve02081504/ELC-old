#### jmp  
提供于文件[`<elc/core>`](./index.md)  
````c++
[[noreturn]] inline void jmp(comn_ptr to);
````
以参数发起一个[jmp动作](./jmp.md)，此动作引起栈回退，并且若回退至等待elc函数语句执行结果的[`eval`](./eval.md)时停止回退，
改变[`eval`](./eval.md)的后续处理列表为参数  
注意：[jmp动作](./jmp.md)的本质为扔出一个[`jmp_error`](./jmp_error.md)或派生于[`jmp_error`](./jmp_error.md)的类，
这意味着于cpp中的`catch(jmp_error)`或`catch(...)`等语句可以打断[jmp动作](./jmp.md)  
同时，[`delay_jmp`](./delay_jmp.md)函数可使[jmp动作](./jmp.md)的发作时间延后  

