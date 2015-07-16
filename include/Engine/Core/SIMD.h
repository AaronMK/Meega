#ifndef _ENGINE_SSE_H_
#define _ENGINE_SSE_H_

#ifndef __SSE__
#	define __SSE__
#endif

#ifndef __MMX__
#	define __MMX__
#endif

#include <xmmintrin.h>
#include <assert.h>

/**
* Builds a MMShuffle mask for use with the MMShuffle macro.  All parameters must be
* immedietes between 0 and 3 inclusive.
*
* @param A0
*	First index into MMShuffle parameter A.
* @param A1
*	Second index into MMShuffle parameter A.
* @param B0
*	First index into MMShuffle parameter B.
* @param B1
*	Second index into MMShuffle parameter B.
*
* @see MMShuffle
*/
#define ShuffleMask(A0, A1, B0, B1) ((B1<<6) | (B0<<4) | (A1<<2) | A0)

/**
* @def MMShuffle(A, B, Mask)
*	Creates a new Float4 using two components from A and two components from B,
*	using Mask to place components as detailed in ShuffleMask.
*
* @param A
*	A Float4
* @param B
*	A Float4
* @param Mask
*	A mask built using the ShuffleMask macro.
*
* @see ShuffleMask
*/

#define MMShuffle(A, B, Mask) (vec4(_mm_shuffle_ps(A.Vals, B.Vals, Mask)))

#endif // _ENGINE_SSE_H_