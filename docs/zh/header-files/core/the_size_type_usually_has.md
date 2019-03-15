#### the_size_type_usually_has  
提供于文件[`<elc/core>`](./index.md)  
````c++
constexpr eluint the_size_type_usually_has=3;
````
保证以`make_node(the_size_type_usually_has)`的返回值作为[类型](../../concept/node/type.md)的[`node`](./node.md)被[`destructor_of`](../helpers/destructor_of.md)、[`call_of`](../helpers/call_of.md)、[`eval_of`](../helpers/eval_of.md)
调用，返回的[`setter`](./setter.md)之间不会出现链接于同一个[`member`](./member.md)的情况   
