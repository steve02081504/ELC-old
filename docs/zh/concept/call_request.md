#### 调用要求  
满足以下条件任意一条的类型满足elc调用要求  
- 可以以[`(safe_ptr)`](../header-files/core/safe_ptr.md)或`()`调用，并返回可转换为[`setter`](../header-files/core/setter.md)或`void`的类  
- 可转换为[`comn_ptr`](../header-files/core/comn_ptr.md)的类  

可通过[`elc::function`](../header-files/helpers/function.md)将满足此要求的类型统一接口，特殊规则如下：
- 若返回类型为`void`，则接口返回默认构造的[`setter`](../header-files/core/setter.md)  
- 若无法以[`(safe_ptr)`](../header-files/core/safe_ptr.md)调用，且能以`()`调用，接口将于实际调用后丢弃传入的参数  

若有类型有多种调用方案满足要求，则以可以以[`(safe_ptr)`](../header-files/core/safe_ptr.md)调用的方式优先的方法进行选择  

 <a href="javascript:history.go(-1)">返回上一页</a>  