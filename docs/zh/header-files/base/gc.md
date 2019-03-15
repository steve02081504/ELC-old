#### gc  
提供于文件[`<elc/base>`](./index.md)  
````c++
inline void gc()noexcept;
````
通过[`destory`](../core/node/destory.md)无法被[`t`](../core/t.md)、所有的[`safe_ptr`](../core/safe_ptr.md)、所有的[`safe_ppr`](../core/safe_ppr.md)
到达的[`node`](../core/node.md)，达到释放空间的效果  
注意：当elc模块申请内存失败时会自动调用此函数，所以一般来说手动调用是不必要的  

