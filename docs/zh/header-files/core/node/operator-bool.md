#### operator bool  
提供于文件[`<elc/core>`](../index.md)  
类[`node`](../node.md)的成员函数   
````c++
[[nodiscard]]virtual constexpr explicit operator bool()noexcept;
````
默认返回`true`  
对于[`fail`](../fail.md)与[`nil`](../nil.md)，返回`false`  
