/*
 *  Copyright 2008-2011 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include <thrust/detail/config.h>
#include <thrust/system/cpp/detail/tag.h>
#include <thrust/system/omp/memory.h>
#include <thrust/system/cpp/memory.h>
#include <limits>

namespace thrust
{
namespace system
{
namespace omp
{


template<typename T>
  template<typename OtherT>
    reference<T> &
      reference<T>
        ::operator=(const reference<OtherT> &other)
{
  return super_t::operator=(other);
} // end reference::operator=()

template<typename T>
  reference<T> &
    reference<T>
      ::operator=(const value_type &x)
{
  return super_t::operator=(x);
} // end reference::operator=()

template<typename T>
__host__ __device__
void swap(reference<T> a, reference<T> b)
{
  a.swap(b);
} // end swap()

namespace detail
{

// XXX circular #inclusion problems cause the compiler to believe that cpp::malloc
//     is not defined
//     WAR the problem by using adl to call cpp::malloc, which requires it to depend
//     on a template parameter
template<typename Tag>
  pointer<void> malloc_workaround(Tag t, std::size_t n)
{
  return pointer<void>(malloc(t, n));
} // end malloc_workaround()

// XXX circular #inclusion problems cause the compiler to believe that cpp::free
//     is not defined
//     WAR the problem by using adl to call cpp::free, which requires it to depend
//     on a template parameter
template<typename Tag>
  void free_workaround(Tag t, pointer<void> ptr)
{
  free(t, ptr.get());
} // end free_workaround()

} // end detail

inline pointer<void> malloc(std::size_t n)
{
  // XXX this is how we'd like to implement this function,
  //     if not for circular #inclusion problems:
  //
  // return pointer<void>(thrust::system::cpp::malloc(n))
  //
  return detail::malloc_workaround(cpp::tag(), n);
} // end malloc()

inline void free(pointer<void> ptr)
{
  // XXX this is how we'd like to implement this function,
  //     if not for circular #inclusion problems:
  //
  // thrust::system::cpp::free(ptr)
  //
  detail::free_workaround(cpp::tag(), ptr);
} // end free()

} // end omp
} // end system

namespace detail
{

// XXX iterator_facade tries to instantiate the Reference
//     type when computing the answer to is_convertible<Reference,Value>
//     we can't do that at that point because reference
//     is not complete
//     WAR the problem by specializing is_convertible
template<typename T>
  struct is_convertible<thrust::omp::reference<T>, T>
    : thrust::detail::true_type
{};

namespace backend
{

// specialize dereference_result and overload dereference
template<typename> struct dereference_result;

template<typename T>
  struct dereference_result<thrust::omp::pointer<T> >
{
  typedef T& type;
}; // end dereference_result

template<typename T>
  struct dereference_result<thrust::omp::pointer<const T> >
{
  typedef const T& type;
}; // end dereference_result

template<typename T>
  typename dereference_result< thrust::omp::pointer<T> >::type
    dereference(thrust::omp::pointer<T> ptr)
{
  return *ptr.get();
} // end dereference()

template<typename T, typename IndexType>
  typename dereference_result< thrust::omp::pointer<T> >::type
    dereference(thrust::omp::pointer<T> ptr, IndexType n)
{
  return ptr.get()[n];
} // end dereference()

} // end backend
} // end detail
} // end thrust

