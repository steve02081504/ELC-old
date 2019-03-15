#### node  
提供于文件[`<elc/core>`](./index.md)  
如同`array<std::byte>`与`array<comn_ppr>`的复合  

______

如此制造[`node`](./node.md)实例是未定义行为：  
````c++
node a;
comn_ptr b=new node;
````
应当通过[`make_node`](./make_node.md)构造新[`node`](./node.md)，这是唯一保证不会出错的方法。  

______

此类有成员函数：  
````c++
[[nodiscard]]setter type()noexcept;
[[nodiscard]]eluint get_size()const noexcept;
void for_each(void mapper(comn_ppr&));
void for_each(void mapper(comn_ppr&)noexcept)noexcept;

[[nodiscard]]setter arec(eluint a)noexcept;
[[nodiscard]]setter nocheck_arec(eluint a)noexcept;

[[nodiscard]]virtual ref_setter get_ref(eluint a)noexcept;
[[nodiscard]]virtual ref_setter get_type_ref()noexcept;

virtual void resize(eluint nsize)often_noexcept;
virtual void data_resize(eluint nsize)often_noexcept;
[[nodiscard]]std::byte* get_data()noexcept;
template<class T>[[nodiscard]]inline T& get_data_as()noexcept;
[[nodiscard]]eluint get_data_size()noexcept;

virtual void destory()often_noexcept;
[[nodiscard]]virtual constexpr explicit operator bool()noexcept;
````
这些成员函数文档在此：  
- [`type`](./node/type.md)  
- [`get_size`](./node/get_size.md)  
- [for_each](./node/for_each.md)  
- [arec](./node/arec.md)  
- [nocheck_arec](./node/nocheck_arec.md)  
- [get_ref](./node/get_ref.md)  
- [get_type_ref](./node/get_type_ref.md)  
- [resize](./node/resize.md)  
- [data_resize](./node/data_resize.md)  
- [`get_data`](./node/get_data.md)  
- [`get_data_as`](./node/get_data_as.md)  
- [`get_data_size`](./node/get_data_size.md)  
- [`destory`](./node/destory.md)  
- [`operator bool`](./node/operator-bool.md)  

  

