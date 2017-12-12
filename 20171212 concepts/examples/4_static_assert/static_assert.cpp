
#include <type_traits>

template<class T>
void foo(T t)
{
    (void)t;
    static_assert(std::is_floating_point<T>::value);
}

int main()
{
    // ok int is plain old data
    foo(1.5);

    // not ok vector is not pod
    foo(42);
}