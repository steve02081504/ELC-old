#### make_node  
提供于文件[`<elc/core>`](./index.md)  
````c++
template<typename...args>
inline comn_ptr make_node(args&&...rest);
````
保证安全的[`node`](./node.md)构造方法  

______

保证提供的变体如下：  
````c++
make_node(eluint size,safe_ppr type,eluint data_size);//构造初始大小为size、类型为type、数据段大小为data_size的node
make_node(eluint size,safe_ppr type);//如同meak_node(size,type,0);
make_node(eluint size);//如同meak_node(size,make_member());
make_node();//如同meak_node(0);
````

