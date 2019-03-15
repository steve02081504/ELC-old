#### function  
提供于文件[`<elc/function>`](./index.md)  
以一致的接口对满足[elc可调用要求](../../concept/call_request.md)的对象进行包装  
是否派生于[`comn_ptr`](../core/comn_ptr.md)是不确定的，但保证不会公开继承自[`comn_ptr`](../core/comn_ptr.md)或[`safe_ptr`](../core/safe_ptr.md)  
同时，与`std::function`不同，`elc::function`不保证进行小对象优化  

______

注意：
相比于`std::function`，我们更加建议使用`elc::function`来封装满足[elc可调用要求](../../concept/call_request.md)的对象，因为它具有更为强大的泛型能力  
同时，与`std::function`不同的是，`elc::function`为空时，对其进行调用单纯返回参数列表的第一个元素，如同调用特殊值[`nil`](../core/nil.md)  

______

此类有成员函数：  
````c++
void swap(function&a)noexcept;
function()noexcept;
~function();
function(const function&a)noexcept;
function(function&&a)noexcept;

function&operator=(const function&a)&noexcept;
function&operator=(function&&a)&noexcept;
function&operator=(comn_ptr a)&noexcept;
template<class T,class=std::enable_if_t<elc::function_info<T>::can_call_and_can_built>>
function&operator=(T&&a)&
noexcept(elc::function_info<T>::can_nothrow_built);
function&operator=(std::nullptr_t)&noexcept;

template<class...args>
setter operator()(args&&...rest)const;
setter call(safe_ptr a)const;

template<class T,class=std::enable_if_t<std::is_assignable_v<function,T>>>
function(T&&a)noexcept(std::is_nothrow_assignable_v<function,T>):function()
{operator=(a);}

comn_ptr make_node_from_this()const;

explicit operator bool()const noexcept;
````

______

以及非成员函数：  
````c++
inline void swap(elc::function&a,elc::function&b)noexcept{a.swap(b);}

inline bool operator==(const elc::function&f,std::nullptr_t)noexcept{return!bool(f);}
inline bool operator==(std::nullptr_t,const elc::function&f)noexcept{return!bool(f);}
inline bool operator!=(const elc::function&f,std::nullptr_t)noexcept{return bool(f);}
inline bool operator!=(std::nullptr_t,const elc::function&f)noexcept{return bool(f);}
````

这些成员函数定义于function所在的名称空间  

______

[`make_node_by_function`](../helpers/make_node_by_function.md)针对`elc::function`进行了重载  
````c++ 
inline comn_ptr make_node_by_function(elc::function&a){
	return a.make_node_from_this();
}
````