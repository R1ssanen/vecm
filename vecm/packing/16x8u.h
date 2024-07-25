#ifndef PACK_16X8U_H
#define PACK_16X8U_H

#include <x86intrin.h>

#include "../types.h"

typedef __m128i m16x8u;

/** @brief Basic */
#define mpack16x8u(_a, _b, _c, _d, _e, _f, _g, _h, _i, _j, _k, _l, _m, _n, _o, _p)                 \
    _mm_setr_epi8(_a, _b, _c, _d, _e, _f, _g, _h, _i, _j, _k, _l, _m, _n, _o, _p)
#define mset16x8u(_s)      _mm_set1_epi8(_s)
#define mzero16x8u()       _mm_setzero_si128()

#define mavg16x8u(_a, _b)  _mm_avg_epu8(_a, _b)
#define mmin16x8u(_a, _b)  _mm_min_epu8(_a, _b)
#define mmax16x8u(_a, _b)  _mm_max_epu8(_a, _b)

#define mload16x8u(_addr)  _mm_loadu_si128((__m128i*)_addr)
#define mstore16x8u(_addr) _mm_storeu_si128((__m128i*)_addr)

/** @brief Arithmeric Pack */
static inline m16x8u _madd16x8u_16x8u(const m16x8u _a, const m16x8u _b) {
    return _mm_adds_epu8(_a, _b);
}

static inline m16x8u _msub16x8u_16x8u(const m16x8u _a, const m16x8u _b) {
    return _mm_subs_epu8(_a, _b);
}

/** @brief Arithmeric Scalar */
static inline m16x8u _madd16x8u_u8(const m16x8u _p, u8 _s) {
    return _mm_adds_epu8(_p, mset16x8u(_s));
}

static inline m16x8u _msub16x8u_u8(const m16x8u _p, u8 _s) {
    return _mm_subs_epu8(_p, mset16x8u(_s));
}

#define madd16x8u(_a, _b) _Generic((_b), m16x8u: _madd16x8b_16x8u, u8: _madd16x8u_u8)(_a, _b)
#define msub16x8u(_a, _b) _Generic((_b), m16x8u: _msub16x8b_16x8u, u8: _msub16x8u_u8)(_a, _b)

#endif
