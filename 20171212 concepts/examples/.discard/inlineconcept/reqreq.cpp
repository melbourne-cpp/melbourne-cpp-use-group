/**
 * demonstrates an inline concept definition
 * using the double requires clause.
 */
#include<vector>
using namespace std;

template<typename T>
void foo(const T&) requires requires () { typename T::value_type; }
{}

struct with_value_type
{
    typedef int value_type;
};

int main()
{
    foo(vector<int>());
    foo(with_value_type());
    foo(1);
}
