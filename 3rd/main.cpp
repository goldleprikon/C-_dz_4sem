#include <iostream>
#include <string>
#include <unordered_map>
#include <typeindex>

namespace details {

template <typename... ARGS>
struct TypeList {};

// --------------------------------------------------------------------
// TYPE LIST

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
    using value = std::conditional_t<std::is_same<T, Elem>::value, std::true_type, typename ContainsType<T, TypeList<Tail...>>::value>;
};

template <typename T, typename Elem>
struct ContainsType<T, TypeList<Elem>> {
    using value = std::conditional_t<std::is_same<T, Elem>::value, std::true_type, std::false_type>;
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


// --------------------------------------------------------------------

template <typename T, typename TList>
struct RemoveType;

template <typename T, typename... Elems>
struct RemoveType<T, TypeList<Elems...>> {
    using type = TypeList<>;
};

template <typename T, typename Elem, typename... Tail>
struct RemoveType<T, TypeList<Elem, Tail...>> {
    using type = std::conditional_t<std::is_same<T, Elem>::value,
                                    typename RemoveType<T, TypeList<Tail...>>::type,
                                    typename AppendTypeToListBegin<Elem, typename RemoveType<T, TypeList<Tail...>>::type>::type>;
};

// --------------------------------------------------------------------
// TYPE MAP
// IMPL

template <typename Key, typename Value, typename ListKeys>
struct TypeMapImpl;

template <typename Key, typename Value, typename... Keys>
struct TypeMapImpl<Key, Value, TypeList<Keys...>> {
    static  Value values_m[sizeof...(Keys)];

    template <typename T>
    static void Set(const Value& value) {
        values_m[GetTypeIndex<T, TypeList<Keys...>>::value] = value;
    }

    template <typename T>
    static bool Contains() {
        return typename ContainsType<T, TypeList<Keys...>>::value();
    }

    template <typename T>
    static Value& Get() {
        return values_m[GetTypeIndex<T, TypeList<Keys...>>::value];
    }

    template <typename T>
    static void Remove() {
        values_m[GetTypeIndex<T, TypeList<Keys...>>::value] = Value{};
    }
};

template <typename Key, typename Value, typename... Keys>
Value TypeMapImpl<Key, Value, TypeList<Keys...>>::values_m[sizeof...(Keys)]{};

// --------------------------------------------------------------------
// TYPE MAP

template <typename Key, typename Value, typename KeyList>
class TypeMap {
public:
    template <typename T>
    void Set(const Value& value) {
        TypeMapImpl<Key, Value, KeyList>::template Set<T>(value);
    }

    template <typename T>
    bool Contains() {
        return TypeMapImpl<Key, Value, KeyList>::template Contains<T>();
    }

    template <typename T>
    Value& Get() {
        return TypeMapImpl<Key, Value, KeyList>::template Get<T>();
    }

    template <typename T>
    void Remove() {
        TypeMapImpl<Key, Value, KeyList>::template Remove<T>();
    }
};

}

struct DataA {
    std::string value;
};

struct DataB {
    int value;
};

int main()
{
    // --------------------------------------------------------------------
    // TYPEMAP SIMPLE TESTS
    // FOR INT AND DOUBLE

    using MyTypeMap = details::TypeMap<std::string, std::string, details::TypeList<int, double>>;
    MyTypeMap TypeMap;
    TypeMap.Set<int>("Integer");
    TypeMap.Set<double>("Double");

    std::cout << "Contains int: " << TypeMap.Contains<int>() << std::endl;
    std::cout << "Contains float: " << TypeMap.Contains<float>() << std::endl;

    std::cout << "Value for int: " << TypeMap.Get<int>() << std::endl;

    TypeMap.Remove<int>();

    std::cout << "Int value after removal: " << TypeMap.Get<int>() << std::endl;


    std::cout<<"\n\n\n";

    // --------------------------------------------------------------------
    // TYPEMAP SIMPLE TESTS
    // FOR DataA AND DataB

    using MyTypeMapHarder = details::TypeMap<std::string, std::string, details::TypeList<DataA, DataB>>;
    MyTypeMapHarder TypeMap2;
    TypeMap2.Set<DataA>("HEHE");
    TypeMap2.Set<DataB>("NOT HEHE");

    std::cout << "Contains int: " << TypeMap2.Contains<int>() << std::endl;
    std::cout << "Contains float: " << TypeMap.Contains<float>() << std::endl;

    std::cout << "DataA value: " << TypeMap2.Get<DataA>() << std::endl;
    std::cout << "DataB value: " << TypeMap2.Get<DataB>() << std::endl;

    TypeMap2.Remove<DataA>();
    TypeMap2.Remove<DataB>();

    std::cout << "DataA value after removal: " << TypeMap2.Get<DataA>() << std::endl;
    std::cout << "DataB value after removal: " << TypeMap2.Get<DataB>() << std::endl;
    return 0;
}
