#ifndef PACK_4X32U_H
#define PACK_4X32U_H

#include <x86intrin.h>

#include "../types.h"

typedef __m128i m4x32u;

/** @brief Basic */
#define mpack4x32u(_x, _y, _z, _w) _mm_setr_epi32(_x, _y, _z, _w)
#define mset4x32u(_s)              _mm_set1_epi32(_s)
#define mzero4x32u()               _mm_setzero_si128()

#define mload4x32u(_addr)          _mm_loadu_si128((__m128i*)_addr)
#define mstore4x32u(_addr)         _mm_storeu_si128((__m128i*)_addr)

/** @brief Arithmeric Pack */
static inline m4x32u _madd4x32u_4x32u(const m4x32u _a, const m4x32u _b) {
    return _mm_add_epi32(_a, _b);
}

static inline m4x32u _msub4x32u_4x32u(const m4x32u _a, const m4x32u _b) {
    return _mm_sub_epi32(_a, _b);
}

/** @brief Arithmeric Scalar */
static inline m4x32u _madd4x32u_u32(const m4x32u _p, u32 _s) {
    return _mm_add_epi32(_p, mset4x32u(_s));
}

static inline m4x32u _msub4x32u_u32(const m4x32u _p, u32 _s) {
    return _mm_sub_epi32(_p, mset4x32u(_s));
}

#define madd4x32u(_a, _b) _Generic((_b), m4x32u: _madd4x32u_4x32u, u32: _madd4x32u_u32)(_a, _b)
#define msub4x32u(_a, _b) _Generic((_b), m4x32u: _msub4x32u_4x32u, u32: _msub4x32u_u32)(_a, _b)

#endif
