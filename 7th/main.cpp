#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

namespace details {

template <typename T>
class Storage {
public:
    virtual void add(const T& element) = 0;
    virtual void remove(const T& element) = 0;
    virtual bool contains(const T& element) = 0;
//    virtual std::size_t Size() const = 0;

    virtual Storage<T>* unite(Storage<T>* other_set) = 0;
    virtual Storage<T>* intersect(Storage<T>* other_set) = 0;

    virtual std::vector<T> getElements() const = 0;
    virtual void printStorageType() const = 0;

    virtual ~Storage() = default;
};

template <typename T>
class VectorStorage : public Storage<T> {
private:
    std::vector<T> storage_m;
public:
    void add(const T& element) override;
    void remove(const T& element) override;
    bool contains(const T& element) override;
    VectorStorage<T>* unite(Storage<T>* other_set) override;
    VectorStorage<T>* intersect(Storage<T>* other_set) override;
    std::vector<T> getElements() const override {
        return storage_m;
    }
    void printStorageType() const override {
        std::cout << "It's VectorStorage\n";
    }
    ~VectorStorage() override {
        storage_m.clear();
    }
};

template <class T> void VectorStorage<T>::add(const T& element) {
    if (std::find(storage_m.begin(), storage_m.end(), element) == storage_m.end())
        storage_m.push_back(element);
}

template <class T> void VectorStorage<T>::remove(const T& element) {
    if (contains(element))
        storage_m.erase(std::remove(storage_m.begin(), storage_m.end(), element), storage_m.end());
}

template <class T> bool VectorStorage<T>::contains(const T& element) {
    return std::find(storage_m.begin(), storage_m.end(), element) != storage_m.end();
}

template <class T> VectorStorage<T>* VectorStorage<T>::unite(Storage<T>* other_set) {
    VectorStorage<T>* new_set = new VectorStorage<T>;
    for (const T& element : storage_m)
        new_set->add(element);
    for (const T& element : dynamic_cast<VectorStorage<T>*>(other_set)->storage_m)
        new_set->add(element);
    return new_set;
}

template <class T> VectorStorage<T>* VectorStorage<T>::intersect(Storage<T>* other_set) {
    VectorStorage<T>* new_set = new VectorStorage<T>;
    for (const T& element : storage_m)
        if (dynamic_cast<VectorStorage<T>*>(other_set)->contains(element))
            new_set->add(element);
    return new_set;
}

template <typename T>
class MapStorage : public Storage<T> {
private:
    std::unordered_set<T> storage_m;
public:
    void add(const T& element) override;
    void remove(const T& element) override;
    bool contains(const T& element) override;
    MapStorage<T>* unite(Storage<T>* other_set) override;
    MapStorage<T>* intersect(Storage<T>* other_set) override;
    void printStorageType() const override {
        std::cout << "It's MapStorage\n";
    }
    std::vector<T> getElements() const override {
        std::vector<T> elements(storage_m.begin(), storage_m.end());
        return elements;
    }
};

template <typename T> void MapStorage<T>::add(const T& element) {
    storage_m.insert(element);
}

template <typename T> void MapStorage<T>::remove(const T& element) {
    storage_m.erase(element);
}

template <typename T> bool MapStorage<T>::contains(const T& element) {
    return storage_m.find(element) != storage_m.end();
}

template <typename T> MapStorage<T>* MapStorage<T>::unite(Storage<T>* other_set) {
    MapStorage<T>* new_set = new MapStorage<T>;
    for (const T& element : storage_m)
        new_set->add(element);
    for (const T& element : other_set->getElements())
        new_set->add(element);
    return new_set;
}

template <typename T> MapStorage<T>* MapStorage<T>::intersect(Storage<T>* other_set) {
    MapStorage<T>* new_set = new MapStorage<T>;
    for (const T& element : storage_m)
        if (dynamic_cast<MapStorage<T>*>(other_set)->contains(element))
            new_set->add(element);
    return new_set;
}

template <typename T>
class Set {
private:
    Storage<T>* storage_m;
public:
    Set(Storage<T>* storage) : storage_m(storage) {}

