#ifndef VEC2_H
#define VEC2_H

#include <math.h>
#include <x86intrin.h>

#include "../types.h"

typedef __m128d mvec2f;

/** @brief Initialization */
#define mpack2f(_x, _y)        _mm_setr_pd(_x, _y)
#define mset2f(_s)             _mm_set1_pd(_s)
#define mzero2f()              _mm_setzero_pd()
#define mload2f(_addr)         _mm_loadu_pd(_addr)
#define mshuffle2f(_v, _x, _y) _mm_shuffle_pd(_v, _v, _MM_SHUFFLE(3, 2, _y, _x))

/** @brief Arithmetic Vector */
static inline mvec2f _madd_v2f_v2f(const mvec2f _x, const mvec2f _y) { return _mm_add_pd(_x, _y); }

static inline mvec2f _msub_v2f_v2f(const mvec2f _x, const mvec2f _y) { return _mm_sub_pd(_x, _y); }

static inline mvec2f _mmul_v2f_v2f(const mvec2f _x, const mvec2f _y) { return _mm_mul_pd(_x, _y); }

static inline mvec2f _mdiv_v2f_v2f(const mvec2f _x, const mvec2f _y) { return _mm_div_pd(_x, _y); }

/** @brief Arithmetic Scalar */
static inline mvec2f _madd_v2f_f32(const mvec2f _v, f32 _s) { return _mm_add_pd(_v, mset2f(_s)); }

static inline mvec2f _msub_v2f_f32(const mvec2f _v, f32 _s) { return _mm_sub_pd(_v, mset2f(_s)); }

static inline mvec2f _mmul_v2f_f32(const mvec2f _v, f32 _s) { return _mm_mul_pd(_v, mset2f(_s)); }

static inline mvec2f _mdiv_v2f_f32(const mvec2f _v, f32 _s) { return _mm_div_pd(_v, mset2f(_s)); }

/** @brief Arithmetic Generics */
#define madd2f(_a, _b) _Generic((_b), mvec2f: _madd_v2f_v2f, f32: _madd_v2f_f32)(_a, _b)
#define msub2f(_a, _b) _Generic((_b), mvec2f: _msub_v2f_v2f, f32: _msub_v2f_f32)(_a, _b)
#define mmul2f(_a, _b) _Generic((_b), mvec2f: _mmul_v2f_v2f, f32: _mmul_v2f_f32)(_a, _b)
#define mdiv2f(_a, _b) _Generic((_b), mvec2f: _mdiv_v2f_v2f, f32: _mdiv_v2f_f32)(_a, _b)

/** @brief Vector Operations */
static inline f64 mdot2f(const mvec2f _x, const mvec2f _y) {
    __m128d v       = _mm_mul_pd(_x, _y);
    __m128  undef   = _mm_undefined_ps();
    __m128  shuftmp = _mm_movehl_ps(undef, _mm_castpd_ps(v));
    __m128d shuf    = _mm_castps_pd(shuftmp);
    return _mm_cvtsd_f64(_mm_add_sd(v, shuf));
}

static inline f64    mlen2f(const mvec2f _x) { return sqrt(mdot2f(_x, _x)); }

static inline mvec2f mnorm2f(const mvec2f _x) { return _mm_div_pd(_x, mset2f(mlen2f(_x))); }

#endif
