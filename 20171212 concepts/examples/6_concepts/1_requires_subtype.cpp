#include <vector>

using namespace std;

template<typename T>
concept bool HasValueType()
{
   return requires (T t)
   {
       typename T::value_type;
   };
}

void foo(HasValueType)
{}

int main()
{
  vector<int> v = {1,2,3};
  foo(v.begin());

  // fails no value_type member
  foo(12);
}
