// Copyright (C) 2022 Valentin-Ioan VINTILA (313CA / 2021-2022)

#ifndef NETPBM_APPLY_H
#define NETPBM_APPLY_H

// This header provides a way to compute the APPLY command.

// General header file
#include "netpbm.h"

// This function applies the EDGE transformation.
// - - - - -
// image *img = The image which contains the selection that will be transformed
// - - - - -
// Return: error_t = CRITICAL_ERROR if safe_malloc() failed
//                   NO_ERROR if the function finished its task
//                   OTHER_ERROR experienced an issue
extern error_t apply_transformation_edge(image_ptr img);

// This function applies the SHARPEN transformation.
// - - - - -
// image *img = The image which contains the selection that will be transformed
// - - - - -
// Return: error_t = CRITICAL_ERROR if safe_malloc() failed
//                   NO_ERROR if the function finished its task
//                   OTHER_ERROR experienced an issue
extern error_t apply_transformation_sharpen(image_ptr img);

// This function applies the BLUR transformation.
// - - - - -
// image *img = The image which contains the selection that will be transformed
// - - - - -
// Return: error_t = CRITICAL_ERROR if safe_malloc() failed
//                   NO_ERROR if the function finished its task
//                   OTHER_ERROR experienced an issue
extern error_t apply_transformation_blur(image_ptr img);

// This function applies the GAUSSIAN_BLUR transformation.
// - - - - -
// image *img = The image which contains the selection that will be transformed
// - - - - -
// Return: error_t = CRITICAL_ERROR if safe_malloc() failed
//                   NO_ERROR if the function finished its task
//                   OTHER_ERROR experienced an issue
extern error_t apply_transformation_gaussian_blur(image_ptr img);

// This function computes one of the new pixels (after a transformation is
// made). This function shouldn't really be called.
// - - - - -
// pixel                  *p = The pixel that is being computed
// double transformation[][] = This is the transformation that will be applied
// int             max_value = The maximum value that a pixel can have (in the
//                             case of this homework, it is always 255, but
//                             that doesn't matter it cannot change otherwise)
// pixel              **info = The information in the original image
// int                  i, j = Position of the current pixel
extern void apply_transformation_compute_new_pixel(pixel_ptr p,
												   double transformation[3][3],
												   int max_value,
												   pixel_ptr_ptr info,
												   int i, int j);

// This function applies any transformation to an image.
// - - - - -
// image                *img = The image which contains the selection that will
//                             be transformed
// double transformation[][] = The kernel image of the transformation
// - - - - -
// Return: error_t = CRITICAL_ERROR if safe_malloc() failed
//                   NO_ERROR if the function finished its task
//                   OTHER_ERROR experienced an issue
extern error_t apply_transformation(image_ptr img, double transformation[3][3]);

#endif // NETPBM_APPLY_H
