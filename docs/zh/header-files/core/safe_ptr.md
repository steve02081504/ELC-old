#### safe_ptr  
提供于文件[`<elc/core>`](./index.md)  
派生于[`comn_ptr`](./comn_ptr.md)  

______

保证以`std::nullptr_t`或[`node`](./node.md)指针或可转化为[`comn_ptr`](./comn_ptr.md)、[`weak_ptr`](./weak_ptr.md)的类型为参数进行构造、赋值、比较不为病式，除比较外`std::nullptr_t`将等价于[`nil`](./nil.md)的地址  
与[`comn_ptr`](./comn_ptr.md)的不同之处在于[gc](../base/gc.md)时，通过[`safe_ptr`](./safe_ptr.md)可达的[`node`](./node.md)不会被[`destory`](./node/destory.md)  
默认初始化等价于以`nullptr`初始化   

