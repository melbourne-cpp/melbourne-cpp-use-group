#include <iostream>

template<typename T>
concept bool Incrementable(){
   return requires (T t){  
       t++;
       ++t;  // note no braces
   };
}

template<typename T>
void test(T) requires Incrementable<T>(){}

int main(){
    test(1);

    // works because its only testing if it
    // has the operation but would fail if 
    // you tried to actually increment it.
    const int ci = 2;
    test(ci);
}
