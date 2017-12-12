/**
 * demonstrate how tag dispatch can be used to provide
 * more optimized overloads for different iterator categories.
 */

#include<iostream>
#include<vector>
#include<forward_list>
#include<list>

using namespace std;

namespace detail
{
    template<class InputIter>
    void advance_impl(InputIter& it, size_t n, input_iterator_tag)
    {
        cout << " (advance linear) "; 
        while(n--) ++it; 
    }

    template<class BiDiIter>
    void advance_impl(BiDiIter& it, size_t n, bidirectional_iterator_tag)
    {
        cout << " (advance bidir) ";
        if(n > 0)  while(n--) ++it;
        else       while(n++) --it;
    }

    template<class RandomAccessIter>
    void advance_impl(RandomAccessIter& it, size_t n, random_access_iterator_tag)
    { 
        cout << " (advance constant) ";
        it += n;
    }

    template<class TIter>
    using iterator_category_t = typename iterator_traits<TIter>::iterator_category;

    template<class TIter>
    iterator_category_t<TIter> iterator_category(const TIter&)
    {
        return iterator_category_t<TIter>();
    }
}


template<class TIter>
void advance(TIter& it, size_t n)
{
    //typename iterator_traits<TIter>::iterator_category cat;
    detail::advance_impl(it, n, detail::iterator_category<TIter>(it)); 
}

template<typename TIter>
void printadv(TIter it, size_t num)
{
    cout << "starts: "<< *it;
    cout << " will advance by " << num; 
    advance(it, num);

    cout << " ends: " << *it << '\n';
}

int main()
{
    // demonstate advance on vector (RandomAccessIterator)
    vector<int> v = {2,3,4,5,6,7,8,9,10};
    printadv(begin(v), 5);

    // demonstrate advance on list (BidirectionalIterator)
    list<int> L = {3,4,5,6,7,8,6,5,5,4};
    printadv(begin(L), 5);

    forward_list<int> fl = {6,7,8,9,10,11,12};
    printadv(begin(fl), 3);
}

