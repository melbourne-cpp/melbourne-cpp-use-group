template<typename T>
concept bool Incrementable(){
   return requires (T t){  
       { t++ } -> T;
       { ++t } -> T&;
   };
}

template<typename T>
void test(T) requires Incrementable<T>(){}

int main(){
    test(1);
}
