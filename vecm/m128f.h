#ifndef M128F_H
#define M128F_H

#include <x86intrin.h>

#include "types.h"

#if defined(__SSE__)
#    define _vecm128f_Transpose4(_a, _b, _c, _d) _MM_TRANSPOSE4_PS(_a, _b, _c, _d)
#    define _vecm128f_Shuffle(_a, _x, _y, _z, _w)                                                  \
        _mm_shuffle_ps(_a, _a, _MM_SHUFFLE(_w, _z, _y, _x))
#    define _vecm128f_Store(_addr, _a)     _mm_storeu_ps(_addr, _a)
#    define _vecm128f_Stream(_addr, _a)    _mm_stream_ps(_addr, _a)
#    define _vecm128f_Max(_a, _b)          _mm_max_ps(_a, _b)
#    define _vecm128f_Min(_a, _b)          _mm_min_ps(_a, _b)
#    define _vecm128f_Pack(_x, _y, _z, _w) _mm_setr_ps(_x, _y, _z, _w)
#    define _vecm128f_Set(_s)              _mm_set1_ps(_s)
#    define _vecm128f_Zeros()              _mm_setzero_ps()
#    define _vecm128f_Movemask(_a)         _mm_movemask_ps(_a)
#    define _vecm128f_And(_a, _b)          _mm_and_ps(_a, _b)
#    define _vecm128f_Nand(_a, _b)         _mm_andnot_ps(_a, _b)
#    define _vecm128f_Or(_a, _b)           _mm_or_ps(_a, _b)
#    define _vecm128f_Xor(_a, _b)          _mm_xor_ps(_a, _b)
#    define _vecm128f_Load(_addr)          _mm_loadu_ps(_addr)
#    define _vecm128f_Load1(_addr)         _mm_load1_ps(_addr)
#    define _vecm128f_Undef()              _mm_undefined_ps()
#    define _vecm128f_Inv(_a)              _mm_rcp_ps(_a)
#    define _vecm128f_InvSqrt(_a)          _mm_rsqrt_ps(_a)
#    define _vecm128f_Sqrt(_a)             _mm_sqrt_ps(_a)
#    define _vecm128f_ToFloat(_a)          _mm_cvtss_f32(_a)

#    define _vecm128f_Equal(_a, _b)        _mm_cmpeq_ps(_a, _b)
#    define _vecm128f_NotEq(_a, _b)        _mm_cmpneq_ps(_a, _b)
#    define _vecm128f_GreatEq(_a, _b)      _mm_cmpge_ps(_a, _b)
#    define _vecm128f_Greater(_a, _b)      _mm_cmpgt_ps(_a, _b)
#    define _vecm128f_LessEq(_a, _b)       _mm_cmple_ps(_a, _b)
#    define _vecm128f_Less(_a, _b)         _mm_cmplt_ps(_a, _b)

#    define _vecm128f_Add(_a, _b)          _mm_add_ps(_a, _b)
#    define _vecm128f_Sub(_a, _b)          _mm_sub_ps(_a, _b)
#    define _vecm128f_Mul(_a, _b)          _mm_mul_ps(_a, _b)
#    define _vecm128f_Div(_a, _b)          _mm_div_ps(_a, _b)
#else
#    define _vecm128f_Transpose4(_a, _b, _c, _d)  VM_ERROR("No SSE instructions.")
#    define _vecm128f_Shuffle(_a, _x, _y, _z, _w) VM_ERROR("No SSE instructions.")
#    define _vecm128f_Store(_addr, _a)            VM_ERROR("No SSE instructions.")
#    define _vecm128f_Stream(_addr, _a)           VM_ERROR("No SSE instructions.")
#    define _vecm128f_Max(_a, _b)                 VM_ERROR("No SSE instructions.")
#    define _vecm128f_Min(_a, _b)                 VM_ERROR("No SSE instructions.")
#    define _vecm128f_Pack(_x, _y, _z, _w)        VM_ERROR("No SSE instructions.")
#    define _vecm128f_Set(_s)                     VM_ERROR("No SSE instructions.")
#    define _vecm128f_Zeros()                     VM_ERROR("No SSE instructions.")
#    define _vecm128f_Movemask(_a)                VM_ERROR("No SSE instructions.")
#    define _vecm128f_And(_a, _b)                 VM_ERROR("No SSE instructions.")
#    define _vecm128f_Nand(_a, _b)                VM_ERROR("No SSE instructions.")
#    define _vecm128f_Or(_a, _b)                  VM_ERROR("No SSE instructions.")
#    define _vecm128f_Xor(_a, _b)                 VM_ERROR("No SSE instructions.")
#    define _vecm128f_Load(_addr)                 VM_ERROR("No SSE instructions.")
#    define _vecm128f_Load1(_addr)                VM_ERROR("No SSE instructions.")
#    define _vecm128f_Undef()                     VM_ERROR("No SSE instructions.")
#    define _vecm128f_Inv(_a)                     VM_ERROR("No SSE instructions.")
#    define _vecm128f_InvSqrt(_a)                 VM_ERROR("No SSE instructions.")
#    define _vecm128f_Sqrt(_a)                    VM_ERROR("No SSE instructions.")
#    define _vecm128f_ToFloat(_a)                 VM_ERROR("No SSE instructions.")

