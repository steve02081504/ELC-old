#### delay_jmp  
提供于文件[`<elc/core>`](./index.md)  
````c++
inline setter delay_jmp(comn_ptr to_eval);
````
对参数[`eval`](./eval.md)，若此过程发起一个[jmp动作](./jmp.md)且回退栈至此过程的发起者（即[`delay_jmp`](./delay_jmp.md)），
使[jmp动作](./jmp.md)的发作时间延后。
即：  
于下一个等待elc函数语句执行结果的[`eval`](./eval.md)继续回退  

