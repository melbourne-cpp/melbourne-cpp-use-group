/**
 * swap, iter_swap defined using concepts
 * 
 *
 */

#include<type_traits>
#include<utility>

#include<vector>
#include<thread>

using namespace std;

namespace pjr
{
    template<typename T>
    concept bool Destructible()
    {
        // return std::is_destructible<T>::value;
        return requires (T* t) { t->~T(); };
    }

    template<typename T, typename... Args>
    concept bool Constructible()
    {
        return Destructible<T>() && std::is_constructible<T, Args...>::value;
    }

    template<typename T>
    concept bool MoveAssignable()
    {
        return std::is_assignable<T&, T&&>::value;
    }

    template<typename T>
    concept bool MoveConstructible()
    {
        return Constructible<T, T&&>();
    }

template<typename T>
void swap(T& a, T& b) 
  requires MoveConstructible<T>() && MoveAssignable<T>()
{
    using std::move;

    T temp = move(a);
    a = move(b);
    b = move(temp);
}

template<typename FwdIter>
void iter_swap(FwdIter a, FwdIter b)
{
    swap(*a, *b);
}

}

struct no_move
{
    no_move(){}

    no_move(no_move&&) = delete;
    no_move& operator=(no_move&&) = delete;
    
    no_move(const no_move&) = default;
    no_move& operator=(const no_move&) = default;
};

struct no_copy
{
    no_copy(){}

    no_copy(no_move&&) 
    {}
    no_copy& operator=(no_copy&&)
    {
        return *this;
    }
    
    no_copy(const no_copy&) = delete;
    no_copy& operator=(const no_copy&) = delete;
};
int main()
{
    int a = 2, b = 3;
    pjr::swap(a, b);
    
    vector<char> foo = {'b', 'a', 'r'}, bar = {'b','a','z'};
    pjr::swap(foo, bar);

    thread t1, t2;
    pjr::swap(t1, t2);

    no_move x, y;
    pjr::swap(x, y);
}
