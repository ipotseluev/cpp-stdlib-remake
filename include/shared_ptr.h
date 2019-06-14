#pragma once

#include <shared_mutex>

namespace igor
{

template <typename T>
class shared_ptr
{
public:
    shared_ptr();

    // Constructors
    explicit shared_ptr(T* const ptr);
    explicit shared_ptr(shared_ptr<T>&& ptr) noexcept;
    // ?? it's not working when explicit. Why?
    shared_ptr(const shared_ptr<T>& ptr) noexcept;
    ~shared_ptr();

    // Operators
    explicit operator bool() const noexcept;
    T& operator *() const;
    T* operator ->() const;
    shared_ptr<T>& operator =(const shared_ptr<T>& rh);
    shared_ptr<T>& operator =(shared_ptr<T>&& rh) noexcept;

    // Observers
    int use_count() const noexcept;

    // Setters
    void reset();
    void reset(shared_ptr<T>& rh);
    void swap(shared_ptr<T>& rh);

private:
    struct shared_obj
    {
         T* ptr;
         int use_count;
         std::shared_mutex m_sh_mutex;
    };
    shared_obj* m_shared_obj; 
};

} // end of namespace igor

#include "shared_ptr-inl.h"
