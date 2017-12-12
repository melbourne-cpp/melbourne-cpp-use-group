#include <vector>
#include <list>

template<typename T>
concept bool IsRandomAccessIterator(){
   return requires (T t){  
       { t++ } -> T;
       { ++t } -> T&;

       requires std::is_same<typename T::iterator_category,
                             std::random_access_iterator_tag>::value;
   };
}

template<typename T>
void test(T) requires IsRandomAccessIterator<T>(){}

int main(){
    std::vector<short> v = {1,2,3,4,5};
    std::list<short> L = {1,2,3,4,5};

    test(v.begin());
    // fails not random access
    //test(L.begin());
}
