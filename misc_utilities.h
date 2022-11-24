// Copyright (C) 2022 Valentin-Ioan VINTILA (313CA / 2021-2022)

#ifndef MISC_UTILITIES_H
#define MISC_UTILITIES_H

// This file contains miscellaneous functions that are used in this program.

// General header file
#include "netpbm.h"

// This function swaps two integer numbers.
// - - - - -
// int *a = Pointer to the first number
// int *b = Pointer to the second number
extern void swap_int(int *a, int *b);

// This function swaps two unsigned integers.
// - - - - -
// int *a = Pointer to the first number
// int *b = Pointer to the second number
extern void swap_unsigned(unsigned int *a, unsigned int *b);

// This function swaps two pixels.
// - - - - -
// pixel *a = Pointer to the first pixel
// pixel *b = Pointer to the second pixel
extern void swap_pixel(pixel_ptr a, pixel_ptr b);

// This function makes sure l <= x <= r
// - - - - -
// int x = The number that will be clamped
// int l = The left margin
// int r = The right margin
// - - - - -
// Return: int = l, if x < l
//               r, if x > r
//               x, otherwise
extern int clamp_int(int x, int l, int r);

// This function makes sure l <= x <= r
// - - - - -
// double x = The number that will be clamped
// double l = The left margin
// double r = The right margin
// - - - - -
// Return: double = l, if x < l
//                  r, if x > r
//                  x, otherwise
extern double clamp_double(double x, double l, double r);

// This function checks if a given string is a number.
// - - - - -
// char       *s = The string that should be checked
// int  max_size = The maximum length upon the string will be checked
// - - - - -
// Return: bool = true only if the string was a number
extern bool isnint(char *s, int max_size);

#endif // MISC_UTILITIES_H
