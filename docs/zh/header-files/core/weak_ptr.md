#### weak_ptr  
提供于文件[`<elc/core>`](./index.md)  
如同`std::weak_ptr<node>`，以智能指针的形式包装指向[`node`](./node.md)的指针  
但将[`weak_ptr`](./weak_ptr.md)与`std::weak_ptr<node>`混合使用效果是未定义的   

______

提供以下成员函数：  
````c++
[[nodiscard]]node*get()const noexcept;

node*operator->()const noexcept{return get();}
[[nodiscard]]node&operator*()const noexcept{return*get();}
[[nodiscard]]explicit operator node*()const noexcept{return get();}
````
其中get返回指向[`node`](./node.md)的原始指针   

______

保证以`std::nullptr_t`或[`node`](./node.md)指针或可转化为[`comn_ptr`](./comn_ptr.md)、[`weak_ptr`](./weak_ptr.md)的类型为参数进行构造、赋值、比较不为病式，除比较外`std::nullptr_t`将等价于[`nil`](./nil.md)的地址  
当其被指向的[`node`](./node.md)被回收时，其会自动指向[`nil`](./nil.md)  
默认初始化等价于以`nullptr`初始化   

