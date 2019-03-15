//transition.hpp
/*
未完成的elc解释器core文件
由steve02081504与Alex0125设计、编写
转载时请在不对此文件做任何修改的同时注明出处
项目地址：https://github.com/steve02081504/ELC

注意：
	本文件可能使用了cpp20的新支持或语义，而某些编译器可能并没有支持
	同时，此项目并没有完成
*/
class node;//safe_ref_able,weak_ref_able
BREAK_NAMESPACE
template<>inline bool base::ptr_n::checker(core::node*)noexcept;
INTER_NAMESPACE(core)
typedef comn_p_t<node>comn_ptr;
typedef weak_p_t<node>weak_ptr;
typedef safe_p_t<node>safe_ptr;
class member;//safe_ref_able
typedef comn_p_t<member>comn_ppr;
typedef safe_p_t<member>safe_ppr;

class setter;

#define defspecialvalue(a) \
constexpr node*get_##a##_address()noexcept;\
inline bool is_##a(comn_ptr b)noexcept{return b==get_##a##_address();}\
constexpr node*get_##a##_address()noexcept

defspecialvalue(fail);
defspecialvalue(nil);
defspecialvalue(t);

#undef defspecialvalue
