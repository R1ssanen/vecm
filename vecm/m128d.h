#ifndef M128D_H
#define M128D_H

#include <x86intrin.h>

#include "types.h"

#if defined(__SSE__)
#    define _vecm128d_Shuffle(_a, _x, _y) _mm_shuffle_pd(_a, _a, _MM_SHUFFLE(3, 2, _y, _x))
#    define _vecm128d_Store(_addr, _a)    _mm_storeu_pd(_addr, _a)
#    define _vecm128d_Stream(_addr, _a)   _mm_stream_pd(_addr, _a)
#    define _vecm128d_Max(_a, _b)         _mm_max_pd(_a, _b)
#    define _vecm128d_Min(_a, _b)         _mm_min_pd(_a, _b)
#    define _vecm128d_Pack(_x, _y)        _mm_setr_pd(_x, _y)
#    define _vecm128d_Set(_s)             _mm_set1_pd(_s)
#    define _vecm128d_Zeros()             _mm_setzero_pd()
#    define _vecm128d_Movemask(_a)        _mm_movemask_pd(_a)
#    define _vecm128d_And(_a, _b)         _mm_and_pd(_a, _b)
#    define _vecm128d_Nand(_a, _b)        _mm_andnot_pd(_a, _b)
#    define _vecm128d_Or(_a, _b)          _mm_or_pd(_a, _b)
#    define _vecm128d_Xor(_a, _b)         _mm_xor_pd(_a, _b)
#    define _vecm128d_Load(_addr)         _mm_loadu_pd(_addr)
#    define _vecm128d_Load1(_addr)        _mm_load1_pd(_addr)
#    define _vecm128d_Undef()             _mm_undefined_pd()
#    define _vecm128d_Inv(_a)             _mm_rcp_pd(_a)
#    define _vecm128d_InvSqrt(_a)         _mm_rsqrt_pd(_a)
#    define _vecm128d_Sqrt(_a)            _mm_sqrt_pd(_a)
#    define _vecm128d_ToDouble(_a)        _mm_cvtss_f64(_a)

#    define _vecm128d_Equal(_a, _b)       _mm_cmpeq_pd(_a, _b)
#    define _vecm128d_NotEq(_a, _b)       _mm_cmpneq_pd(_a, _b)
#    define _vecm128d_GreatEq(_a, _b)     _mm_cmpge_pd(_a, _b)
#    define _vecm128d_Greater(_a, _b)     _mm_cmpgt_pd(_a, _b)
#    define _vecm128d_LessEq(_a, _b)      _mm_cmple_pd(_a, _b)
#    define _vecm128d_Less(_a, _b)        _mm_cmplt_pd(_a, _b)

#    define _vecm128d_Add(_a, _b)         _mm_add_pd(_a, _b)
#    define _vecm128d_Sub(_a, _b)         _mm_sub_pd(_a, _b)
#    define _vecm128d_Mul(_a, _b)         _mm_mul_pd(_a, _b)
#    define _vecm128d_Div(_a, _b)         _mm_div_pd(_a, _b)
#else
#    define _vecm128d_Transpose4(_a, _b, _c, _d)  VM_ERROR("No SSE instructions.")
#    define _vecm128d_Shuffle(_a, _x, _y, _z, _w) VM_ERROR("No SSE instructions.")
#    define _vecm128d_Store(_addr, _a)            VM_ERROR("No SSE instructions.")
#    define _vecm128d_Stream(_addr, _a)           VM_ERROR("No SSE instructions.")
#    define _vecm128d_Max(_a, _b)                 VM_ERROR("No SSE instructions.")
#    define _vecm128d_Min(_a, _b)                 VM_ERROR("No SSE instructions.")
#    define _vecm128d_Pack(_x, _y, _z, _w)        VM_ERROR("No SSE instructions.")
#    define _vecm128d_Set(_s)                     VM_ERROR("No SSE instructions.")
#    define _vecm128d_Zeros()                     VM_ERROR("No SSE instructions.")
#    define _vecm128d_Movemask(_a)                VM_ERROR("No SSE instructions.")
#    define _vecm128d_And(_a, _b)                 VM_ERROR("No SSE instructions.")
#    define _vecm128d_Nand(_a, _b)                VM_ERROR("No SSE instructions.")
#    define _vecm128d_Or(_a, _b)                  VM_ERROR("No SSE instructions.")
#    define _vecm128d_Xor(_a, _b)                 VM_ERROR("No SSE instructions.")
#    define _vecm128d_Load(_addr)                 VM_ERROR("No SSE instructions.")
#    define _vecm128d_Load1(_addr)                VM_ERROR("No SSE instructions.")
#    define _vecm128d_Undef()                     VM_ERROR("No SSE instructions.")
#    define _vecm128d_Inv(_a)                     VM_ERROR("No SSE instructions.")
#    define _vecm128d_InvSqrt(_a)                 VM_ERROR("No SSE instructions.")
#    define _vecm128d_Sqrt(_a)                    VM_ERROR("No SSE instructions.")
#    define _vecm128d_ToFloat(_a)                 VM_ERROR("No SSE instructions.")

