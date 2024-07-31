#ifndef MAT3X3_H
#define MAT3X3_H

#include "../vec/vec3f.h"

typedef struct mmat3x3f {
    mvec3f _m[3];
} mmat3x3f;

typedef mmat3x3f mmat3f;

/** @brief Basic */
#define mzero3x3f()                                                                                \
    (mmat3f) {                                                                                     \
        ._m = { mzeros3f(), mzeros3f(), mzeros3f() }                                               \
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

static inline mmat3f mtranspose3x3f(mmat3f _a) {
    _vecm128f_Transpose4(_a._m[0], _a._m[1], _a._m[2], _a._m[3]);
    return _a;
}

/** @brief Arithmetic Matrix */
static inline mmat3f _madd3x3f_mat3f(mmat3f _a, mmat3f _b) {
    return (mmat3f){
        ._m = { madd3f(_a._m[0], _b._m[0]), madd3f(_a._m[1], _b._m[1]), madd3f(_a._m[2], _b._m[2]) }
    };
}

static inline mmat3f _msub3x3f_mat3f(mmat3f _a, mmat3f _b) {
    return (mmat3f){
        ._m = { msub3f(_a._m[0], _b._m[0]), msub3f(_a._m[1], _b._m[1]), msub3f(_a._m[2], _b._m[2]) }
    };
}

static inline mmat3f _mmul3x3f_mat3f(mmat3f _a, mmat3f _b) {
    _vecm128f_Transpose4(_b._m[0], _b._m[1], _b._m[2], _b._m[3]);

    return (mmat3f){
        ._m = { mpack3f(
                    mdot3f(_b._m[0], _a._m[0]), mdot3f(_b._m[1], _a._m[0]),
               mdot3f(_b._m[2], _a._m[0])
                ), mpack3f(
                    mdot3f(_b._m[0], _a._m[1]), mdot3f(_b._m[1], _a._m[1]),
               mdot3f(_b._m[2], _a._m[1])
                ), mpack3f(
                    mdot3f(_b._m[0], _a._m[2]), mdot3f(_b._m[1], _a._m[2]),
               mdot3f(_b._m[2], _a._m[2])
                ) }
    };
}

/** @brief Arithmetic Vector */
static inline mvec3f _mmul3x3f_vec3f(mmat3f _m, mvec3f _v) {
    return mpack3f(mdot3f(_m._m[0], _v), mdot3f(_m._m[1], _v), mdot3f(_m._m[2], _v));
}

#define madd3x3f(_a, _b) _Generic((_b), mmat3f: _madd3x3f_mat3f)(_a, _b)
#define msub3x3f(_a, _b) _Generic((_b), mmat3f: _msub3x3f_mat3f)(_a, _b)
#define mmul3x3f(_a, _b) _Generic((_b), mmat3f: _mmul3x3f_mat3f, mvec3f: _mmul3x3f_vec3f)(_a, _b)

#endif
