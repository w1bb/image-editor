// Copyright (C) 2022 Valentin-Ioan VINTILA (313CA / 2021-2022)

// Include the asscociated header file
#include "misc_utilities.h"

// This function swaps two integer numbers.
// - - - - -
// int *a = Pointer to the first number
// int *b = Pointer to the second number
void swap_int(int *a, int *b)
{
	int aux = *a;
	*a = *b;
	*b = aux;
}

// This function swaps two unsigned integers.
// - - - - -
// int *a = Pointer to the first number
// int *b = Pointer to the second number
void swap_unsigned(unsigned int *a, unsigned int *b)
{
	unsigned int aux = *a;
	*a = *b;
	*b = aux;
}

// This function swaps two pixels.
// - - - - -
// pixel *a = Pointer to the first pixel
// pixel *b = Pointer to the second pixel
void swap_pixel(pixel_ptr a, pixel_ptr b)
{
	pixel aux;
	aux = *a;
	*a = *b;
	*b = aux;
}

// This function makes sure l <= x <= r
// - - - - -
// int x = The number that will be clamped
// int l = The left margin
// int r = The right margin
// - - - - -
// Return: int = l, if x < l
//               r, if x > r
//               x, otherwise
int clamp_int(int x, int l, int r)
{
	if (x < l)
		x = l;
	else if (x > r)
		x = r;
	return x;
}

// This function makes sure l <= x <= r
// - - - - -
// double x = The number that will be clamped
// double l = The left margin
// double r = The right margin
// - - - - -
// Return: double = l, if x < l
//                  r, if x > r
//                  x, otherwise
double clamp_double(double x, double l, double r)
{
	if (x < l)
		x = l;
	else if (x > r)
		x = r;
	return x;
}

// This function checks if a given string is a number.
// - - - - -
// char       *s = The string that should be checked
// int  max_size = The maximum length upon the string will be checked
// - - - - -
// Return: bool = true only if the string was a number
bool isnint(char *s, int max_size)
{
	if (max_size) {
		int i = 0;
		if (s[0] == '-' && max_size >= 2 && s[1])
			++i;
		for (; s[i] && i < max_size; ++i) {
			if (!isdigit(s[i]))
				return false;
		}
	}
	return true;
}
