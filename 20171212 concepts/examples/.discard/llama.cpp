#include <iostream>
using namespace std;

template <class T>
concept bool SupportsFoo = requires (T t) {
  { t.get_foo() } -> int;
};

template <SupportsFoo T>
int calculate_foo_factor (const T& t) {
    return t.get_foo();
}

template <class T>
int calculate_foo_factor (const T& t) {
    // insert generic calculation here
    return 42;
}


class Fooey
{
	int i_;
    public:
    Fooey(int i)
        : i_(i)
	{}
    
    int get_foo() const { return i_; }
};

int main()
{
   cout << calculate_foo_factor(Fooey{5}) << '\n';
   cout << calculate_foo_factor(6) << '\n';
}
