#ifndef MAT3X3_H
#define MAT3X3_H

#include "../vec/vec3.h"

typedef struct mmat3x3f {
    mvec3f _m[3];
} mmat3x3f;

typedef mmat3x3f mmat3f;

/** @brief Basic */
#define mzero3x3f()                                                                                \
    (mmat3f) {                                                                                     \
        ._m = { mzero3f(), mzero3f(), mzero3f() }                                                  \
    }

#define mident3x3f()                                                                               \
    (mmat3f) {                                                                                     \
        ._m = { mpack3f(1.f, 0.f, 0.f), mpack3f(0.f, 1.f, 0.f), mpack3f(0.f, 0.f, 1.f) }           \
    }

#define mset3x3f(_s)                                                                               \
    (mmat3f) {                                                                                     \
        ._m = { mset3f(_s), mset3f(_s), mset3f(_s) }                                               \
    }

#define mload3x3f(_addr)                                                                           \
    (mmat3f) {                                                                                     \
        ._m = { mload3f(_addr), mload3f(_addr + 3), mload3f(_addr + 6) }                           \
    }

/** @brief Arithmetic Matrix */
static inline mmat3f _madd3x3f_mat3f(const mmat3f _a, const mmat3f _b) {
    return (mmat3f){
        ._m = { madd3f(_a._m[0], _b._m[0]), madd3f(_a._m[1], _b._m[1]), madd3f(_a._m[2], _b._m[2]) }
    };
}

static inline mmat3f _msub3x3f_mat3f(const mmat3f _a, const mmat3f _b) {
    return (mmat3f){
        ._m = { msub3f(_a._m[0], _b._m[0]), msub3f(_a._m[1], _b._m[1]), msub3f(_a._m[2], _b._m[2]) }
    };
}

static inline mmat3f _mmul3x3f_mat3f(const mmat3f _a, const mmat3f _b) {
    const mvec3f c0 = mpack3f(_b._m[0][0], _b._m[1][0], _b._m[2][0]);
    const mvec3f c1 = mpack3f(_b._m[0][1], _b._m[1][1], _b._m[2][1]);
    const mvec3f c2 = mpack3f(_b._m[0][2], _b._m[1][2], _b._m[2][2]);

    return (mmat3f){
        ._m = { mpack3f(mdot3f(c0, _a._m[0]), mdot3f(c1, _a._m[0]), mdot3f(c2, _a._m[0])),
               mpack3f(mdot3f(c0, _a._m[1]), mdot3f(c1, _a._m[1]), mdot3f(c2, _a._m[1])),
               mpack3f(mdot3f(c0, _a._m[2]), mdot3f(c1, _a._m[2]), mdot3f(c2, _a._m[2])) }
    };
}

/** @brief Arithmetic Vector */
static inline mvec3f _mmul3x3f_vec3f(const mmat3f _m, const mvec3f _v) {
    return mpack3f(mdot3f(_m._m[0], _v), mdot3f(_m._m[1], _v), mdot3f(_m._m[2], _v));
}

#define madd3x3f(_a, _b) _Generic((_b), mmat3f: _madd3x3f_mat3f)(_a, _b)
#define msub3x3f(_a, _b) _Generic((_b), mmat3f: _msub3x3f_mat3f)(_a, _b)
#define mmul3x3f(_a, _b) _Generic((_b), mmat3f: _mmul3x3f_mat3f, mvec3f: _mmul3x3f_vec3f)(_a, _b)

#endif
