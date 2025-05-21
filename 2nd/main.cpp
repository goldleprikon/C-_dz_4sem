#include <iostream>
#include <type_traits>

namespace details {

template <typename... ARGS>
struct TypeList {};

// --------------------------------------------------------------------

template <std::size_t Index, typename TList>
struct GetType;

template <typename Elem, typename ...Tail>
struct GetType<0, TypeList<Elem, Tail...>> {
    using type = Elem;
};

template <std::size_t Index, typename Elem, typename ...Tail>
struct GetType<Index, TypeList<Elem, Tail...>> {
    using type = typename GetType<Index - 1, TypeList<Tail...>>::type;
};

// --------------------------------------------------------------------

template <typename TList>
struct GetSize;

template <typename... Elems>
struct GetSize<TypeList<Elems...>> {
    static constexpr std::size_t value = sizeof...(Elems);
};

// --------------------------------------------------------------------

template <typename T, typename TList>
struct ContainsType;

template <typename T, typename Elem, typename... Tail>
struct ContainsType<T, TypeList<Elem, Tail...>> {
    static constexpr bool value = std::is_same<T, Elem>::value ||
                                  ContainsType<T, TypeList<Tail...>>::value;
};

template <typename T, typename Elem>
struct ContainsType<T, TypeList<Elem>> {
    static constexpr bool value = std::is_same<T, Elem>::value;
};

// --------------------------------------------------------------------

template <typename T, typename TList, std::size_t Index = 0>
struct GetTypeIndex;

template <typename T, std::size_t Index>
struct GetTypeIndex<T, TypeList<>, Index> {
    static constexpr std::size_t value = static_cast<std::size_t>(-1);
};

template <typename T, typename Elem, typename... Tail, std::size_t Index>
struct GetTypeIndex<T, TypeList<Elem, Tail...>, Index> {
    static constexpr std::size_t value = std::is_same<T, Elem>::value ? Index :
                                             GetTypeIndex<T, TypeList<Tail...>, Index + 1>::value;
};

// --------------------------------------------------------------------

template <typename T, typename TList>
struct AppendTypeToListEnd;

template <typename T, typename... Elems>
struct AppendTypeToListEnd<T, TypeList<Elems...>> {
    using type = TypeList<Elems..., T>;
};

// --------------------------------------------------------------------

template <typename T, typename TList>
struct AppendTypeToListBegin;

template <typename T, typename... Elems>
struct AppendTypeToListBegin<T, TypeList<Elems...>> {
    using type = TypeList<T, Elems...>;
};

}

int main()
{
    using List = details::TypeList<char, bool, int>;

    // --------------------------------------------------------------------

    static_assert(std::is_same_v<details::GetType<0, List>::type, char>);
    static_assert(std::is_same_v<details::GetType<1, List>::type, bool>);
    static_assert(std::is_same_v<details::GetType<2, List>::type, int>);
//    static_assert(std::is_same_v<details::GetType<2, List>::type, double>);

    // --------------------------------------------------------------------

    static_assert(details::GetSize<List>::value == 3);
//    static_assert(details::GetSize<List>::value == 4);

    // --------------------------------------------------------------------

    static_assert(!details::ContainsType<double, List>::value);
    static_assert(details::ContainsType<int, List>::value);

    // --------------------------------------------------------------------

    static_assert(details::GetTypeIndex<int, List>::value == 2);

    // --------------------------------------------------------------------

    using NewList = details::AppendTypeToListEnd<float, List>::type;
    static_assert(details::GetSize<NewList>::value == 4);
    static_assert(details::GetTypeIndex<float, NewList>::value == 3);

    // --------------------------------------------------------------------

    using NewList2 = details::AppendTypeToListBegin<float, List>::type;
    static_assert(details::GetSize<NewList2>::value == 4);
    static_assert(details::GetTypeIndex<float, NewList2>::value == 0);

    return 0;
}
