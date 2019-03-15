#### t 
提供于文件[`<elc/core>`](./index.md)  
特殊值t  
不保证`decltype(t)`一定为类[`node`](./node.md)，但`node*t_p=&t;`不为病式，且除以下情况外：  
- `t_p->destory();`等价于`std::exit(0);`  

对于`t_p`可如指向普通[`node`](./node.md)的指针使用  
