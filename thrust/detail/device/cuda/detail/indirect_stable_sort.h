/*
 *  Copyright 2008-2009 NVIDIA Corporation
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


/*! \file indirect_stable_sort.h
 *  \brief Defines the interface for the indirect stable sort meta algorithms.
 */

#pragma once

namespace thrust
{
namespace detail
{
namespace device
{
namespace cuda
{
namespace detail
{

template<typename RandomAccessIterator,
         typename StrictWeakOrdering>
void indirect_stable_sort(RandomAccessIterator first,
                          RandomAccessIterator last,
                          StrictWeakOrdering comp);
    
template<typename RandomAccessIterator1,
         typename RandomAccessIterator2,
         typename StrictWeakOrdering>
void indirect_stable_sort_by_key(RandomAccessIterator1 keys_begin,
                                 RandomAccessIterator1 keys_end,
                                 RandomAccessIterator2 values_begin,
                                 StrictWeakOrdering comp);

} // end namespace detail
} // end namespace cuda
} // end namespace device
} // end namespace detail
} // end namespace thrust

#include "indirect_stable_sort.inl"
