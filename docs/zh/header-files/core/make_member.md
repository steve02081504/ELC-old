#### make_member  
提供于文件[`<elc/core>`](./index.md)  
````c++
template<typename...args>
inline comn_ppr make_member(args&&...rest);
````
保证安全的[`member`](./member.md)构造方法  

______

保证提供的变体如下：  
````c++
make_member(comn_ptr);//构造以参数为内容的，非weak、非virtual的member
make_member();//如同meak_member(&nil); 
````

