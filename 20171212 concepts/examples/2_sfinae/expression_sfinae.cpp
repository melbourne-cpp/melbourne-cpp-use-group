
#include <iostream>
#include <string>

namespace pjr 
{
    // overload that is active for any type with a begin member function
    template <class T>
    auto begin(T& t) -> decltype(t.begin()) // sfinae happens here
    {
        return t.begin();
    }

    // overload that is selected for an array type.
    template<class T, size_t N>
    T* begin(T (&array)[N])
    {
        return &(array[0]);
    }
}
 
int main()
{
    char arr[] = "melbourne cpp";
    std::string s = "cpp melbourne";
    
    std::cout << *pjr::begin(arr) << '\n';
    std::cout << *pjr::begin(s) << '\n';

    // fails has no begin member and is not array.
    //int x = 5;
    //pjr::begin(x);
}
