#ifndef MAT4X4_H
#define MAT4X4_H

#include "../vec/vec4.h"

typedef struct mmat4x4f {
    mvec4f _m[4];
} mmat4x4f;

typedef mmat4x4f mmat4f;

/** @brief Basic */
#define mzero4x4f()                                                                                \
    (mmat4f) {                                                                                     \
        ._m = { mzero4f(), mzero4f(), mzero4f(), mzero4f() }                                       \
    }

#define mident4x4f()                                                                               \
    (mmat4f) {                                                                                     \
        ._m = {                                                                                    \
            mpack4f(1.f, 0.f, 0.f, 0.f),                                                           \
            mpack4f(0.f, 1.f, 0.f, 0.f),                                                           \
            mpack4f(0.f, 0.f, 1.f, 0.f),                                                           \
            mpack4f(0.f, 0.f, 0.f, 1.f)                                                            \
        }                                                                                          \
    }

#define mset4x4f(_s)                                                                               \
    (mmat4f) {                                                                                     \
        ._m = { mset4f(_s), mset4f(_s), mset4f(_s), mset4f(_s) }                                   \
    }

#define mload4x4f(_addr)                                                                           \
    (mmat4f) {                                                                                     \
        ._m = { mload4f(_addr), mload4f(_addr + 3), mload4f(_addr + 6), mload4f(_addr + 9) }       \
    }

/** @brief Arithmetic Matrix */
static inline mmat4f _madd4x4f_mat4f(const mmat4f _a, const mmat4f _b) {
    return (mmat4f){
        ._m = { madd4f(_a._m[0], _b._m[0]), madd4f(_a._m[1], _b._m[1]), madd4f(_a._m[2], _b._m[2]) }
    };
}

static inline mmat4f _msub4x4f_mat4f(const mmat4f _a, const mmat4f _b) {
    return (mmat4f){
        ._m = { msub4f(_a._m[0], _b._m[0]), msub4f(_a._m[1], _b._m[1]), msub4f(_a._m[2], _b._m[2]) }
    };
}

static inline mmat4f _mmul4x4f_mat4f(const mmat4f _a, const mmat4f _b) {
    const mvec4f c0 = mpack4f(_b._m[0][0], _b._m[1][0], _b._m[2][0], _b._m[3][0]);
    const mvec4f c1 = mpack4f(_b._m[0][1], _b._m[1][1], _b._m[2][1], _b._m[3][1]);
    const mvec4f c2 = mpack4f(_b._m[0][2], _b._m[1][2], _b._m[2][2], _b._m[3][2]);
    const mvec4f c3 = mpack4f(_b._m[0][3], _b._m[1][3], _b._m[2][3], _b._m[3][3]);

    return (mmat4f){
        ._m = { mpack4f(
                    mdot4f(c0, _a._m[0]), mdot4f(c1, _a._m[0]), mdot4f(c2, _a._m[0]),
               mdot4f(c3, _a._m[0])
                ), mpack4f(
                    mdot4f(c0, _a._m[1]), mdot4f(c1, _a._m[1]), mdot4f(c2, _a._m[1]),
               mdot4f(c3, _a._m[1])
                ), mpack4f(
                    mdot4f(c0, _a._m[2]), mdot4f(c1, _a._m[2]), mdot4f(c2, _a._m[2]),
               mdot4f(c3, _a._m[2])
                ), mpack4f(
                    mdot4f(c0, _a._m[3]), mdot4f(c1, _a._m[3]), mdot4f(c2, _a._m[3]),
               mdot4f(c3, _a._m[3])
                ) }
    };
}

/** @brief Arithmetic Vector */
static inline mvec4f _mmul4x4f_vec4f(const mmat4f _m, const mvec4f _v) {
    return mpack4f(
        mdot4f(_m._m[0], _v), mdot4f(_m._m[1], _v), mdot4f(_m._m[2], _v), mdot4f(_m._m[3], _v)
    );
}

#define madd4x4f(_a, _b) _Generic((_b), mmat4f: _madd4x4f_mat4f)(_a, _b)
#define msub4x4f(_a, _b) _Generic((_b), mmat4f: _msub4x4f_mat4f)(_a, _b)
#define mmul4x4f(_a, _b) _Generic((_b), mmat4f: _mmul4x4f_mat4f, mvec4f: _mmul4x4f_vec4f)(_a, _b)

#endif
