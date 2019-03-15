//pool.hpp
/*
未完成的elc解释器base文件
由steve02081504与Alex0125设计、编写
转载时请在不对此文件做任何修改的同时注明出处
项目地址：https://github.com/steve02081504/ELC

注意：
	本文件可能使用了cpp20的新支持或语义，而某些编译器可能并没有支持
	同时，此项目并没有完成
*/
namespace pool_n{
	template<class T,::std::uint_fast16_t ment_size>
	struct ment final:cons_t<ment<T,ment_size>>{
		typedef ::std::uint_fast16_t uint;
		typedef cons_t<ment<T,ment_size>> cons;
		static_assert(ment_size,"are you crazy?");
		static constexpr uint ment_index_max=ment_size-1;

		uint unuse_indexes_index;
		uint unuse_indexes[ment_size];
		struct part final{
			data_t<T>data;
			part()noexcept{
				data.activation_by([](T*a)noexcept{new(a)T(just_init_flag);});
			}
			T*get()noexcept{return data.get();}
			bool was_using()noexcept{
				return data.get()->was_using();
			}
			~part()noexcept{
				data.inactivation();
			}
		};
		part member[ment_size];

		[[nodiscard]]static void*operator new(::std::size_t)noexcept{
			return memory::alloc<ment>();
		}
		static void operator delete(void*a)noexcept{
			memory::free(a);
		}
		constexpr ment():cons(do_nothing){
			for(uint a=0;a!=ment_size;a++)unuse_indexes[a]=a;
			unuse_indexes_index=ment_size;
		}
		template<typename...args>
		[[nodiscard]]T*get_new(args&&...rest)noexcept{
			auto&uii=unuse_indexes_index;
			auto&ui=unuse_indexes;
			if(!uii)return nullptr;
			T*tmp=member[ui[--uii]].get();
			tmp->start_using(::std::forward<args>(rest)...);
			return tmp;
		}
		[[nodiscard]]bool unused(T*a)noexcept{
			if(
			reinterpret_cast<void*>(a)>=reinterpret_cast<void*>(member)&&
			reinterpret_cast<void*>(member+ment_index_max)>=reinterpret_cast<void*>(a)
			){
				unuse_indexes[unuse_indexes_index++]=a-(T*)member;
				return true;
			}
			return false;
		}
		void for_each(void mapper(T&)){
			for(uint a=0;a!=ment_size;a++)if(member[a].was_using())mapper(*member[a].get());
		}
		[[nodiscard]]bool empty()noexcept{return unuse_indexes_index==ment_size;}
	};
	//requre:
	//was_using、constructor(just_init_flag_t)、start_using
	//call use_end when use end.
	template<class T,::std::uint_fast16_t ment_size>
	class pool_t final:list_t<ment<T,ment_size>>,non_copyable,non_moveable{
		typedef ment<T,ment_size> ment;
		typedef list_t<ment> list;
		using typename list::iterator;
		using list::begin;
		using list::head;
		using list::end;
	public:
		typedef ment friend_t;
		pool_t()noexcept=default;
		~pool_t()noexcept{
			auto i=begin(),e=end();
			while(i!=e)
				delete i++;
		}
		template<typename...args>
		[[nodiscard]]T*get_new(args&&...rest)noexcept{
			{
				T*tmp;
				auto i=head(),e=end();
				while(--e!=i){//从后向前遍历，一般情况下可以加快分配速度🐀򓠀
					tmp=e->get_new(::std::forward<args>(rest)...);
					if(tmp)return tmp;
				}
			}
			auto tmp2=new ment;//失败，加入新单元
			list::add(tmp2);
			return tmp2->get_new(::std::forward<args>(rest)...);
		}
		void use_end(T*a)noexcept{
			auto i=head(),e=end();
			while(++i!=e)
				if(i->unused(a))return;
		}
		void for_each(void mapper(T&)noexcept)noexcept{
			auto i=head(),e=end();
			while(++i!=e)
				i->for_each(mapper);
		}
		bool shrink()noexcept{
			bool shrink_success=false;
			iterator i=begin(),e=end(),n;
			while((n=i++)!=e){
				if(n->empty()){
					delete n;
					shrink_success=true;
				}
			}
			return shrink_success;
		}
		[[nodiscard]]bool empty()noexcept{
			auto i=head(),e=end();
			while(++i!=e)
				if(i->empty())return false;
			return true;
		}
	};
}
using pool_n::pool_t;
