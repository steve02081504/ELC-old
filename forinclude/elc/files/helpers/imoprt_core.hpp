//imoprt_core.hpp
//at namespace elc
/*
未完成的elc解释器helpers文件
由steve02081504与Alex0125设计、编写
转载时请在不对此文件做任何修改的同时注明出处
项目地址：https://github.com/steve02081504/ELC

注意：
	本文件可能使用了cpp20的新支持或语义，而某些编译器可能并没有支持
	同时，此项目并没有完成
*/
#define import using core::
import function_info;
import car;
import cdr;
import cons;
import list;
import make_node_by_function;
import make_node_by;
import is_cons;
import destructor_of;
import call_of;
import eval_of;
import is_elfunc;
import is_bottom_func;
import pop;
import push;
import is_true;
import is_false;
import is_t;
import is_nil;
import is_fail;
#undef import
