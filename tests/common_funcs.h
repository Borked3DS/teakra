// Copyright 2013 Dolphin Emulator Project / 2014 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "../src/common_types.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

/// Textually concatenates two tokens. The double-expansion is required by the C preprocessor.
#define CONCAT2(x, y) DO_CONCAT2(x, y)
#define DO_CONCAT2(x, y) x##y

// helper macro to properly align structure members.
// Calling INSERT_PADDING_BYTES will add a new member variable with a name like "pad121",
// depending on the current source line to make sure variable names are unique.
#define INSERT_PADDING_BYTES(num_bytes) u8 CONCAT2(pad, __LINE__)[(num_bytes)]
#define INSERT_PADDING_WORDS(num_words) u32 CONCAT2(pad, __LINE__)[(num_words)]

// Inlining
#ifdef _MSC_VER
#define FORCE_INLINE __forceinline
#else
#define FORCE_INLINE inline __attribute__((always_inline))
#endif

#ifdef ARCHITECTURE_x86_64
#define Crash() __asm__ __volatile__("int $3")
#elif defined(_M_ARM)
#define Crash() __asm__ __volatile__("trap")
#else
#define Crash() exit(1)
#endif

// GCC 4.8 defines all the rotate functions now
// Small issue with GCC's lrotl/lrotr intrinsics is they are still 32bit while we require 64bit
#ifdef _rotl
#define rotl _rotl
#else
inline u32 rotl(u32 x, int shift) {
    shift &= 31;
    if (!shift)
        return x;
    return (x << shift) | (x >> (32 - shift));
}
#endif

#ifdef _rotr
#define rotr _rotr
#else
inline u32 rotr(u32 x, int shift) {
    shift &= 31;
    if (!shift)
        return x;
    return (x >> shift) | (x << (32 - shift));
}
#endif

inline u64 _rotl64(u64 x, unsigned int shift) {
    unsigned int n = shift % 64;
    return (x << n) | (x >> (64 - n));
}

inline u64 _rotr64(u64 x, unsigned int shift) {
    unsigned int n = shift % 64;
    return (x >> n) | (x << (64 - n));
}
