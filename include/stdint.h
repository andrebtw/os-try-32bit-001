#ifndef STDINT_H
#define STDINT_H

/* integers typedef */
typedef char                int8;
typedef unsigned char       uint8;
typedef short               int16;
typedef unsigned short      uint16;
typedef int                 int32;
typedef unsigned int        uint32;
typedef long long           int64;
typedef unsigned long long  uint64;
typedef uint64              size_t;

typedef uint8 uint8_t;
typedef uint16 uint16_t;
typedef uint32 uint32_t;


/* float typedef */
typedef float               float32;
typedef double              float64;

#define NULL ((void *)0)

#endif