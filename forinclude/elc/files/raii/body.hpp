//body.hpp
/*
未完成的elc解释器raii文件
由steve02081504与Alex0125设计、编写
转载时请在不对此文件做任何修改的同时注明出处
项目地址：https://github.com/steve02081504/ELC

注意：
	本文件可能使用了cpp20的新支持或语义，而某些编译器可能并没有支持
	同时，此项目并没有完成
*/
namespace elc{
	#include"defs.hpp"

	namespace raii{
		#include"raii_node.hpp"
	}

	#include"export.hpp"
	#include"undefs.hpp"
}