    void add(const T& element);
    void remove(const T& element);
    bool contains(const T& element);
    Set<T>* unite(Set<T>* other_set);
    Set<T>* intersect(Set<T>* other_set);
    std::vector<T> getElements() const {
        return storage_m->getElements();
    }
    Storage<T>* getStorage() const {
        return storage_m;
    }
    void printStorageType() const {
        storage_m->printStorageType();
    }
//    ~Set() {
//        delete storage_m;
//    }
};

template <typename T> void Set<T>::add(const T& element) {
    size_t start_size = storage_m->getElements().size();
    storage_m->add(element);
    if (storage_m->getElements().size() > 100 && start_size <= 100)
    {
        Storage<T>* new_storage = new MapStorage<T>;
        for (const T& el : storage_m->getElements()) {
            new_storage->add(el);
        }
        storage_m = new_storage;
    }
}

template <typename T> void Set<T>::remove(const T& element) {
    size_t start_size = storage_m->getElements().size();
    storage_m->remove(element);
    if (storage_m->getElements().size() < 100 && start_size >= 100)
    {
        Storage<T>* new_storage = new VectorStorage<T>;
        for (const T& el : storage_m->getElements()) {
            new_storage->add(el);
        }
        delete storage_m;
        storage_m = new_storage;
    }
}

template <typename T> bool Set<T>::contains(const T& element) {
    return storage_m->contains(element);
}

template <typename T> Set<T>* Set<T>::unite(Set<T>* other_set) {
    Storage<T>* new_vector_storage = new VectorStorage<T>;
    Storage<T>* new_map_storage = new MapStorage<T>;
    Storage<T>* united_storage = storage_m->unite(other_set->storage_m);
    if (united_storage->getElements().size() > 100) {
        MapStorage<T>* map_storage = dynamic_cast<MapStorage<T>*>(new_map_storage);
        delete new_vector_storage;
        for (const T& el : united_storage->getElements()) {
            map_storage->add(el);
        }
        return (new Set<T>(map_storage));
    } else {
        VectorStorage<T>* vector_storage = dynamic_cast<VectorStorage<T>*>(new_vector_storage);
        delete new_map_storage;
        for (const T& el : united_storage->getElements()) {
            vector_storage->add(el);
        }
        return (new Set<T>(vector_storage));
    }
}

template <typename T> Set<T>* Set<T>::intersect(Set<T>* other_set) {
    Storage<T>* new_vector_storage = new VectorStorage<T>;
    Storage<T>* new_map_storage = new MapStorage<T>;
    Storage<T>* united_storage = storage_m->intersect(other_set->storage_m);
    if (united_storage->getElements().size() > 100)
    {
        MapStorage<T>* map_storage = dynamic_cast<MapStorage<T>*>(new_map_storage);
        delete new_vector_storage;
        for (const T& el : united_storage->getElements()) {
            map_storage->add(el);
        }
        return (new Set<T>(map_storage));
    }
    else {
        VectorStorage<T>* vector_storage = dynamic_cast<VectorStorage<T>*>(new_vector_storage);
        delete new_map_storage;
        for (const T& el : united_storage->getElements()) {
            vector_storage->add(el);
        }
        return (new Set<T>(vector_storage));
    }
}
}

using namespace details;

void SimpleVectorStorageTest() {
    std::cout << "SIMPLE VECTOR STORAGE TEST" << std::endl;

    VectorStorage<int> vector;

    for (size_t i = 0; i < 200; i++)
        vector.add(i);

    int counter = 0;
    for (size_t j = 0; j < 200; j++)
        counter += vector.contains(j);
    std::cout << "There are 200 elements in vector, counter = " << counter << ";\n";

    vector.remove(2);
    vector.remove(102);
    std::cout << "Deleted 102 and 2, contains(102): " << vector.contains(102) << ", contains(2): " << vector.contains(2) << ";\n";

    VectorStorage<int> vector_union_intersect;
    vector_union_intersect.add(2);
    vector_union_intersect.add(102);

    VectorStorage<int>* united_vector = vector.unite(&vector_union_intersect);
    std::cout << "Added from unit 102 and 2, contains(102): " << united_vector->contains(102) << ", contains(2): " << united_vector->contains(2) << ";\n";

    VectorStorage<int>* intersected_vector = vector.intersect(&vector_union_intersect);
    int counter_intersect = 0;
    for (size_t j = 0; j < 200; j++)
        counter += intersected_vector->contains(j);
    std::cout << "There are 0 elements in vector, counter = " << counter_intersect << ";\n\n";
}

void SimpleHashStorageTest() {
    std::cout << "SIMPLE HASH STORAGE TEST" << std::endl;

    MapStorage<int> map;

    for (size_t i = 0; i < 200; i++)
        map.add(i);

    int counter = 0;
    for (size_t j = 0; j < 200; j++)
        counter += map.contains(j);
    std::cout << "There are 200 elements in map, counter = " << counter << ";\n";

    map.remove(2);
    map.remove(102);
    std::cout << "Deleted 102 and 2, contains(102): " << map.contains(102) << ", contains(2): " << map.contains(2) << ";\n";

    MapStorage<int> map_union_intersect;
    map_union_intersect.add(2);
    map_union_intersect.add(102);

    MapStorage<int>* united_map = map.unite(&map_union_intersect);
    std::cout << "Added from unit 102 and 2, contains(102): " << united_map->contains(102) << ", contains(2): " << united_map->contains(2) << ";\n";

    MapStorage<int>* intersected_map = map.intersect(&map_union_intersect);
    int counter_intersect = 0;
    for (size_t j = 0; j < 200; j++)
        counter += intersected_map->contains(j);
    std::cout << "There are 0 elements in map, counter = " << counter_intersect << ";\n\n";
}

void SimpleSetTest() {
    VectorStorage<int> vector_st;
    Set<int> set(&vector_st);
    for (size_t i = 0; i < 200; i ++)
        set.add(i);

    MapStorage<int> map_st;
    Set<int> set2(&map_st);
    for (size_t i = 200; i < 250; i ++)
        set.add(i);

    Set<int>* set_united = set.unite(&set2);
    std::cout << "Count of elements in united set " << set_united->getElements().size() << std::endl;

    Set<int>* set_intersected = set.intersect(&set2);
    std::cout << "Count of elements in intersected set " << set_intersected->getElements().size() << std::endl;
    std::cout << std::endl;
}

void TransitionSetTest() {
    VectorStorage<int> vector_st;
    Set<int> set(&vector_st);
    set.printStorageType();
    for (size_t i = 0; i < 200; i ++)
        set.add(i);
    set.printStorageType();

    MapStorage<int> map_st;
    Set<int> set2(&map_st);
    for (size_t i = 200; i < 301; i ++)
        set2.add(i);
    set2.printStorageType();
    set2.remove(200);
    set2.remove(201);
    set2.printStorageType();
}

int main()
{
    // It works )))
    SimpleVectorStorageTest();
    SimpleHashStorageTest();

    // It's time to use Set
    SimpleSetTest();
    TransitionSetTest();
    return 0;
}
