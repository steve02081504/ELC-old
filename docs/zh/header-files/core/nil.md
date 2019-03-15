#### nil  
提供于文件[`<elc/core>`](./index.md)  
特殊值nil  

______

不保证`decltype(nil)`一定为类[`node`](./node.md)，但`node*nil_p=&nil;`不为病式，且除以下情况外：  
- `nil_p->destory();`无效无错  
- `nil_p->resize(num);`无效无错  
- `nil_p->data_resize(num);`无效无错  
- `nil_p->get_ref(num)=some_other;`无效无错  
- `nil_p->arec(num)`返回的[`setter`](./setter.md)绑定于[`nil.member`](#member)  
- `bool(*nil_p)`为`false`  

对于`nil_p`可如指向普通[`node`](./node.md)的指针使用  

______

<p id = "member"></p>
对于`nil.member`，不保证`decltype(nil.member)`一定为类[`member`](./member.md)，但`member*nil_m_p=&nil.member;`不为病式，且除以下情况外： 
- `nil_m_p->set(sth);`无效无错  
- `nil_m_p->access();`返回指向[`nil`](./nil.md)的[`comn_ptr`](./comn_ptr.md)  
- `nil_m_p->to_weak();`无效无错  
- `nil_m_p->un_weak();`无效无错  
- `nil_m_p->to_virtual();`无效无错  
- `nil_m_p->un_virtual();`无效无错  

对于`nil_m_p`可如指向普通[`member`](./member.md)的指针使用  

______

