#ifndef VEC4_H
#define VEC4_H

#include <assert.h>
#include <math.h>
#include <x86intrin.h>

#include "../types.h"

typedef __m128 mvec4f;

/** @brief Initialization */
#define mpack4f(_x, _y, _z, _w) _mm_set_ps((f32)(_w), (f32)(_z), (f32)(_y), (f32)(_x))
#define mset4f(_Val)            _mm_set_ps1((f32)(_Val))
#define mzero4f()               _mm_setzero_ps()

static inline mvec4f mload4f(const f32* _xddr) {
    assert(_xddr);
    return _mm_loadu_ps(_xddr);
}

/** @brief Arithmetic Math */
#define madd4f(_x, _y) _mm_add_ps(_x, _y)
#define msub4f(_x, _y) _mm_sub_ps(_x, _y)
#define mmul4f(_x, _y) _mm_mul_ps(_x, _y)
#define mdiv4f(_x, _y) _mm_div_ps(_x, _y)

/** @brief Vector Operations */
static inline f32 mdot4f(const mvec4f _x, const mvec4f _y) {
    mvec4f _Tmp = mmul4f(_x, _y);
    return (_Tmp[0] + _Tmp[1] + _Tmp[2] + _Tmp[3]);
}

static inline mvec4f mcross4f(const mvec4f _x, const mvec4f _y) {
    mvec4f _x1 = _mm_shuffle_ps(_x, _x, _MM_SHUFFLE(3, 0, 2, 1));
    mvec4f _x2 = _mm_shuffle_ps(_x, _x, _MM_SHUFFLE(3, 1, 0, 2));
    mvec4f _y1 = _mm_shuffle_ps(_y, _y, _MM_SHUFFLE(3, 1, 0, 2));
    mvec4f _y2 = _mm_shuffle_ps(_y, _y, _MM_SHUFFLE(3, 0, 2, 1));

    return msub4f(mmul4f(_x1, _y1), mmul4f(_x2, _y2));
}

static inline f32    mlen4f(const mvec4f _x) { return sqrtf(mdot4f(_x, _x)); }

static inline mvec4f mnorm4f(const mvec4f _x) { return mdiv4f(_x, mset4f(mlen4f(_x))); }

#endif
