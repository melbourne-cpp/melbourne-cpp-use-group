#include <iostream>
#include <vector>
#include <list>
#include <thread>
#include <memory>
#include <type_traits>
// cant have using namespace std;

// requires copy construct and assignment op
template <typename T>
void swap(T& a, T& b) noexcept
{
    using std::move;
    
    T temp = move(a);
    a = move(b);
    b = move(temp);
}

/*
// create a specialization for integral types that does not require a temp. hahahahaha
template <typename T, typename std::enable_if<std::is_integral<T>::value, T>::type>
void swap(T& a, T& b)
{
    a ^= b;
    b ^= a;
    a ^= b;
}
*/

// requires dereferenceable, plus all from swap
template<typename Iter>
void iter_swap(Iter a, Iter b)
{
    swap(*a, *b);
}

// requires bi di iterator
// i.e increment and decrement.
// plus all from iter_swap
template<typename BiDirIter>
void reverse(BiDirIter first, BiDirIter last)
{
    while((first != last) && (first != --last))
    {
        iter_swap(first, last);
        ++first;
    }
}

class NoCopyCtor
{
    int i_;

    public:
    explicit NoCopyCtor(int i) : i_(i){} 
    NoCopyCtor(const NoCopyCtor&) = delete;

    friend std::ostream& operator<<(std::ostream& os, const NoCopyCtor& n)
    {
        os << n.i_;
        return os;
    }
};

class NoCopyAssig
{
    int i_;

    public:
    explicit NoCopyAssig(int i) : i_(i){} 
    NoCopyAssig& operator=(const NoCopyAssig&) = delete;

    friend std::ostream& operator<<(std::ostream& os, const NoCopyAssig& n)
    {
        os << n.i_;
        return os;
    }
};

template<typename T>
void swap_test(T& x, T& y)
{
    std::cout << "before: x=" << x << " y=" << y << '\n';
    swap(x, y);
    std::cout << "after: x=" << x << " y=" << y << '\n';
}

int main()
{
    int x = 1, y = 2;
    swap_test(x, y);

    NoCopyCtor nx(3), ny(4);
    //swap_test(nx, ny);
    NoCopyAssig ax(5), ay(6);
    //swap_test(ax, ay);
    
    std::list<int> il = {3,5,7,8,9};
    for(int i: il) std::cout << i << ", ";
    std::cout << '\n';
    
    reverse(il.begin(), il.end());

    for(int i: il) std::cout << i << ", ";
    std::cout << '\n';

    std::thread t;
    std::thread t2;
    swap(t, t2);

    std::unique_ptr<int> up1 = std::make_unique<int>(1);
    std::unique_ptr<int> up2 = std::make_unique<int>(2);
    swap(up1, up2);
}

