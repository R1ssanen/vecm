#ifndef VEC3F_H
#define VEC3F_H

#include <x86intrin.h>

#include "../m128f.h"

typedef __m128 mvec3f;

#define mshuffle3f(_a, _x, _y, _z)  _vecm128f_Shuffle(_a, _x, _y, _z, 3.f)
#define mstore3f(_addr, _a)         _vecm128f_Store(_addr, _a)
#define mstream3f(_addr, _a)        _vecm128f_Stream(_addr, _a)
#define mmax3f(_a, _b)              _vecm128f_Max(_a, _b)
#define mmin3f(_a, _b)              _vecm128f_Min(_a, _b)
#define mpack3f(_x, _y, _z)         _vecm128f_Pack(_x, _y, _z, 0.f)
#define mset3f(_s)                  _vecm128f_Set(_s)
#define mzeros3f()                  _vecm128f_Zeros()
#define mmovemask3f(_a)             _vecm128f_Movemask(_a)
#define mand3f(_a, _b)              _vecm128f_And(_a, _b)
#define mnand3f(_a, _b)             _vecm128f_Nand(_a, _b)
#define mor3f(_a, _b)               _vecm128f_Or(_a, _b)
#define mxor3f(_a, _b)              _vecm128f_Xor(_a, _b)
#define mload3f(_addr)              _vecm128f_Load(_addr)
#define mloadone3f(_addr)           _vecm128f_Load1(_addr)
#define mundef3f()                  _vecm128f_Undef()
#define minv3f(_a)                  _vecm128f_Inv(_a)
#define minvsqrt3f(_a)              _vecm128f_InvSqrt(_a)
#define msqrt3f(_a)                 _vecm128f_Sqrt(_a)
#define mtofloat3f(_a)              _vecm128f_ToFloat(_a)

#define mequal3f(_a, _b)            _vecm128f_Equal(_a, _b)
#define mnoteq3f(_a, _b)            _vecm128f_NotEq(_a, _b)
#define mgreateq3f(_a, _b)          _vecm128f_GreatEq(_a, _b)
#define mgreater3f(_a, _b)          _vecm128f_Greater(_a, _b)
#define mlesseq3f(_a, _b)           _vecm128f_LessEq(_a, _b)
#define mless3f(_a, _b)             _vecm128f_Less(_a, _b)

#define madd3f(_a, _b)              _vecm128f_Add(_a, _b)
#define msub3f(_a, _b)              _vecm128f_Sub(_a, _b)
#define mmul3f(_a, _b)              _vecm128f_Mul(_a, _b)
#define mdiv3f(_a, _b)              _vecm128f_Div(_a, _b)

#define maddsub3f(_a, _b)           _vecm128f_AddSub(_a, _b)
#define mhadd3f(_a, _b)             _vecm128f_HoriAdd(_a, _b)
#define mhsub3f(_a, _b)             _vecm128f_HoriSub(_a, _b)

#define mblend3f(_a, _b, _ctrl)     _vecm128f_Blend(_a, _b, _ctrl)
#define mmaskblend3f(_a, _b, _mask) _vecm128f_MaskBlend(_a, _b, _mask)
#define mextract3f(_a, _ctrl)       _vecm128f_Extract(_a, _ctrl)
#define minsert3f(_a, _b, _ctrl)    _vecm128f_Insert(_a, _b, _ctrl)
#define mceil3f(_a)                 _vecm128f_Ceil(_a)
#define mfloor3f(_a)                _vecm128f_Floor(_a)
#define mround3f(_a, _round)        _vecm128f_Round(_a, _round)

#if defined(__SSE4_1__)
#    define mdot3f(_a, _b) _vecm128f_Dot(_a, _b)
#else
static inline f32 mdot3f(mvec3f _a, mvec3f _b) {
    __m128 v    = _vecm128f_Mul(_a, _b);            // _mm_mul_ps(_a, _b);
    __m128 shuf = _vecm128f_Shuffle(v, 1, 0, 3, 2); //_mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 3, 0, 1));
    __m128 sums = _vecm128f_Add(v, shuf);           //_mm_add_ps(v, shuf);
    shuf        = _mm_movehl_ps(shuf, sums);
    sums        = _mm_add_ss(sums, shuf);
    return _vecm128f_ToFloat(sums); //_mm_cvtss_f32(sums);
}
#endif

#define mpermute3f(_v, _ctrl)          _vecm128f_Permute(_v, _ctrl)
#define mmaskstore3f(_addr, _mask, _a) _vecm128f_MaskStore(_addr, _mask, _a)
#define mmaskload3f(_addr, _mask)      _vecm128f_MaskLoad(_addr, _mask)
#define mcomp3f(_a, _b, _ctrl)         _vecm128f_Cmp(_a, _b, _ctrl)

#define mgather3f(_addr, _idx, _scale) _vecm128f_Gather(_addr, _idx, _scale)
#define mmaskgather3f(_src, _addr, _idx, _mask, _scale)                                            \
    _vecm128f_MaskGather(_src, _addr, _idx, _mask, _scale)

static inline mvec3f mcross3f(mvec3f _a, mvec3f _b) {
    __m128 _x1 = _vecm128f_Shuffle(_a, 1, 2, 0, 3);
    __m128 _x2 = _vecm128f_Shuffle(_a, 2, 0, 1, 3);
    __m128 _y1 = _vecm128f_Shuffle(_b, 2, 0, 1, 3);
    __m128 _y2 = _vecm128f_Shuffle(_b, 1, 2, 0, 3);

    return _vecm128f_Sub(_vecm128f_Mul(_x1, _y1), _vecm128f_Mul(_x2, _y2));
}

f32                  sqrtf(f32);

static inline f32    mlen3f(const mvec3f _x) { return sqrtf(mdot3f(_x, _x)); }

static inline mvec3f mnorm3f(const mvec3f _x) { return _vecm128f_Div(_x, mset3f(mlen3f(_x))); }

#endif
