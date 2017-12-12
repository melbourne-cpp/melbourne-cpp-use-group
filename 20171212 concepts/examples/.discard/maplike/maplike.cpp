#include <vector>
#include <map>


/* types of requirements
 *
 * type requirements - requires that a type holds a sub type
 * simple requirement
 *
 */

template<typename T>
concept bool HasValueType = requires(T t)
{
    typename T::value_type;
};

template<typename T>
concept bool ContainsPairLike = requires(T t)
{
    typename T::value_type;
    typename T::value_type::first_type;
    typename T::value_type::second_type;
};


template<typename T>
concept bool MapLike = requires(T t)
{
    typename T::value_type;
    typename T::value_type::first_type;
    typename T::value_type::second_type;
};

void has_value_type(HasValueType vt)
{ 
    (void)vt;
}

void contains_pair_like(ContainsPairLike pl)
{
    (void)pl;
}

void is_map_like(MapLike ml)
{
    (void)ml;
}

int main()
{
    is_map_like(std::map<int, int>());
    is_map_like(std::vector<std::pair<int, int>>());
    //is_map_like(1);

    //static_assert(MapLike(std::vector<int>);
}
