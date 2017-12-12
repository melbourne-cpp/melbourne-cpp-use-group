#include<cstddef>
#include<iterator>
#include<iostream>
using namespace std;
/**
requirements on a type to go into a std::vector

(copy constructable) ??
copy assignable
*/

template<typename T>
class vector
{
   public:
   typedef T value_type;
   typedef size_t size_type; // should come from allocator

   // constructor 1
   vector(size_type n, const value_type& t)
   {
       (void) n; (void)t;
       cout << "ctor 1\n";
   }

   // constructor 2
   template<typename InputIter>
   vector(InputIter first, InputIter last)
   {
       (void)first, (void)last;
       cout << "ctor 2\n";
   }

   private:
   char* storage;
};

int main()
{
   int x[] = {1,2,3,4};

   // calls ctor 2 as expected
   vector<int> v2(begin(x), end(x));

   // whoops calls ctor 2 aswell, not what we wanted! 
   vector<int> v(5, 2);

   // calls ctor 1 as we wanted due to exact type match.
   vector<int> v3(3lu, 4);
}

