#ifndef MAT3X3_H
#define MAT3X3_H

#include <assert.h>

#include "../vec/vec3.h"

typedef struct mmat3x3 {
    mvec3f _m[3];
} mmat3x3;

typedef mmat3x3 mmat3;

#define mzero3x3f()                                                                                \
    (mmat3) {                                                                                      \
        ._m = { mzero3f(), mzero3f(), mzero3f() }                                                  \
    }

#define mident3x3f()                                                                               \
    (mmat3) {                                                                                      \
        ._m = { mpack3f(1.f, 0.f, 0.f), mpack3f(0.f, 1.f, 0.f), mpack3f(0.f, 0.f, 1.f) }           \
    }

#define mset3x3f(_Val)                                                                             \
    (mmat3) {                                                                                      \
        ._m = { mset3f(_Val), mset3f(_Val), mset3f(_Val) }                                         \
    }

static inline mmat3 mload3x3f(const f32* _Addr) {
    assert(_Addr);
    return (mmat3){
        ._m = { mload3f(_Addr), mload3f(_Addr + 3), mload3f(_Addr + 6) }
    };
}

static inline mmat3 madd3x3f(const mmat3 _a, const mmat3 _b) {
    return (mmat3){
        ._m = { madd3f(_a._m[0], _b._m[0]), madd3f(_a._m[1], _b._m[1]), madd3f(_a._m[2], _b._m[2]) }
    };
}

static inline mmat3 msub3x3f(const mmat3 _a, const mmat3 _b) {
    return (mmat3){
        ._m = { msub3f(_a._m[0], _b._m[0]), msub3f(_a._m[1], _b._m[1]), msub3f(_a._m[2], _b._m[2]) }
    };
}

static inline mmat3 mmul3x3f(const mmat3 _a, const mmat3 _b) {
    const mvec3f c0 = mpack3f(_b._m[0][0], _b._m[1][0], _b._m[2][0]);
    const mvec3f c1 = mpack3f(_b._m[0][1], _b._m[1][1], _b._m[2][1]);
    const mvec3f c2 = mpack3f(_b._m[0][2], _b._m[1][2], _b._m[2][2]);

    return (mmat3){
        ._m = { mpack3f(mdot3f(c0, _a._m[0]), mdot3f(c1, _a._m[0]), mdot3f(c2, _a._m[0])),
               mpack3f(mdot3f(c0, _a._m[1]), mdot3f(c1, _a._m[1]), mdot3f(c2, _a._m[1])),
               mpack3f(mdot3f(c0, _a._m[2]), mdot3f(c1, _a._m[2]), mdot3f(c2, _a._m[2])) }
    };
}

#endif
