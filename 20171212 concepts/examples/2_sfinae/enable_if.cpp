
#include <iostream>
#include <numeric>
#include <type_traits>

namespace pjr
{
    // none specialized version (falls back to this when B = false)
    // type typedef does not exist
    template<bool B, class T = void>
    struct enable_if {};

    // specialization when B = true 
    //   (you could implement it the other way round if 
    //   you want where the specialization is for false)
    // type typedef exists
    template<class T>
    struct enable_if<true, T>  { typedef T type; };

    // helper to remove boilerplate at call site
    template<bool B, class T = void>
    using enable_if_t = typename enable_if<B, T>::type;
}

/**
 * sfinae on return type
 * 
 * but there are a few other context where it is allowed
 * these differ between class and function templates and
 * new contexts have been added in recent standards.
 * 
 * most common are
 * 1. on return type (dont think this works if return type is void)
 * 2. on function parameter
 * 3. on dummy template parameter
 */
template<class T>
typename pjr::enable_if<std::is_integral<T>::value, T>::type succ(T t)
{
    return t + 1;
}

template<class T>
pjr::enable_if_t<std::is_integral<T>::value, T> prev(T t)
{
    return t - 1;
}

int main()
{
    int a[10];
    std::iota(std::begin(a), std::end(a), 1);

    for(int i: a)
    {
        std::cout << "succ(" << i << ")" << succ(i) << '\n';
    }

    for(int i: a)
    {
        std::cout << "prev(" << i << ")" << prev(i) << '\n';
    }   

    // overload not present as 2.5 is not integral
    //std::cout << "succ(2.5)" << succ(2.5) << '\n';
}