#### safe_ppr  
提供于文件[`<elc/core>`](./index.md)  
派生于[`comn_ppr`](./comn_ppr.md)  

______

保证以`std::nullptr_t`或[`member`](./member.md)指针或可转化为[`comn_ppr`](./comn_ppr.md)、[`weak_ptr`](./weak_ptr.md)的类型为参数进行构造、赋值、比较不为病式，其中`std::nullptr_t`将等价于[`nil.member`](./nil.md#member)的地址  
与[`comn_ppr`](./comn_ppr.md)的不同之处在于[gc](../base/gc.md)时，通过[`safe_ppr`](./safe_ppr.md)可达的[`node`](./node.md)不会被[`destory`](./member/destory.md)   

______

注意：因为[gc](../base/gc.md)时只回收[`node`](./node.md)，所以即使使用[`comn_ppr`](./comn_ppr.md)也可以保证被指向的[`member`](./member.md)不会被回收，但被指向的[`member`](./member.md)指向的[`node`](./node.md)的安全性则得不到保证  
默认初始化等价于以`nullptr`初始化   

