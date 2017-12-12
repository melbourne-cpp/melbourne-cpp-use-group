#include <vector>
#include <forward_list>
using namespace std;

template<typename T>
concept bool HasValueType()
{
   return requires (T t)
   {
       typename T::value_type;
   };
}

template<typename T>
concept bool Incrementable()
{
   return requires (T t)
   {  
       { t++ } -> T;
       { ++t } -> T&;
   };
}

template<typename T>
concept bool Decrementable()
{
   return requires (T t)
   {
       { t-- } -> T;
       { --t } -> T&;
   };
}

template<typename T>
concept bool Dereferenceable()
{
   return HasValueType<T>() &&
   requires (T t)
   {
       { *t } -> typename T::value_type&;
   };
}

void foo(Incrementable){}
void bar(Decrementable){}
void baz(Dereferenceable){}

template<typename T>
void fooandbar(T t)
{
 foo(t);
 bar(t);
}

int main()
{
 vector<int> v = {1,2,3};
 fooandbar(v.begin());
 fooandbar(10);
 fooandbar(1.1);

 forward_list<int> L = {1,2,3};
#ifdef FAIL
 // fails because fwd list iterator is not decrementable
 fooandbar(L.begin());
#endif

 baz(v.begin());
 baz(L.begin());
#ifdef FAIL
 // fails because int is not dereferenceable
 baz(1);

 int i = 10;
 // fails because int has no value_type
 baz(&i);
#endif
}

