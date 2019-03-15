#### fail  
提供于文件[`<elc/core>`](./index.md)  
特殊值fail  

______

不保证`decltype(fail)`一定为类[`node`](./node.md)，但`node*fail_p=&fail;`不为病式，且除以下情况外：  
- `fail_p->destory();`抛出[`fail_error`](./fail_error.md)  
- `fail_p->resize(num);`抛出[`fail_error`](./fail_error.md)  
- `fail_p->data_resize(num);`抛出[`fail_error`](./fail_error.md)  
- `fail_p->get_ref(num)=some_other;`抛出[`fail_error`](./fail_error.md)  
- `fail_p->arec(num)`返回的[`setter`](./setter.md)绑定于[`fail.member`](#member)   
- `bool(*fail_p)`为`false`  

对于`fail_p`可如指向普通[`node`](./node.md)的指针使用  

______

<p id = "member"></p>
对于`fail.member`，不保证`decltype(fail.member)`一定为类[`member`](./member.md)，但`member*fail_m_p=&fail.member;`不为病式，且除以下情况外： 
- `fail_m_p->set(sth);`抛出[`fail_error`](./fail_error.md)  
- `fail_m_p->access();`返回指向[`fail`](./fail.md)的[`comn_ptr`](./comn_ptr.md)  
- `fail_m_p->to_weak();`抛出[`fail_error`](./fail_error.md)  
- `fail_m_p->un_weak();`抛出[`fail_error`](./fail_error.md)  
- `fail_m_p->to_virtual();`抛出[`fail_error`](./fail_error.md)  
- `fail_m_p->un_virtual();`抛出[`fail_error`](./fail_error.md)  

对于`fail_m_p`可如指向普通[`member`](./member.md)的指针使用  

______

