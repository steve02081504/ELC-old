//export.hpp
//at namespace elc
/*
未完成的elc解释器core文件
由steve02081504与Alex0125设计、编写
转载时请在不对此文件做任何修改的同时注明出处
项目地址：https://github.com/steve02081504/ELC

注意：
	本文件可能使用了cpp20的新支持或语义，而某些编译器可能并没有支持
	同时，此项目并没有完成
*/
#define export using core::
export t;
export nil;
export fail;
export eval;
export comn_ptr;
export safe_ptr;
export weak_ptr;
export comn_ppr;
export safe_ppr;
export node;
export member;
export setter;
export ref_setter;
export jmp;
export delay_jmp;
export make_node;
export make_member;
export the_size_type_usually_has;
export the_size_virtual_node_usually_has; 
#undef export
