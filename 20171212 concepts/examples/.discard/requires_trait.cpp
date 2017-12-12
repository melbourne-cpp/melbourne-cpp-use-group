
/**
 * demonstrate how the ability to add two of the same type can be detected using
 * a type train which can then be composed into a concept.
 *
 * This is a pretty flawed example. It doesnt accoutn for adding two different 
 * types or for cv qualification or for 
 *
 */

#include <iostream>
#include <complex>
#include <type_traits>
using namespace std;

// has operator+ type trait
// this is a rudimentary version of void_t

template<class> 
struct type_sink { typedef void type; };

template<class T>
using type_sink_t = typename type_sink<T>::type;


template<class T, class=void>
struct has_operator_plus : false_type
{};

template<class T>
struct has_operator_plus<T, type_sink_t<decltype(declval<T>() + declval<T>())>> : true_type 
{};

template<typename T>
inline constexpr bool has_operator_plus_v = has_operator_plus<T>::value;

template<class T>
concept bool Addable()
{
    return has_operator_plus_v<T>;
}

#if 0

// use requires clause with type trait or concept
// but why create a concept when a type trait will do? 
template <class T>
//T add(T a, T b) requires has_operator_plus_v<T>
T add(T a, T b) requires Addable<T>()
{
    return a + b;
}
#endif


// using static_assert
// this example shows that static_assert does not in any
// way give you a shorter or clearer error message
template<class T>
auto add(T a, T b)
{
    static_assert(has_operator_plus_v<T>);
    return a + b;
}

#if 0
// using expression sfinae
template<class T>
auto add(T a, T b) -> decltype(a + b)
{
    return a + b;
}
#endif

#if 0
template<class T>
enable_if_t<has_operator_plus_v<T>, T> add(T a, T b)
{
    return a + b;
}
#endif
struct cant_add 
{
    int i;

    // comment out to see failure
    cant_add operator+(const cant_add& oth)
    {
        return cant_add{i + oth.i};
    }

    friend ostream& operator<<(ostream& os, const cant_add& ca)
    {
        os << ca.i;
        return os;
    }
};


// this class shows the trait can work with classes that require constructor args
class add_wargs
{
    int i_;
    public:
    explicit add_wargs(int i) : i_(i)
    {}

    add_wargs operator+(const add_wargs& oth)
    {
       return add_wargs{i_ +  oth.i_};
    }

    friend ostream& operator<<(ostream& os, const add_wargs& a)
    {
        os << a.i_;
        return os;
    }
};


int main()
{
    int i1 = add(1, 2);
    long i2 = add(1L, 3L);
    double i3 = add(3.2, 4.6);
    auto c1 = add(complex{1.0, 5.0}, complex{1.0, 2.0});
    char ch1 = add('e', 't');

    cant_add ca1 = add(cant_add{1}, cant_add{2});
    add_wargs wa1 = add(add_wargs{1}, add_wargs{2});

    cout << "i1 = " << i1 << '\n';
    cout << "i2 = " << i2 << '\n';
    cout << "i3 = " << i3 << '\n';
    cout << "c1 = " << c1 << '\n';
    cout << "ch1 = " << ch1 << '\n';
    cout << ca1 << '\n';
    cout << wa1 << '\n';
}

