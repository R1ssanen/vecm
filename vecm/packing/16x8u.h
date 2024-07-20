#ifndef PACK_16X8U_H
#define PACK_16X8U_H

#include <assert.h>
#include <x86intrin.h>

#include "../types.h"

typedef __m128i m16x8u;

#define mpack16x8u(_a, _b, _c, _d, _e, _f, _g, _h, _i, _j, _k, _l, _m, _n, _o, _p)                 \
    _mm_set_epi8(                                                                                  \
        (char)(_p), (char)(_o), (char)(_n), (char)(_m), (char)(_l), (char)(_k), (char)(_j),        \
        (char)(_i), (char)(_h), (char)(_g), (char)(_f), (char)(_e), (char)(_d), (char)(_c),        \
        (char)(_b), (char)(_a)                                                                     \
    )
#define mset16x8u(_Val)   _mm_set1_epi8((char)(_Val))
#define mzero16x8u()      _mm_setzero_si128()

#define mavg16x8u(_a, _b) _mm_avg_epu8(_a, _b)
#define mmin16x8u(_a, _b) _mm_min_epu8(_a, _b)
#define mmax16x8u(_a, _b) _mm_max_epu8(_a, _b)

static inline m16x8u mload16x8u(const u8* _Addr) {
    assert(_Addr);
    return _mm_loadu_si128((__m128i*)_Addr);
}

static inline void mstore16x8u(u8* _Addr, const m16x8u _Val) {
    assert(_Addr);
    _mm_storeu_si128((__m128i*)_Addr, _Val);
}

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
