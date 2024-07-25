#ifndef VEC4_H
#define VEC4_H

#include <math.h>
#include <x86intrin.h>

#include "../types.h"

typedef __m128 mvec4f;

/** @brief Basic */
#define mpack4f(_x, _y, _z, _w)        _mm_setr_ps(_x, _y, _z, _w)
#define mset4f(_s)                     _mm_set_ps1(_s)
#define mzero4f()                      _mm_setzero_ps()
#define mload4f(_addr)                 _mm_loadu_ps(_addr)
#define mshuffle4f(_v, _x, _y, _z, _w) _mm_shuffle_ps(_v, _v, _MM_SHUFFLE(_w, _z, _y, _x))

/** @brief Arithmetic Vector */
static inline mvec4f _madd_v4f_v4f(const mvec4f _x, const mvec4f _y) { return _mm_add_ps(_x, _y); }

static inline mvec4f _msub_v4f_v4f(const mvec4f _x, const mvec4f _y) { return _mm_sub_ps(_x, _y); }

static inline mvec4f _mmul_v4f_v4f(const mvec4f _x, const mvec4f _y) { return _mm_mul_ps(_x, _y); }

static inline mvec4f _mdiv_v4f_v4f(const mvec4f _x, const mvec4f _y) { return _mm_div_ps(_x, _y); }

/** @brief Arithmetic Scalar */
static inline mvec4f _madd_v4f_f32(const mvec4f _v, f32 _s) { return _mm_add_ps(_v, mset4f(_s)); }

static inline mvec4f _msub_v4f_f32(const mvec4f _v, f32 _s) { return _mm_sub_ps(_v, mset4f(_s)); }

static inline mvec4f _mmul_v4f_f32(const mvec4f _v, f32 _s) { return _mm_mul_ps(_v, mset4f(_s)); }

static inline mvec4f _mdiv_v4f_f32(const mvec4f _v, f32 _s) { return _mm_div_ps(_v, mset4f(_s)); }

/** @brief Arithmetic Generics */
#define madd4f(_a, _b) _Generic((_b), mvec4f: _madd_v4f_v4f, f32: _madd_v4f_f32)(_a, _b)
#define msub4f(_a, _b) _Generic((_b), mvec4f: _msub_v4f_v4f, f32: _msub_v4f_f32)(_a, _b)
#define mmul4f(_a, _b) _Generic((_b), mvec4f: _mmul_v4f_v4f, f32: _mmul_v4f_f32)(_a, _b)
#define mdiv4f(_a, _b) _Generic((_b), mvec4f: _mdiv_v4f_v4f, f32: _mdiv_v4f_f32)(_a, _b)

/** @brief Vector Operations */
static inline f32 mdot4f(const mvec4f _x, const mvec4f _y) {
    __m128 v    = _mm_mul_ps(_x, _y);
    __m128 shuf = _mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 3, 0, 1));
    __m128 sums = _mm_add_ps(v, shuf);
    shuf        = _mm_movehl_ps(shuf, sums);
    sums        = _mm_add_ss(sums, shuf);
    return _mm_cvtss_f32(sums);
}

static inline mvec4f mcross4f(const mvec4f _x, const mvec4f _y) {
    __m128 _x1 = _mm_shuffle_ps(_x, _x, _MM_SHUFFLE(3, 0, 2, 1));
    __m128 _x2 = _mm_shuffle_ps(_x, _x, _MM_SHUFFLE(3, 1, 0, 2));
    __m128 _y1 = _mm_shuffle_ps(_y, _y, _MM_SHUFFLE(3, 1, 0, 2));
    __m128 _y2 = _mm_shuffle_ps(_y, _y, _MM_SHUFFLE(3, 0, 2, 1));

    return _mm_sub_ps(_mm_mul_ps(_x1, _y1), _mm_mul_ps(_x2, _y2));
}

static inline f32    mlen4f(const mvec4f _x) { return sqrtf(mdot4f(_x, _x)); }

static inline mvec4f mnorm4f(const mvec4f _x) { return _mm_div_ps(_x, mset4f(mlen4f(_x))); }

#endif
