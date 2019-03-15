#### envy  
提供于文件[`<elc/envy>`](./index.md)  

> 这不是类型，是特殊值  


1. 此特殊值不可复制构造、不可移动构造  
2. 此特殊值可隐式转换至任意可默认构造类型  
	 1. 若目标类型是`elc::xxxx_ptr`，其值等价于`xxxx_ptr(make_node())`   
	 2. 若目标类型是`elc::xxxx_ppr`，其值等价于`xxxx_ppr(make_member())`   
	 3. 否则，其值等价于目标类型的默认构造  
3. 此特殊值可与大部分类型比较  
4. 若比较不为病式，则一定不相等  
5. 若`bool(elc::envy > x)`不为病式，其值恒为`true`，其中`x`可为任意类型任意值  
6. 若`bool(elc::envy < x)`不为病式，其值恒为`false`，其中`x`可为任意类型任意值  


示例：
````c++
//？
#include<elc/envy>
#include<iostream>//cout
#include<cmath>//使用INFINITY
bool fun(bool a){return!a;}
int main(){
	using elc::envy;
	if(envy > INFINITY)//规则5
		if(envy != envy)//规则4
			if(!(envy < envy))//规则6
				if(fun(envy))//规则2.3，等价于fun(false)
					std::cout<<"-1s";
}
````
