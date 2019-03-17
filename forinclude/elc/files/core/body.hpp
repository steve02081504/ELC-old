//body.hpp
//at namespace ::
/*
未完成的elc解释器core文件
由steve02081504与Alex0125设计、编写
转载时请在不对此文件做任何修改的同时注明出处
项目地址：https://github.com/steve02081504/ELC

注意：
	本文件可能使用了cpp20的新支持或语义，而某些编译器可能并没有支持
	同时，此项目并没有完成
*/
//因为elc没有const语义，所以core内类不会支持const，除非迫不得已。
namespace elc{
	#include"defs.hpp"
	namespace core{
		using namespace::elc::base;
		//定义常用别名、声明特殊值
		#include"base_decl.hpp"
		//内存池声明
		#include"pools.hpp"

		//比较主要的类定义
		#include"member.hpp"
		#include"setter.hpp"
		#include"ref_setter.hpp"

		//一堆函数声明
		#include"other_decl.hpp"

		//主要类定义
		#include"node.hpp"

		//几个异常类
		#include"exceptions.hpp"

		//特殊值
		#include"special_value_def.hpp"

		//跳转
		#include"jmp.hpp"

		//从对象构建节点
		#include"make_node_by_object.hpp"

		//可调用类型信息
		#include"function_info.hpp"
		//从节点数据存取callable对象
		#include"bottom_func.hpp"


		//补充定义一些乱七八糟的东西
		#include"other_def.hpp"

		//定义特殊函数
		#include"gc.hpp"
		#include"eval.hpp"
	}
	#include"export.hpp"
	#include"undefs.hpp"
}
