#### member  
提供于文件[`<elc/core>`](./index.md)  

______

如此制造[`member`](./member.md)实例是未定义行为：  
````c++
member a;
comn_ppr b=new member;
````
应当通过[`make_member`](./make_member.md)构造新[`member`](./member.md)，这是唯一保证不会出错的方法。  

______

此类有成员函数：  
````c++
comn_ptr access();
void set(comn_ptr a);
void to_weak()noexcept;
void un_weak()noexcept;
void to_virtual()noexcept;
void un_virtual()noexcept;
````
这些成员函数文档在此：  
- [access](./member/access.md)  
- [set](./member/set.md)  
- [to_weak](./member/to_weak.md)  
- [un_weak](./member/un_weak.md)  
- [to_virtual](./member/to_virtual.md)  
- [un_virtual](./member/un_virtual.md)  