#    define _vecm128f_Equal(_a, _b)               VM_ERROR("No SSE instructions.")
#    define _vecm128f_NotEq(_a, _b)               VM_ERROR("No SSE instructions.")
#    define _vecm128f_GreatEq(_a, _b)             VM_ERROR("No SSE instructions.")
#    define _vecm128f_Greater(_a, _b)             VM_ERROR("No SSE instructions.")
#    define _vecm128f_LessEq(_a, _b)              VM_ERROR("No SSE instructions.")
#    define _vecm128f_Less(_a, _b)                VM_ERROR("No SSE instructions.")

#    define _vecm128f_Add(_a, _b)                 VM_ERROR("No SSE instructions.")
#    define _vecm128f_Sub(_a, _b)                 VM_ERROR("No SSE instructions.")
#    define _vecm128f_Mul(_a, _b)                 VM_ERROR("No SSE instructions.")
#    define _vecm128f_Div(_a, _b)                 VM_ERROR("No SSE instructions.")
#endif

#if defined(__SSE2__)
#    define _vecm128f_From128d(_a) _mm_cvtpd_ps(_a)
#    define _vecm128f_From128i(_a) _mm_castsi128_ps(_a)
#else
#    define _vecm128f_From128i(_a) VM_ERROR("No SSE2 instructions.")
#    define _vecm128f_From128d(_a) VM_ERROR("No SSE2 instructions.")
#endif

#if defined(__SSE3__)
#    define _vecm128f_AddSub(_a, _b)  _mm_addsub_ps(_a, _b)
#    define _vecm128f_HoriAdd(_a, _b) _mm_hadd_ps(_a, _b)
#    define _vecm128f_HoriSub(_a, _b) _mm_hsub_ps(_a, _b)
#else
#    define _vecm128f_AddSub(_a, _b)  VM_ERROR("No SSE3 instructions.")
#    define _vecm128f_HoriAdd(_a, _b) VM_ERROR("No SSE3 instructions.")
#    define _vecm128f_HoriSub(_a, _b) VM_ERROR("No SSE3 instructions.")
#endif

#if defined(__SSE4_1__)
#    define _vecm128f_Blend(_a, _b, _ctrl)     _mm_blend_ps(_a, _b, _ctrl)
#    define _vecm128f_MaskBlend(_a, _b, _mask) _mm_blendv_ps(_a, _b, _mask)
#    define _vecm128f_Extract(_a, _ctrl)       _mm_extract_ps(_a, _ctrl)
#    define _vecm128f_Insert(_a, _b, _ctrl)    _mm_insert_ps(_a, _b, _ctrl)
#    define _vecm128f_Ceil(_a)                 _mm_ceil_ps(_a)
#    define _vecm128f_Floor(_a)                _mm_floor_ps(_a)
#    define _vecm128f_Round(_a, _round)        _mm_round_ps(_a, _round)
#    define _vecm128f_Dot(_a, _b)              _mm_cvtss_f32(_mm_dp_ps(_a, _b, 0xff))
#else
#    define _vecm128f_Blend(_a, _b, _ctrl)     VM_ERROR("No SSE4.1 instructions.")
#    define _vecm128f_MaskBlend(_a, _b, _mask) VM_ERROR("No SSE4.1 instructions.")
#    define _vecm128f_Extract(_a, _ctrl)       VM_ERROR("No SSE4.1 instructions.")
#    define _vecm128f_Insert(_a, _b, _ctrl)    VM_ERROR("No SSE4.1 instructions.")
#    define _vecm128f_Ceil(_a)                 VM_ERROR("No SSE4.1 instructions.")
#    define _vecm128f_Floor(_a)                VM_ERROR("No SSE4.1 instructions.")
#    define _vecm128f_Round(_a, _round)        VM_ERROR("No SSE4.1 instructions.")
#    define _vecm128f_Dot(_a, _b)              VM_ERROR("No SSE4.1 instructions.")
#endif

#if defined(__AVX__)
#    define _vecm128f_Permute(_v, _ctrl)          _mm_permute_ps(_v, _ctrl)
#    define _vecm128f_MaskStore(_addr, _mask, _a) _mm_maskstore_ps(_addr, _mask, _a)
#    define _vecm128f_MaskLoad(_addr, _mask)      _mm_maskload_ps(_addr, _mask)
#    define _vecm128f_Cmp(_a, _b, _ctrl)          _mm_cmp_ps(_a, _b, _ctrl)
#else
#    define _vecm128f_Permute(_v, _ctrl)          VM_ERROR("No AVX instructions.")
#    define _vecm128f_MaskStore(_addr, _mask, _a) VM_ERROR("No AVX instructions.")
#    define _vecm128f_MaskLoad(_addr, _mask)      VM_ERROR("No AVX instructions.")
#    define _vecm128f_Cmp(_a, _b, _ctrl)          VM_ERROR("No AVX instructions.")
#endif

#if defined(__AVX2__)
#    define _vecm128f_Gather(_addr, _idx, _scale) _mm_i32gather_ps(_addr, _idx, _scale)
#    define _vecm128f_MaskGather(_src, _addr, _idx, _mask, _scale)                                 \
        _mm_mask_i32gather_ps(_src, _addr, _idx, _mask, _scale)
#else
#    define _vecm128f_Gather(_addr, _idx, _scale)                  VM_ERROR("No AVX2 instructions.")
#    define _vecm128f_MaskGather(_src, _addr, _idx, _mask, _scale) VM_ERROR("No AVX2 instructions.")
#endif

#endif
