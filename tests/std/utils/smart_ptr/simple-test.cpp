#include <memory>
#include <iostream>
#include <cassert>

template <class T>
using Ptr = std::shared_ptr<T>;

int main()
{
    std::cout << "Testing constructors\n";
    Ptr<int> p;
    p = std::make_shared<int> (1);
    std::cout << "Conditional == true: ";
    assert(p);
    std::cout << "ok\n";
    std::cout << "Counter == 1: ";
    assert(p.use_count() == 1);
    std::cout << "ok\n";

    std::cout << "Perform reset\n";
    p.reset();
    std::cout << "Counter == 0: ";
    assert(p.use_count() == 0);
    std::cout << "ok\n";
    std::cout << "Conditional == false: ";
    assert(!p);
    std::cout << "ok\n";
}
