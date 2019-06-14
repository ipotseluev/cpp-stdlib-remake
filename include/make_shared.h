#pragma once

#include "shared_ptr.h"

namespace igor
{

template <typename T, typename ... types>
shared_ptr<T> make_shared(const types& ... args)
{
   return shared_ptr<T>(new T(args...));
}

}
