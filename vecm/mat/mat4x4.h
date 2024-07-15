#ifndef MAT4X4_H
#define MAT4X4_H

#include <assert.h>

#include "../vec/vec4.h"

typedef struct mmat4x4 {
    mvec4f _m[4];
} mmat4x4;

typedef mmat4x4 mmat4;

#define mzero4x4f()                                                                                \
    (mmat4) {                                                                                      \
        ._m = { mzero4f(), mzero4f(), mzero4f(), mzero4f() }                                       \
    }

#define mident4x4f()                                                                               \
    (mmat4) {                                                                                      \
        ._m = {                                                                                    \
            mpack4f(1.f, 0.f, 0.f, 0.f),                                                           \
            mpack4f(0.f, 1.f, 0.f, 0.f),                                                           \
            mpack4f(0.f, 0.f, 1.f, 0.f),                                                           \
            mpack4f(0.f, 0.f, 0.f, 1.f)                                                            \
        }                                                                                          \
    }

#define mset4x4f(_Val)                                                                             \
    (mmat4) {                                                                                      \
        ._m = { mset4f(_Val), mset4f(_Val), mset4f(_Val), mset4f(_Val) }                           \
    }

static inline mmat4 mload4x4f(const f32* _Addr) {
    assert(_Addr);
    return (mmat4){
        ._m = { mload4f(_Addr), mload4f(_Addr + 3), mload4f(_Addr + 6), mload4f(_Addr + 9) }
    };
}

static inline mmat4 madd4x4f(const mmat4 _a, const mmat4 _b) {
    return (mmat4){
        ._m = { madd4f(_a._m[0], _b._m[0]), madd4f(_a._m[1], _b._m[1]), madd4f(_a._m[2], _b._m[2]),
               madd4f(_a._m[3], _b._m[3]) }
    };
}

static inline mmat4 msub4x4f(const mmat4 _a, const mmat4 _b) {
    return (mmat4){
        ._m = { msub4f(_a._m[0], _b._m[0]), msub4f(_a._m[1], _b._m[1]), msub4f(_a._m[2], _b._m[2]),
               msub4f(_a._m[3], _b._m[3]) }
    };
}

static inline mmat4 mmul4x4f(const mmat4 _a, const mmat4 _b) {
    const mvec4f c0 = mpack4f(_b._m[0][0], _b._m[1][0], _b._m[2][0], _b._m[3][0]);
    const mvec4f c1 = mpack4f(_b._m[0][1], _b._m[1][1], _b._m[2][1], _b._m[3][1]);
    const mvec4f c2 = mpack4f(_b._m[0][2], _b._m[1][2], _b._m[2][2], _b._m[3][2]);
    const mvec4f c3 = mpack4f(_b._m[0][3], _b._m[1][3], _b._m[2][3], _b._m[3][3]);

    return (mmat4){
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

#endif
