#ifndef MAT2X2_H
#define MAT2X2_H

#include <assert.h>

#include "../vec/vec2.h"

typedef struct mmat2x2f {
    mvec2f _m[2];
} mmat2x2f;

typedef mmat2x2f mmat2f;

#define mzero2x2f()                                                                                \
    (mmat2f) {                                                                                     \
        ._m = { mzero2f(), mzero2f() }                                                             \
    }

#define mident2x2f()                                                                               \
    (mmat2f) {                                                                                     \
        ._m = { mpack2f(1.f, 0.f), mpack2f(0.f, 1.f) }                                             \
    }

#define mset2x2f(_Val)                                                                             \
    (mmat2f) {                                                                                     \
        ._m = { mset2f(_Val), mset2f(_Val) }                                                       \
    }

static inline mmat2f mload2x2f(const f64* _Addr) {
    assert(_Addr);
    return (mmat2f){
        ._m = { mload2f(_Addr), mload2f(_Addr + 3) }
    };
}

/** @brief Arithmetic Matrix */
static inline mmat2f _madd2x2f_mat2f(const mmat2f _a, const mmat2f _b) {
    return (mmat2f){
        ._m = { madd2f(_a._m[0], _b._m[0]), madd2f(_a._m[1], _b._m[1]) }
    };
}

static inline mmat2f _msub2x2f_mat2f(const mmat2f _a, const mmat2f _b) {
    return (mmat2f){
        ._m = { msub2f(_a._m[0], _b._m[0]), msub2f(_a._m[1], _b._m[1]) }
    };
}

static inline mmat2f _mmul2x2f_mat2f(const mmat2f _a, const mmat2f _b) {
    const mvec2f c0 = mpack2f(_b._m[0][0], _b._m[1][0]);
    const mvec2f c1 = mpack2f(_b._m[0][1], _b._m[1][1]);

    return (mmat2f){
        ._m = { mpack2f(mdot2f(c0, _a._m[0]), mdot2f(c1, _a._m[0])),
               mpack2f(mdot2f(c0, _a._m[1]), mdot2f(c1, _a._m[1])) }
    };
}

/** @brief Arithmetic Vector */
static inline mvec2f _mmul2x2f_vec2f(const mmat2f _m, const mvec2f _v) {
    return mpack2f(mdot2f(_m._m[0], _v), mdot2f(_m._m[1], _v));
}

#define madd2x2f(_a, _b) _Generic((_b), mmat2f: _madd2x2f_mat2f)(_a, _b)
#define msub2x2f(_a, _b) _Generic((_b), mmat2f: _msub2x2f_mat2f)(_a, _b)
#define mmul2x2f(_a, _b) _Generic((_b), mmat2f: _mmul2x2f_mat2f, mvec2f: _mmul2x2f_vec2f)(_a, _b)

#endif
