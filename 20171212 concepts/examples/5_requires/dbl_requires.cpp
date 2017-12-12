#include <vector>

template<typename T>
   requires requires () { typename T::iterator_category; }
void foo(T)
{ }

int main()
{
	std::vector<char> vc = {'c','p','p'};
	foo(vc.begin());
    // fails no iterator_category
    //foo(42);
}

