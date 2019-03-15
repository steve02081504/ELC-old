#### list  
提供于文件[`<elc/helpers>`](./index.md)  
````c++
[[nodiscard]]inline comn_ptr list()noexcept{return&nil;}
template<class T,class...args>
[[nodiscard]]inline comn_ptr list(T&&a,args&&...rest)noexcept{
	return cons(a,list(std::forward<args>(rest)...));
}
````
更加可读地构造列表  

