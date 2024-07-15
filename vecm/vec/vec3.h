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

static inline mvec3f mload3f(const f32* _xddr) {
    assert(_xddr);
    return _mm_loadu_ps(_xddr);
}

/** @brief Arithmetic Math */
#define madd3f(_x, _y) _mm_add_ps(_x, _y)
#define msub3f(_x, _y) _mm_sub_ps(_x, _y)
#define mmul3f(_x, _y) _mm_mul_ps(_x, _y)
#define mdiv3f(_x, _y) _mm_div_ps(_x, _y)

/** @brief Vector Operations */
static inline f32 mdot3f(const mvec3f _x, const mvec3f _y) {
    mvec3f _Tmp = mmul3f(_x, _y);
    return (_Tmp[0] + _Tmp[1] + _Tmp[2]);
}

static inline mvec3f mcross3f(const mvec3f _x, const mvec3f _y) {
    mvec3f _x1 = _mm_shuffle_ps(_x, _x, _MM_SHUFFLE(3, 0, 2, 1));
    mvec3f _x2 = _mm_shuffle_ps(_x, _x, _MM_SHUFFLE(3, 1, 0, 2));
    mvec3f _y1 = _mm_shuffle_ps(_y, _y, _MM_SHUFFLE(3, 1, 0, 2));
    mvec3f _y2 = _mm_shuffle_ps(_y, _y, _MM_SHUFFLE(3, 0, 2, 1));

    return msub3f(mmul3f(_x1, _y1), mmul3f(_x2, _y2));
}

static inline f32    mlen3f(const mvec3f _x) { return sqrtf(mdot3f(_x, _x)); }

static inline mvec3f mnorm3f(const mvec3f _x) { return mdiv3f(_x, mset3f(mlen3f(_x))); }

#endif
