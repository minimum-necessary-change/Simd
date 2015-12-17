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
#include "Simd/SimdMemory.h"
#include "Simd/SimdStore.h"
#include "Simd/SimdExtract.h"

namespace Simd
{
#ifdef SIMD_VSX_ENABLE  
    namespace Vsx
    {
        template <bool align> SIMD_INLINE void AnnProductSum(const float * a, const float * b, size_t offset, v128_f32 & sum)
        {
            v128_f32 _a = Load<align>(a + offset);
            v128_f32 _b = Load<align>(b + offset);
            sum = vec_add(sum, vec_mul(_a, _b));
        }

        template <bool align> SIMD_INLINE void AnnProductSum(const float * a, const float * b, size_t size, float * sum)
        {
            if(align)
                assert(Aligned(a) && Aligned(b));

            *sum = 0;
            size_t partialAlignedSize = AlignLo(size, 4);
            size_t fullAlignedSize = AlignLo(size, 16);
            size_t i = 0;
            if(partialAlignedSize)
            {
                v128_f32 sums[4] = {K_0_0f, K_0_0f, K_0_0f, K_0_0f};
                if(fullAlignedSize)
                {
                    for(; i < fullAlignedSize; i += 16)
                    {
						AnnProductSum<align>(a, b, i, sums[0]);
						AnnProductSum<align>(a, b, i + 4, sums[1]);
						AnnProductSum<align>(a, b, i + 8, sums[2]);
						AnnProductSum<align>(a, b, i + 12, sums[3]);
                    }
                    sums[0] = vec_add(vec_add(sums[0], sums[1]), vec_add(sums[2], sums[3]));
                }
                for(; i < partialAlignedSize; i += 4)
					AnnProductSum<align>(a, b, i, sums[0]);
                *sum += ExtractSum(sums[0]);
            }
            for(; i < size; ++i)
                *sum += a[i]*b[i];
        }

        void AnnProductSum(const float * a, const float * b, size_t size, float * sum)
        {
            if(Aligned(a) && Aligned(b))
				AnnProductSum<true>(a, b, size, sum);
            else
				AnnProductSum<false>(a, b, size, sum);
        }
    }
#endif// SIMD_VSX_ENABLE
}