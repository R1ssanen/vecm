#ifndef PACK_4X32U_H
#define PACK_4X32U_H

#include <assert.h>
#include <x86intrin.h>

#include "../types.h"

typedef __m128i m4x32u;

#define mpack4x32u(_x, _y, _z, _w) _mm_set_epi32((i32)(_w), (i32)(_z), (i32)(_y), (i32)(_x))
#define mset4x32u(_Val)            _mm_set1_epi32((i32)(_Val))
#define mzero4x32u()               _mm_setzero_si128()

static inline m4x32u mload4x32u(const u32* _Addr) {
    assert(_Addr);
    return _mm_loadu_si128((__m128i*)_Addr);
}

static inline void mstore4x32u(u32* _Addr, const m4x32u _Val) {
    assert(_Addr);
    _mm_storeu_si128((__m128i*)_Addr, _Val);
}

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
