/*
* Simd Library (http://simd.sourceforge.net).
*
* Copyright (c) 2011-2015 Yermalayeu Ihar.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/
#ifndef __SimdAllocator_h__
#define __SimdAllocator_h__

#include "Simd/SimdMemory.h"

namespace Simd
{
    /*! @ingroup cpp_allocator

        \short Aligned memory allocator.

        Performs allocation and deletion of aligned memory.
    */
    struct Allocator
    {
        /*!
            \fn void * Allocate(size_t size, size_t align);

            \short Allocates aligned memory block.

            \note The memory allocated by this function is must be deleted by function Simd::Allocator::Free.

            \param [in] size - a size of required memory block.
            \param [in] align - an align of allocated memory address.
            \return a pointer to allocated memory.
        */
        static void * Allocate(size_t size, size_t align);

        /*!
            \fn void Free(void * p);

            \short Frees aligned memory block.

            \note This function frees a memory allocated by function Simd::Allocator::Allocate.

            \param [in] p - a pointer to the memory to be deleted.
        */
        static void Free(void * p);
    };

    //-------------------------------------------------------------------------

    // struct Allocator implementation:

    SIMD_INLINE void * Allocator::Allocate(size_t size, size_t align)
    {
        return Simd::Allocate(size, align);
    }

    SIMD_INLINE void Allocator::Free(void * p)
    {
        Simd::Free(p);
    }
}

#endif//__SimdAllocator_h__
