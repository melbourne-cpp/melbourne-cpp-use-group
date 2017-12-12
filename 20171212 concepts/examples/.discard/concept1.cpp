#include <iostream>
using namespace std;

#if 0
template<typename T>
auto f3(T t) {
	return t.i, t.i;
}

template<typename T>
auto f2(T t) {
	return f3(t);
}

template<typename T>
auto f1(T t) {
	return f2(t);
}
#endif


template<typename T>
concept bool C = requires(T t) {
    t.i;
};


template<C T>
auto f3(T t) {
    return t.i;
}

template<C T>
auto f2(T t) {
    return f3(t);
}

template<C T>
auto f1(T t) {
    return f2(t);
}

struct S {
    int i;
};


int main()
{
	auto x = f1(S{});
    cout << x << '\n';
}

