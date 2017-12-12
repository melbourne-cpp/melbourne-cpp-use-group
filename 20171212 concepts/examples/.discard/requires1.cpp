
#include <iostream>
using namespace std;

template<typename T>
T add(T a, T b)
{
    return a + b;
}

int main()
{
    int i = add(1,2);
    float f = add(1.0, 2.0);
    
    cout << i << ' ' << f << '\n';
}
