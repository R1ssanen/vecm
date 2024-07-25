#ifndef VEC3_H
#define VEC3_H

#include <math.h>
#include <x86intrin.h>

#include "../types.h"

typedef __m128 mvec3f;

/** @brief Basic */
#define mpack3f(_x, _y, _z)        _mm_setr_ps(_x, _y, _z, 0.f)
#define mset3f(_s)                 _mm_set_ps1(_s)
#define mzero3f()                  _mm_setzero_ps()
#define mload3f(_addr)             _mm_loadu_ps(_addr)
#define mshuffle3f(_v, _x, _y, _z) _mm_shuffle_ps(_v, _v, _MM_SHUFFLE(3, _z, _y, _x))

/** @brief Arithmetic Vector */
static inline mvec3f _madd_v3f_v3f(const mvec3f _x, const mvec3f _y) { return _mm_add_ps(_x, _y); }

static inline mvec3f _msub_v3f_v3f(const mvec3f _x, const mvec3f _y) { return _mm_sub_ps(_x, _y); }

static inline mvec3f _mmul_v3f_v3f(const mvec3f _x, const mvec3f _y) { return _mm_mul_ps(_x, _y); }

static inline mvec3f _mdiv_v3f_v3f(const mvec3f _x, const mvec3f _y) { return _mm_div_ps(_x, _y); }

/** @brief Arithmetic Scalar */
static inline mvec3f _madd_v3f_f32(const mvec3f _v, f32 _s) { return _mm_add_ps(_v, mset3f(_s)); }

static inline mvec3f _msub_v3f_f32(const mvec3f _v, f32 _s) { return _mm_sub_ps(_v, mset3f(_s)); }

static inline mvec3f _mmul_v3f_f32(const mvec3f _v, f32 _s) { return _mm_mul_ps(_v, mset3f(_s)); }

static inline mvec3f _mdiv_v3f_f32(const mvec3f _v, f32 _s) { return _mm_div_ps(_v, mset3f(_s)); }

/** @brief Arithmetic Generics */
#define madd3f(_a, _b) _Generic((_b), mvec3f: _madd_v3f_v3f, f32: _madd_v3f_f32)(_a, _b)
#define msub3f(_a, _b) _Generic((_b), mvec3f: _msub_v3f_v3f, f32: _msub_v3f_f32)(_a, _b)
#define mmul3f(_a, _b) _Generic((_b), mvec3f: _mmul_v3f_v3f, f32: _mmul_v3f_f32)(_a, _b)
#define mdiv3f(_a, _b) _Generic((_b), mvec3f: _mdiv_v3f_v3f, f32: _mdiv_v3f_f32)(_a, _b)

/** @brief Vector Operations */
static inline f32 mdot3f(const mvec3f _x, const mvec3f _y) {
    __m128 v    = _mm_mul_ps(_x, _y);
    __m128 shuf = _mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 3, 0, 1));
    __m128 sums = _mm_add_ps(v, shuf);
    shuf        = _mm_movehl_ps(shuf, sums);
    sums        = _mm_add_ss(sums, shuf);
    return _mm_cvtss_f32(sums);
}

static inline mvec3f mcross3f(const mvec3f _x, const mvec3f _y) {
    __m128 _x1 = _mm_shuffle_ps(_x, _x, _MM_SHUFFLE(3, 0, 2, 1));
    __m128 _x2 = _mm_shuffle_ps(_x, _x, _MM_SHUFFLE(3, 1, 0, 2));
    __m128 _y1 = _mm_shuffle_ps(_y, _y, _MM_SHUFFLE(3, 1, 0, 2));
    __m128 _y2 = _mm_shuffle_ps(_y, _y, _MM_SHUFFLE(3, 0, 2, 1));

    return _mm_sub_ps(_mm_mul_ps(_x1, _y1), _mm_mul_ps(_x2, _y2));
}

static inline f32    mlen3f(const mvec3f _x) { return sqrtf(mdot3f(_x, _x)); }

static inline mvec3f mnorm3f(const mvec3f _x) { return _mm_div_ps(_x, mset3f(mlen3f(_x))); }

#endif
