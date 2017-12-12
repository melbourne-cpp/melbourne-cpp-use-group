#include <type_traits>

template<typename T>
void foo(T) requires true
{}

template<typename T>
void bar(T) requires false
{}

constexpr bool pred() { return true; }

template<typename T>
void baz(T) requires pred()
{}

template<typename T>
struct meta_fn : std::true_type
{};

template<typename T>
void foo2(T) requires meta_fn<T>::value
{}

int main()
{
 foo(2);
 //bar('x');
 baz(7UL);
 foo2(2.5);
}

