// Copyright (C) 2022 Valentin-Ioan VINTILA (313CA / 2021-2022)

#ifndef NETPBM_ROTATE_H
#define NETPBM_ROTATE_H

// This header provides the means to rotate a whole image or just a selection.

// General header file
#include "netpbm.h"

// This function rotates deg degrees (a selection of) an image.
// - - - - -
// image *img = The image (that contains the selection) that has to be rotated
// int    deg = The number of degrees the image should be rotated. Should be
//              0, +/-90, +/-180, +/-270, +/-360, but the function handles any
//				value, even if it is not accepted
// - - - - -
// Return: error_t = CRITICAL_ERROR if safe_malloc() failed
//                   NO_ERROR if the function finished its task
//                   OTHER_ERROR experienced an issue
extern error_t netpbm_rotate(image_ptr img, int deg);

// This function rotates the selection of an image 90 degrees clockwise.
// - - - - -
// image *img = The image that contains the square that has to be rotated
extern void netpbm_rotate_square_90deg_clockwise(image_ptr img);

// This function rotates a whole image 90 degrees clockwise.
// - - - - -
// image *img = The image that has to be rotated
// - - - - -
// Return: error_t = CRITICAL_ERROR if safe_malloc() failed
//                   NO_ERROR if the function finished its task
extern error_t netpbm_rotate_full_90deg_clockwise(image_ptr img);

#endif // NETPBM_ROTATE_H
