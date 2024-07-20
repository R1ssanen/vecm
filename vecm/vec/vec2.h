#ifndef VEC2_H
#define VEC2_H

#include <assert.h>
#include <math.h>
#include <x86intrin.h>

#include "../types.h"

typedef __m128d mvec2f;

/** @brief Initialization */
#define mpack2f(_x, _y) _mm_set_pd((f64)(_y), (f64)(_x))
#define mset2f(_Val)    _mm_set1_pd((f64)(_Val))
#define mzero2f()       _mm_setzero_pd()

static inline mvec2f mload2f(const f64* _Addr) {
    assert(_Addr);
    return _mm_loadu_pd(_Addr);
}

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
    mvec2f _Tmp = mmul2f(_x, _y);
    return (_Tmp[0] + _Tmp[1]);
}

static inline f64    mlen2f(const mvec2f _x) { return sqrt(mdot2f(_x, _x)); }

static inline mvec2f mnorm2f(const mvec2f _x) { return mdiv2f(_x, mset2f(mlen2f(_x))); }

#endif
