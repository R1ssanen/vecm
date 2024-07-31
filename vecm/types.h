/**
 * @file types.h
 * @brief Convenience type definitions.
 * @author github.com/r1ssanen
 */

#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>
#include <stdint.h>

typedef bool     b8;

typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float    f32;
typedef double   f64;

#define unused            __attribute__((unused))

#define DO_PRAGMA(_str)   _Pragma(#_str)
#define VM_ERROR(_errmsg) DO_PRAGMA(GCC error #_errmsg)

#endif
