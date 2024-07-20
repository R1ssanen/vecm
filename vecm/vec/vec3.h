#ifndef VEC3_H
#define VEC3_H

#include <assert.h>
#include <math.h>
#include <x86intrin.h>

#include "../types.h"

typedef __m128 mvec3f;

/** @brief Initialization */
#define mpack3f(_x, _y, _z) _mm_set_ps(1.f, (f32)(_z), (f32)(_y), (f32)(_x))
#define mset3f(_Val)        _mm_set_ps1((f32)(_Val))
#define mzero3f()           _mm_setzero_ps()

static inline mvec3f mload3f(const f32* _Addr) {
    assert(_Addr);
    return _mm_loadu_ps(_Addr);
}

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
    mvec3f _Tmp = _mmul_v3f_v3f(_x, _y);
    return (_Tmp[0] + _Tmp[1] + _Tmp[2]);
}

static inline mvec3f mcross3f(const mvec3f _x, const mvec3f _y) {
    mvec3f _x1 = _mm_shuffle_ps(_x, _x, _MM_SHUFFLE(3, 0, 2, 1));
    mvec3f _x2 = _mm_shuffle_ps(_x, _x, _MM_SHUFFLE(3, 1, 0, 2));
    mvec3f _y1 = _mm_shuffle_ps(_y, _y, _MM_SHUFFLE(3, 1, 0, 2));
    mvec3f _y2 = _mm_shuffle_ps(_y, _y, _MM_SHUFFLE(3, 0, 2, 1));

    return _msub_v3f_v3f(_mmul_v3f_v3f(_x1, _y1), _mmul_v3f_v3f(_x2, _y2));
}

static inline f32    mlen3f(const mvec3f _x) { return sqrtf(mdot3f(_x, _x)); }

static inline mvec3f mnorm3f(const mvec3f _x) { return _mdiv_v3f_v3f(_x, mset3f(mlen3f(_x))); }

#endif
