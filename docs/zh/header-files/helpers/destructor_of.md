#### destructor_of  
提供于文件[`<elc/helpers>`](./index.md)  
````c++
[[nodiscard]]inline setter destructor_of(comn_ptr a){return setter(a->type()->arec(0));}
````
返回与被传入[`comn_ptr`](../core/comn_ptr.md)指向的[`node`](../core/node.md)的[elc层面的析构函数](../../concept/node/destructor.md)关联的[`setter`](../core/setter.md)   
此函数会在被传入[`comn_ptr`](../core/comn_ptr.md)指向的[`node`](../core/node.md)被[`destory`](../core/node/destory.md)时被调用   

