#ifndef VEC4f_H
#define VEC4f_H

#include <x86intrin.h>

#include "../m128f.h"

typedef __m128 mvec4f;

#define mshuffle4f(_a, _x, _y, _z, _w) _vecm128f_Shuffle(_a, _x, _y, _z, _w)
#define mstore4f(_addr, _a)            _vecm128f_Store(_addr, _a)
#define mstream4f(_addr, _a)           _vecm128f_Stream(_addr, _a)
#define mmax4f(_a, _b)                 _vecm128f_Max(_a, _b)
#define mmin4f(_a, _b)                 _vecm128f_Min(_a, _b)
#define mpack4f(_x, _y, _z, _w)        _vecm128f_Pack(_x, _y, _z, _w)
#define mset4f(_s)                     _vecm128f_Set(_s)
#define mzeros4f()                     _vecm128f_Zeros()
#define mmovemask4f(_a)                _vecm128f_Movemask(_a)
#define mand4f(_a, _b)                 _vecm128f_And(_a, _b)
#define mnand4f(_a, _b)                _vecm128f_Nand(_a, _b)
#define mor4f(_a, _b)                  _vecm128f_Or(_a, _b)
#define mxor4f(_a, _b)                 _vecm128f_Xor(_a, _b)
#define mload4f(_addr)                 _vecm128f_Load(_addr)
#define mloadone4f(_addr)              _vecm128f_Load1(_addr)
#define mundef4f()                     _vecm128f_Undef()
#define minv4f(_a)                     _vecm128f_Inv(_a)
#define minvsqrt4f(_a)                 _vecm128f_InvSqrt(_a)
#define msqrt4f(_a)                    _vecm128f_Sqrt(_a)
#define mtofloat4f(_a)                 _vecm128f_ToFloat(_a)

#define mequal4f(_a, _b)               _vecm128f_Equal(_a, _b)
#define mnoteq4f(_a, _b)               _vecm128f_NotEq(_a, _b)
#define mgreateq4f(_a, _b)             _vecm128f_GreatEq(_a, _b)
#define mgreater4f(_a, _b)             _vecm128f_Greater(_a, _b)
#define mlesseq4f(_a, _b)              _vecm128f_LessEq(_a, _b)
#define mless4f(_a, _b)                _vecm128f_Less(_a, _b)

#define madd4f(_a, _b)                 _vecm128f_Add(_a, _b)
#define msub4f(_a, _b)                 _vecm128f_Sub(_a, _b)
#define mmul4f(_a, _b)                 _vecm128f_Mul(_a, _b)
#define mdiv4f(_a, _b)                 _vecm128f_Div(_a, _b)

#define maddsub4f(_a, _b)              _vecm128f_AddSub(_a, _b)
#define mhadd4f(_a, _b)                _vecm128f_HoriAdd(_a, _b)
#define mhsub4f(_a, _b)                _vecm128f_HoriSub(_a, _b)

#define mblend4f(_a, _b, _ctrl)        _vecm128f_Blend(_a, _b, _ctrl)
#define mmaskblend4f(_a, _b, _mask)    _vecm128f_MaskBlend(_a, _b, _mask)
#define mextract4f(_a, _ctrl)          _vecm128f_Extract(_a, _ctrl)
#define minsert4f(_a, _b, _ctrl)       _vecm128f_Insert(_a, _b, _ctrl)
#define mceil4f(_a)                    _vecm128f_Ceil(_a)
#define mfloor4f(_a)                   _vecm128f_Floor(_a)
#define mround4f(_a, _round)           _vecm128f_Round(_a, _round)

#if defined(__SSE4_1__)
//    WARN: Might also be slower
#    define mdot4f(_a, _b) _vecm128f_Dot(_a, _b)
#else
static inline f32 mdot4f(mvec4f _a, mvec4f _b) {
    __m128 v    = _vecm128f_Mul(_a, _b);            // _mm_mul_ps(_a, _b);
    __m128 shuf = _vecm128f_Shuffle(v, 1, 0, 3, 2); //_mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 3, 0, 1));
    __m128 sums = _vecm128f_Add(v, shuf);           //_mm_add_ps(v, shuf);
    shuf        = _mm_movehl_ps(shuf, sums);
    sums        = _mm_add_ss(sums, shuf);
    return _vecm128f_ToFloat(sums); //_mm_cvtss_f32(sums);
}
#endif

#define mpermute4f(_v, _ctrl)          _vecm128f_Permute(_v, _ctrl)
#define mmaskstore4f(_addr, _mask, _a) _vecm128f_MaskStore(_addr, _mask, _a)
#define mmaskload4f(_addr, _mask)      _vecm128f_MaskLoad(_addr, _mask)
#define mcomp4f(_a, _b, _ctrl)         _vecm128f_Cmp(_a, _b, _ctrl)

#define mgather4f(_addr, _idx, _scale) _vecm128f_Gather(_addr, _idx, _scale)
#define mmaskgather4f(_src, _addr, _idx, _mask, _scale)                                            \
    _vecm128f_MaskGather(_src, _addr, _idx, _mask, _scale)

static inline mvec4f mcross4f(mvec4f _a, mvec4f _b) {
    __m128 _x1 = _vecm128f_Shuffle(_a, 1, 2, 0, 3);
    __m128 _x2 = _vecm128f_Shuffle(_a, 2, 0, 1, 3);
    __m128 _y1 = _vecm128f_Shuffle(_b, 2, 0, 1, 3);
    __m128 _y2 = _vecm128f_Shuffle(_b, 1, 2, 0, 3);

    return _vecm128f_Sub(_vecm128f_Mul(_x1, _y1), _vecm128f_Mul(_x2, _y2));
}

f32                  sqrtf(f32);

static inline f32    mlen4f(const mvec4f _x) { return sqrtf(mdot4f(_x, _x)); }

static inline mvec4f mnorm4f(const mvec4f _x) { return _vecm128f_Div(_x, mset4f(mlen4f(_x))); }

#endif
