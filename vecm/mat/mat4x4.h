#ifndef MAT4X4_H
#define MAT4X4_H

#include "../vec/vec4f.h"

typedef struct mmat4x4f {
    mvec4f _m[4];
} mmat4x4f;

typedef mmat4x4f mmat4f;

/** @brief Basic */
#define mzero4x4f()                                                                                \
    (mmat4f) {                                                                                     \
        ._m = { mzeros4f(), mzeros4f(), mzeros4f(), mzeros4f() }                                   \
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
        ._m = { mload4f(_addr), mload4f(_addr + 4), mload4f(_addr + 8), mload4f(_addr + 12) }      \
    }

static inline mmat4f mtranspose4x4f(mmat4f _a) {
    _vecm128f_Transpose4(_a._m[0], _a._m[1], _a._m[2], _a._m[3]);
    return _a;
}

/** @brief Arithmetic Matrix */
static inline mmat4f _madd4x4f_mat4f(mmat4f _a, mmat4f _b) {
    return (mmat4f){
        ._m = { madd4f(_a._m[0], _b._m[0]), madd4f(_a._m[1], _b._m[1]), madd4f(_a._m[2], _b._m[2]) }
    };
}

static inline mmat4f _msub4x4f_mat4f(mmat4f _a, mmat4f _b) {
    return (mmat4f){
        ._m = { msub4f(_a._m[0], _b._m[0]), msub4f(_a._m[1], _b._m[1]), msub4f(_a._m[2], _b._m[2]) }
    };
}

static inline mmat4f _mmul4x4f_mat4f(mmat4f _a, mmat4f _b) {
    _vecm128f_Transpose4(_b._m[0], _b._m[1], _b._m[2], _b._m[3]);

    return (mmat4f){
        ._m = { mpack4f(
                    mdot4f(_b._m[0], _a._m[0]), mdot4f(_b._m[1], _a._m[0]),
               mdot4f(_b._m[2], _a._m[0]), mdot4f(_b._m[3], _a._m[0])
                ), mpack4f(
                    mdot4f(_b._m[0], _a._m[1]), mdot4f(_b._m[1], _a._m[1]),
               mdot4f(_b._m[2], _a._m[1]), mdot4f(_b._m[3], _a._m[1])
                ), mpack4f(
                    mdot4f(_b._m[0], _a._m[2]), mdot4f(_b._m[1], _a._m[2]),
               mdot4f(_b._m[2], _a._m[2]), mdot4f(_b._m[3], _a._m[2])
                ), mpack4f(
                    mdot4f(_b._m[0], _a._m[3]), mdot4f(_b._m[1], _a._m[3]),
               mdot4f(_b._m[2], _a._m[3]), mdot4f(_b._m[3], _a._m[3])
                ) }
    };
}

/** @brief Arithmetic Vector */
static inline mvec4f _mmul4x4f_vec4f(mmat4f _m, mvec4f _v) {
    return mpack4f(
        mdot4f(_m._m[0], _v), mdot4f(_m._m[1], _v), mdot4f(_m._m[2], _v), mdot4f(_m._m[3], _v)
    );
}

#define madd4x4f(_a, _b) _Generic((_b), mmat4f: _madd4x4f_mat4f)(_a, _b)
#define msub4x4f(_a, _b) _Generic((_b), mmat4f: _msub4x4f_mat4f)(_a, _b)
#define mmul4x4f(_a, _b) _Generic((_b), mmat4f: _mmul4x4f_mat4f, mvec4f: _mmul4x4f_vec4f)(_a, _b)

#endif
