#### comn_ppr  
提供于文件[`<elc/core>`](./index.md)  
如同`std::shared_ptr<member>`，以智能指针的形式包装指向[`member`](./member.md)的指针  
但将[`comn_ppr`](./comn_ppr.md)与`std::shared_ptr<member>`混合使用效果是未定义的  

______
 
提供以下成员函数：  
````c++
[[nodiscard]]member*get()const noexcept;

member*operator->()const noexcept{return get();}
[[nodiscard]]member&operator*()const noexcept{return*get();}
[[nodiscard]]explicit operator member*()const noexcept{return get();}
````
其中get返回指向[`member`](./member.md)的原始指针   

______

保证以`std::nullptr_t`或[`member`](./member.md)指针或可转化为[`comn_ppr`](./comn_ppr.md)的类型为参数进行构造、赋值、比较不为病式，其中`std::nullptr_t`将等价于[`nil.member`](./nil.md#member)的地址  
与[`safe_ppr`](./safe_ppr.md)的不同之处在于[gc](../base/gc.md)时，通过[`safe_ppr`](./safe_ppr.md)可达的[`node`](./node.md)不会被[`destory`](./member/destory.md)   
注意：因为[gc](../base/gc.md)时只回收[`node`](./node.md)，所以即使使用[`comn_ppr`](./comn_ppr.md)也可以保证被指向的[`member`](./member.md)不会被回收，但[`member`](./member.md)指向的[`node`](./node.md)的安全性则得不到保证  
默认初始化等价于以`nullptr`初始化   

