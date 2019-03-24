//body.hpp
//at namespace ::
/*
未完成的elc解释器base文件
由steve02081504与Alex0125设计、编写
转载时请在不对此文件做任何修改的同时注明出处
项目地址：https://github.com/steve02081504/ELC

注意：
	本文件可能使用了cpp20的新支持或语义，而某些编译器可能并没有支持
	同时，此项目并没有完成
*/
namespace elc{
	#include"defs.hpp"
	namespace memory{
		#include"gc_decl.hpp"//基础声明
	}
	namespace base{
		#include"base.hpp"//几个typedef
		#include"concept.hpp"//杂项
	}
	namespace memory{
		using namespace base;
		#include"alloc.hpp"//分配包装函数
		//#include"memtools.hpp"//内存操作工具
		#include"pool.hpp"//内存池
	}
	namespace base{
		#include"ptr.hpp"//引用计数指针
		#include"array.hpp"//数组容器定义
	}
	#include"export.hpp"
	#include"undefs.hpp"
}
