//string.hpp
//at namespace elc::string_n
/*
未完成的elc解释器string文件
由steve02081504与Alex0125设计、编写
转载时请在不对此文件做任何修改的同时注明出处
项目地址：https://github.com/steve02081504/ELC

注意：
	本文件可能使用了cpp20的新支持或语义，而某些编译器可能并没有支持
	同时，此项目并没有完成
*/
template<class T,typename size_type=::std::size_t>
class string{
	typedef string_data<T,size_type> data_type;

	comn_ptr<data_type> to;
	bool unique()noexcept{return to->link_num()==1;}
public:
	
	T&arec(size_type a)noexcept{return to->arec(a);}
	T&operator[](size_type a)noexcept{return (*to)[a];}

	
}
