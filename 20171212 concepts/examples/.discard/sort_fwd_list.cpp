/**
 * does not compile as forward list does not use 
 * random access iterators .
 */

#include<algorithm>
#include<forward_list>
using namespace std;

int main()
{
    forward_list<int> fl = {3,8,5,6,2,6,7,1};
    sort(fl.begin(), fl.end());
}
