namespace for_test{
	unsigned error_num;
	(const char)*part_name;
	(const char)*test_name;
	inline void should(bool,const char,unsigned long);
}
#define TEST_PART(name) \
namespace name{ \
	void test_main()noexcept;

#define END }

#define DECL_TEST_PART(name) \
namespace name{ \
	void test_main()noexcept; \
}

#define DEF_MOD(name) \
void name()noexcept{ \
	::for_test::test_name=#name;

#define END_MOD_DEF }

#define DEF_PART(name) \
namespace name{ \
	void test_main()noexcept{ \
		::for_test::part_name=#name; \
		::for_test::error_num=0;

#define END_PART_DEF ::for_test::part_test_end();}}

#define MOD(name) name();

#define TEST(name) name::test_main();

#define WHEN

#define SHOULD(...) ::for_test::should(__VA_ARGS__,__FILE__,__LINE__)

#define MUST(...) ::for_test::must(__VA_ARGS__,__FILE__,__LINE__)
