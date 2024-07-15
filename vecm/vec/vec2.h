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

static inline mvec2f mload2f(const f64* _xddr) {
    assert(_xddr);
    return _mm_loadu_pd(_xddr);
}

/** @brief Arithmetic Math */
#define madd2f(_x, _y) _mm_add_pd(_x, _y)
#define msub2f(_x, _y) _mm_sub_pd(_x, _y)
#define mmul2f(_x, _y) _mm_mul_pd(_x, _y)
#define mdiv2f(_x, _y) _mm_div_pd(_x, _y)

/** @brief Vector Operations */
static inline f64 mdot2f(const mvec2f _x, const mvec2f _y) {
    mvec2f _Tmp = mmul2f(_x, _y);
    return (_Tmp[0] + _Tmp[1]);
}

static inline f64    mlen2f(const mvec2f _x) { return sqrt(mdot2f(_x, _x)); }

static inline mvec2f mnorm2f(const mvec2f _x) { return mdiv2f(_x, mset2f(mlen2f(_x))); }

#endif
