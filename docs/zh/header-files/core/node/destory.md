#### destory  
提供于文件[`<elc/core>`](../index.md)  
类[`node`](../node.md)的成员函数   
````c++
inline virtual void destory()noexcept;
````
调用此[`node`](../node.md)的[elc层面的析构函数](../../../concept/node/destructor.md)后使此[`node`](../node.md)作废  
具体步骤如下：  
1.  调用此[`node`](../node.md)的[elc层面的析构函数](../../../concept/node/destructor.md)，若此析构函数抛出elc层面或cpp层面的异常，则忽略此异常并继续  
2.  令所有指向此[`node`](../node.md)的[`member`](../member.md)、[`comn_ptr`](../comn_ptr.md)、[`safe_ptr`](../safe_ptr.md)、[`weak_ptr`](../weak_ptr.md)指向[`nil`](../nil.md)  
3.  断开此[`node`](../node.md)与其[`member`](../member.md)间的链接  
4.  释放内存，对内存的释放大小保证不为负  

当任意[`node`](../node.md)无法被任何：非weak的[`member`](../member.md)、[`comn_ptr`](../comn_ptr.md)、[`safe_ptr`](../safe_ptr.md) 访问时，自动对此[`node`](../node.md)进行[`destory`](./destory.md)  
在析构函数中[`destory`](./destory.md)正在[`destory`](./destory.md)的[`node`](../node.md)，会令第2、3、4步先行进行。  
即，通过[`destory`](./destory.md)调用同一[`node`](../node.md)的[elc层面的析构函数](../../../concept/node/destructor.md)，保证只进行一次。  

_______

若查询释放内存方法，参见[`gc`](../../base/gc.md)  