#    define _vecm128d_Equal(_a, _b)               VM_ERROR("No SSE instructions.")
#    define _vecm128d_NotEq(_a, _b)               VM_ERROR("No SSE instructions.")
#    define _vecm128d_GreatEq(_a, _b)             VM_ERROR("No SSE instructions.")
#    define _vecm128d_Greater(_a, _b)             VM_ERROR("No SSE instructions.")
#    define _vecm128d_LessEq(_a, _b)              VM_ERROR("No SSE instructions.")
#    define _vecm128d_Less(_a, _b)                VM_ERROR("No SSE instructions.")

#    define _vecm128d_Add(_a, _b)                 VM_ERROR("No SSE instructions.")
#    define _vecm128d_Sub(_a, _b)                 VM_ERROR("No SSE instructions.")
#    define _vecm128d_Mul(_a, _b)                 VM_ERROR("No SSE instructions.")
#    define _vecm128d_Div(_a, _b)                 VM_ERROR("No SSE instructions.")
#endif

#if defined(__SSE2__)
#    define _vecm128d_From128f(_a) _mm_cvtps_pd(_a)
#    define _vecm128d_From128i(_a) _mm_castsi128_pd(_a)
#else
#    define _vecm128d_From128i(_a) VM_ERROR("No SSE2 instructions.")
#    define _vecm128d_From128d(_a) VM_ERROR("No SSE2 instructions.")
#endif

#if defined(__SSE3__)
#    define _vecm128d_AddSub(_a, _b)  _mm_addsub_pd(_a, _b)
#    define _vecm128d_HoriAdd(_a, _b) _mm_hadd_pd(_a, _b)
#    define _vecm128d_HoriSub(_a, _b) _mm_hsub_pd(_a, _b)
#else
#    define _vecm128d_AddSub(_a, _b)  VM_ERROR("No SSE3 instructions.")
#    define _vecm128d_HoriAdd(_a, _b) VM_ERROR("No SSE3 instructions.")
#    define _vecm128d_HoriSub(_a, _b) VM_ERROR("No SSE3 instructions.")
#endif

#if defined(__SSE4_1__)
#    define _vecm128d_Blend(_a, _b, _ctrl)     _mm_blend_pd(_a, _b, _ctrl)
#    define _vecm128d_MaskBlend(_a, _b, _mask) _mm_blendv_pd(_a, _b, _mask)
#    define _vecm128d_Extract(_a, _ctrl)       _mm_extract_pd(_a, _ctrl)
#    define _vecm128d_Insert(_a, _b, _ctrl)    _mm_insert_pd(_a, _b, _ctrl)
#    define _vecm128d_Ceil(_a)                 _mm_ceil_pd(_a)
#    define _vecm128d_Floor(_a)                _mm_floor_pd(_a)
#    define _vecm128d_Round(_a, _round)        _mm_round_pd(_a, _round)
#    define _vecm128d_Dot(_a, _b)              _mm_cvtss_f64(_mm_dp_pd(_a, _b, 0xff))
#else
#    define _vecm128d_Blend(_a, _b, _ctrl)     VM_ERROR("No SSE4.1 instructions.")
#    define _vecm128d_MaskBlend(_a, _b, _mask) VM_ERROR("No SSE4.1 instructions.")
#    define _vecm128d_Extract(_a, _ctrl)       VM_ERROR("No SSE4.1 instructions.")
#    define _vecm128d_Insert(_a, _b, _ctrl)    VM_ERROR("No SSE4.1 instructions.")
#    define _vecm128d_Ceil(_a)                 VM_ERROR("No SSE4.1 instructions.")
#    define _vecm128d_Floor(_a)                VM_ERROR("No SSE4.1 instructions.")
#    define _vecm128d_Round(_a, _round)        VM_ERROR("No SSE4.1 instructions.")
#    define _vecm128d_Dot(_a, _b)              VM_ERROR("No SSE4.1 instructions.")
#endif

#if defined(__AVX__)
#    define _vecm128d_Permute(_v, _ctrl)          _mm_permute_pd(_v, _ctrl)
#    define _vecm128d_MaskStore(_addr, _mask, _a) _mm_maskstore_pd(_addr, _mask, _a)
#    define _vecm128d_MaskLoad(_addr, _mask)      _mm_maskload_pd(_addr, _mask)
#    define _vecm128d_Cmp(_a, _b, _ctrl)          _mm_cmp_pd(_a, _b, _ctrl)
#else
#    define _vecm128d_Permute(_v, _ctrl)          VM_ERROR("No AVX instructions.")
#    define _vecm128d_MaskStore(_addr, _mask, _a) VM_ERROR("No AVX instructions.")
#    define _vecm128d_MaskLoad(_addr, _mask)      VM_ERROR("No AVX instructions.")
#    define _vecm128d_Cmp(_a, _b, _ctrl)          VM_ERROR("No AVX instructions.")
#endif

#if defined(__AVX2__)
#    define _vecm128d_Gather(_addr, _idx, _scale) _mm_i32gather_pd(_addr, _idx, _scale)
#    define _vecm128d_MaskGather(_src, _addr, _idx, _mask, _scale)                                 \
        _mm_mask_i32gather_pd(_src, _addr, _idx, _mask, _scale)
#else
#    define _vecm128d_Gather(_addr, _idx, _scale)                  VM_ERROR("No AVX2 instructions.")
#    define _vecm128d_MaskGather(_src, _addr, _idx, _mask, _scale) VM_ERROR("No AVX2 instructions.")
#endif

#endif
