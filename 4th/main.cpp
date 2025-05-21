#include <iostream>
template <typename Derived>
class less_than_comparable {
public:
    friend bool operator>(const Derived& lhs, const Derived& rhs) {
        return rhs < lhs;
    }

    friend bool operator<=(const Derived& lhs, const Derived& rhs) {
        return !(rhs < lhs);
    }

    friend bool operator>=(const Derived& lhs, const Derived& rhs) {
        return !(lhs < rhs);
    }

    friend bool operator==(const Derived& lhs, const Derived& rhs) {
        return !(lhs < rhs) && !(rhs < lhs);
    }

    friend bool operator!=(const Derived& lhs, const Derived& rhs) {
        return (lhs < rhs) || (rhs < lhs);
    }
};


class MyNumber : public less_than_comparable<MyNumber> {
private:
    int value;
public:
    MyNumber(int val) : value{val} {}

    friend bool operator<(const MyNumber& lhs, const MyNumber& rhs) {
        return lhs.value < rhs.value;
    }
};

template <typename Derived>
class counter {
private:
    static int count;

protected:
    counter() {
        ++count;
    }

public:
    static int getCount() {
        return count;
    }
};

template <typename Derived>
int counter<Derived>::count = 0;

class MyCountedClass : public counter<MyCountedClass> {
public:
    MyCountedClass() {}
};

int main()
{
    MyNumber num1(10);
    MyNumber num2(25);

    std::cout << (num1 < num2) << std::endl;
    std::cout << (num1 > num2) << std::endl;
    std::cout << (num1 <= num2) << std::endl;
    std::cout << (num1 >= num2) << std::endl;
    std::cout << (num1 == num2) << std::endl;
    std::cout << (num1 != num2) << std::endl;

    MyCountedClass obj1;
    MyCountedClass obj2;

    std::cout << "Number of MyClass instances: " << MyCountedClass::getCount() << std::endl;
    return 0;
}
