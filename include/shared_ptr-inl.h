#include <cstring>
#include <exception>
#include <iostream>
#include <shared_mutex>

namespace igor
{

// Constructors
template<typename T>
shared_ptr<T>::shared_ptr()
{
    m_shared_obj = new shared_obj();
}

template<typename T>
shared_ptr<T>::shared_ptr(T* const ptr)
{
    if (!ptr)
    {
        throw std::runtime_error("Creation of shared_ptr from null pointer");
    }
    m_shared_obj = new shared_obj;
    m_shared_obj->ptr = ptr;
    m_shared_obj->use_count = 1;
}

template<typename T>
shared_ptr<T>::shared_ptr(shared_ptr<T>&& rh) noexcept
: m_shared_obj(nullptr)
{
    std::cout << "\t<Move Ctor>\n";
    swap(rh);
}

template<typename T>
shared_ptr<T>::shared_ptr(const shared_ptr<T>& rh) noexcept
: m_shared_obj(rh.m_shared_obj)
{
    ++m_shared_obj->use_count;
    std::cout << "\t<Copy Ctor>\n";
}

template<typename T>
shared_ptr<T>::~shared_ptr()
{
    if (!(--m_shared_obj->use_count))
    {
        delete m_shared_obj;
    }
}

// Operators
template<typename T>
shared_ptr<T>::operator bool() const noexcept
{
    return (m_shared_obj->ptr ? true : false);
}
 
template<typename T>
T* shared_ptr<T>::operator ->() const
{
    if (!m_shared_obj->ptr)
    {
        throw std::runtime_error("Attempt to dereference null pointer");
    }
    return m_shared_obj->ptr;
}

template<typename T>
T& shared_ptr<T>::operator *() const
{
    return *this->operator->();
}

template<typename T>
shared_ptr<T>& shared_ptr<T>::operator =(const shared_ptr<T>& rh)
{
    reset();
    this->m_shared_obj = rh.m_shared_obj;
    ++m_shared_obj->use_count;
    return *this;
}

template<typename T>
shared_ptr<T>& shared_ptr<T>::operator =(shared_ptr<T>&& rh) noexcept
{
    std::cout << "\t<Move assignment operator>\n";
    swap(rh);
    return *this;
}

// Observers
template<typename T>
int shared_ptr<T>::use_count() const noexcept
{
    return m_shared_obj->use_count;
}

// Setters
template<typename T>
void shared_ptr<T>::reset() 
{
    if (m_shared_obj->use_count && !--m_shared_obj->use_count)
    {
        if (m_shared_obj->ptr)
        {
            delete m_shared_obj->ptr;
            m_shared_obj->ptr = nullptr;
        }
    }
}

template<typename T>
void shared_ptr<T>::reset(shared_ptr<T>& rh) 
{
    this->operator=(rh);
}

template<typename T>
void shared_ptr<T>::swap(shared_ptr<T>& rh)
{
    std::swap(this->m_shared_obj, rh.m_shared_obj);
}

} // end of namespace igor
