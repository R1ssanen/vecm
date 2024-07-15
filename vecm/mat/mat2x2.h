#ifndef MAT2X2_H
#define MAT2X2_H

#include <assert.h>

#include "../vec/vec2.h"

typedef struct mmat2x2 {
    mvec2f _m[2];
} mmat2x2;

typedef mmat2x2 mmat2;

#define mzero2x2f()                                                                                \
    (mmat2) {                                                                                      \
        ._m = { mzero2f(), mzero2f() }                                                             \
    }

#define mident2x2f()                                                                               \
    (mmat2) {                                                                                      \
        ._m = { mpack2f(1.f, 0.f), mpack2f(0.f, 1.f) }                                             \
    }

#define mset2x2f(_Val)                                                                             \
    (mmat2) {                                                                                      \
        ._m = { mset2f(_Val), mset2f(_Val) }                                                       \
    }

static inline mmat2 mload2x2f(const f64* _Addr) {
    assert(_Addr);
    return (mmat2){
        ._m = { mload2f(_Addr), mload2f(_Addr + 3) }
    };
}

static inline mmat2 madd2x2f(const mmat2 _a, const mmat2 _b) {
    return (mmat2){
        ._m = { madd2f(_a._m[0], _b._m[0]), madd2f(_a._m[1], _b._m[1]) }
    };
}

static inline mmat2 msub2x2f(const mmat2 _a, const mmat2 _b) {
    return (mmat2){
        ._m = { msub2f(_a._m[0], _b._m[0]), msub2f(_a._m[1], _b._m[1]) }
    };
}

static inline mmat2 mmul2x2f(const mmat2 _a, const mmat2 _b) {
    const mvec2f c0 = mpack2f(_b._m[0][0], _b._m[1][0]);
    const mvec2f c1 = mpack2f(_b._m[0][1], _b._m[1][1]);

    return (mmat2){
        ._m = { mpack2f(mdot2f(c0, _a._m[0]), mdot2f(c1, _a._m[0])),
               mpack2f(mdot2f(c0, _a._m[1]), mdot2f(c1, _a._m[1])) }
    };
}

#endif
