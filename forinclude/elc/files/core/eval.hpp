//eval.hpp
/*
未完成的elc解释器core文件
由steve02081504与Alex0125设计、编写
转载时请在不对此文件做任何修改的同时注明出处
项目地址：https://github.com/steve02081504/ELC

注意：
	本文件可能使用了cpp20的新支持或语义，而某些编译器可能并没有支持
	同时，此项目并没有完成
*/
namespace eval_n{
	inline void set_args(comn_ptr toset,comn_ptr arg){
		comn_ppr tmp;
		while(is_true(toset)&&is_true(arg)){
			car(toset)=pop(arg);
			tmp=comn_ppr(cdr(toset));
			if(is_false(toset=tmp->access())){
				tmp->set(arg);
				break;
			}
		}
		while(is_true(toset)){
			pop(toset)=&nil;
		}
	}
	inline setter eval(safe_ptr expr){
	//	stest_entryevent("in eval");
	//	struct tmp_{~tmp_(){stest_exitevent();}}tmp__;
		safe_ptr&func=expr;
		safe_ptr arglist;
	begin:
		if(is_cons(expr)){
			arglist=cdr(expr);
			func=car(expr);
		}else{
			arglist=cons(expr,&nil);
			func=eval_of(expr);
		}
		while(1){
			if(is_elfunc(func)){
				pop(func);//remove t
				set_args(car(func),arglist);
				pop(func);//remove arglist set space
				safe_ppr aret;
				safe_ptr&to_eval=arglist; 
		retry:	try{
					while(1){
						to_eval=pop(func);
						if(is_true(func))[[likely]]{//不是最后一个表达式
							aret=comn_ppr(eval(to_eval));
						}else[[unlikely]]{
							//得到函数的最后一个表达式，其返回值为函数返回值
							expr=to_eval;
							goto begin;//尾调用优化
						}
					}
				}catch(jmp_t&a){
					if(a.delaying){a.undelay();throw;}
					if(is_false(a.to))return setter(aret);
					func=a.to;
					goto retry;
				}
			}else if(is_bottom_func(func)||is_false(func))
				return setter(get_bottom_function(func).call(arglist));
			else{
				push(arglist,func);
				func=call_of(func);
			}
		}
	}
}
using eval_n::eval;
