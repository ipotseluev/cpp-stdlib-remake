#include <iostream>
#include <cassert>
#include <string>
#include "shared_ptr.h"
#include "make_shared.h"

template <class T>
using Ptr = igor::shared_ptr<T>;

void test_true(const std::string name, bool condition)
{
    std::cout << "\t" << name << ": "; 
    if (condition)
    {
        std::cout << "ok\n";
    }
    else
    {
        std::cout << "failed\n";
        exit(1);
    }
}

int main()
{
    std::cout << "Default Ctor\n";
    {
    Ptr<int> ptr_default;
    test_true("Conditional operator", !ptr_default);
    test_true("Default ctor use_count == 0", !ptr_default.use_count());
    try
    {
        *ptr_default;
        test_true("Default ctor dereference throws exception", false);
    }
    catch (...)
    {
        test_true("Default ctor dereference throws exception", true);
    }
    }

    std::cout << "Test case: make shared\n";
    {
    Ptr<int> ptr_int_ms = igor::make_shared<int>(1);
    test_true("Initialized", *ptr_int_ms == 1);
    }

    std::cout << "Test case: raw ptr Ctor\n";
    {
    Ptr<int> ptr_int(new int(10));
    test_true("use_count == 1", ptr_int.use_count() == 1);
    test_true("Conditional operator", (bool)ptr_int);
    test_true("Dereference operator", *ptr_int == 10);
    }

    std::cout << "Test case: member access operator\n";
    {
    Ptr<std::string> ptr_string(new std::string("Hello Igor"));
    test_true("Dereference operator", *ptr_string == "Hello Igor");
    test_true("Dereference operator member access", (*ptr_string).size() == 10);
    test_true("Arrow operator member access", ptr_string->size() == 10);
    }

    std::cout << "Test case: Copy Ctor\n";
    {
    Ptr<int> rh_ptr(new int(1));
    Ptr<int> lh_ptr(rh_ptr);
    test_true("Copy ctor makes equal value", *lh_ptr == *rh_ptr);
    test_true("Copy ctor makes use_counter == 2", lh_ptr.use_count() == 2);
    }

    std::cout << "Test case: Move Ctor\n";
    {
        std::cout << "TODO\n";
    }

    std::cout << "Test case: Copy assignment operator\n";
    {
        std::cout << "TODO\n";
    }

    std::cout << "Test case: Move assignment operator\n";
    {
    Ptr<int> ptr(igor::make_shared<int>(1));
    Ptr<int> copy_ptr = ptr;
    ptr = igor::make_shared<int>(10);
    test_true("Move assignment decrements usage counter of original ptr",
              copy_ptr.use_count() == 1);
    test_true("Move assignment assigns new value", *ptr == 10);
    test_true("Move assignment doesn't force destroying old value", *copy_ptr == 1);
    }

    std::cout << "Test case: reset\n";
    {
    Ptr<int> ptr0;
    ptr0.reset();
    test_true("Ref count on uninitialized pointer after reset", !ptr0.use_count());
    test_true("Conditional on uninitialized pointer after reset", !ptr0);

    Ptr<std::string> ptr1 = igor::make_shared<std::string>("Hello");
    Ptr<std::string> ptr2 = igor::make_shared<std::string>("Igor");
    ptr1.reset();
    test_true("Ref count on initialized pointer after reset", !ptr1.use_count());
    test_true("Conditional on initialized pointer after reset", !ptr1);
    ptr1.reset(ptr2);
    test_true("Ref count on initialized pointer after swap reset",
              ptr1.use_count() == 2);
    test_true("Conditional on initialized pointer after swap reset", (bool)ptr1);
    }

    std::cout << "Test case: use_count\n";
    {
    Ptr<int> ptr1;
    Ptr<int> ptr2 = igor::make_shared<int>(1);
    Ptr<int> ptr3 = ptr2;
    test_true("Use count == 2", ptr2.use_count() == 2);
    ptr1 = ptr2;
    test_true("Use count == 3", ptr1.use_count() == 3);
    ptr1 = igor::make_shared<int> (1);
    test_true("Use count == 2", ptr2.use_count() == 2);
    }
}
