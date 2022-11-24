// Copyright (C) 2022 Valentin-Ioan VINTILA (313CA / 2021-2022)

// Include the asscociated header file
#include "netpbm_apply.h"

// This function applies the EDGE transformation.
// - - - - -
// image *img = The image which contains the selection that will be transformed
// - - - - -
// Return: error_t = CRITICAL_ERROR if safe_malloc() failed
//                   NO_ERROR if the function finished its task
//                   OTHER_ERROR experienced an issue
error_t apply_transformation_edge(image_ptr img)
{
	static double transformation[3][3] = {{-1.0, -1.0, -1.0},
										  {-1.0, 8.0, -1.0},
										  {-1.0, -1.0, -1.0}};
	return apply_transformation(img, transformation);
}

// This function applies the SHARPEN transformation.
// - - - - -
// image *img = The image which contains the selection that will be transformed
// - - - - -
// Return: error_t = CRITICAL_ERROR if safe_malloc() failed
//                   NO_ERROR if the function finished its task
//                   OTHER_ERROR experienced an issue
error_t apply_transformation_sharpen(image_ptr img)
{
	static double transformation[3][3] = {{0.0, -1.0, 0.0},
										  {-1.0, 5.0, -1.0},
										  {0.0, -1.0, 0.0}};
	return apply_transformation(img, transformation);
}

// This function applies the BLUR transformation.
// - - - - -
// image *img = The image which contains the selection that will be transformed
// - - - - -
// Return: error_t = CRITICAL_ERROR if safe_malloc() failed
//                   NO_ERROR if the function finished its task
//                   OTHER_ERROR experienced an issue
error_t apply_transformation_blur(image_ptr img)
{
	static double transformation[3][3] = {{0.1111, 0.1111, 0.1111},
										  {0.1111, 0.1111, 0.1111},
										  {0.1111, 0.1111, 0.1111}};
	return apply_transformation(img, transformation);
}

// This function applies the GAUSSIAN_BLUR transformation.
// - - - - -
// image *img = The image which contains the selection that will be transformed
// - - - - -
// Return: error_t = CRITICAL_ERROR if safe_malloc() failed
//                   NO_ERROR if the function finished its task
//                   OTHER_ERROR experienced an issue
error_t apply_transformation_gaussian_blur(image_ptr img)
{
	static double transformation[3][3] = {{0.0625, 0.125, 0.0625},
										  {0.125, 0.25, 0.125},
										  {0.0625, 0.125, 0.0625}};
	return apply_transformation(img, transformation);
}

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
void apply_transformation_compute_new_pixel(pixel_ptr p,
											double transformation[3][3],
											int max_value,
											pixel_ptr_ptr info,
											int i, int j)
{
	double dsum_r = 0, dsum_g = 0, dsum_b = 0;
	for (unsigned int ni = 0; ni < 3; ++ni) {
		unsigned int pi = i + ni - 1;
		for (unsigned int nj = 0; nj < 3; ++nj) {
			unsigned int pj = j + nj - 1;
			dsum_r += transformation[ni][nj] *
					  info[pi][pj].color_r;
			dsum_g += transformation[ni][nj] *
					  info[pi][pj].color_g;
			dsum_b += transformation[ni][nj] *
					  info[pi][pj].color_b;
		}
	}
	p->color_r = clamp_double(dsum_r, 0, max_value);
	p->color_g = clamp_double(dsum_g, 0, max_value);
	p->color_b = clamp_double(dsum_b, 0, max_value);
}

// This function applies any transformation to an image.
// - - - - -
// image                *img = The image which contains the selection that will
//                             be transformed
// double transformation[][] = The kernel image of the transformation
// - - - - -
// Return: error_t = CRITICAL_ERROR if safe_malloc() failed
//                   NO_ERROR if the function finished its task
//                   OTHER_ERROR experienced an issue
error_t apply_transformation(image_ptr img, double transformation[3][3])
{
	if (check_ppm(img) == NO_ERROR) {
		pixel_ptr_ptr new_info;
		new_info = safe_malloc(sizeof(pixel_ptr) * img->height);
		if (!new_info) // safe_malloc failed
			return CRITICAL_ERROR;
		for (unsigned int i = 0; i < img->height; ++i) {
			new_info[i] = safe_malloc(sizeof(pixel) * img->width);
			if (!new_info[i]) { // safe_malloc failed
				for (unsigned int old_i = 0; old_i < i; ++old_i)
					free(new_info[old_i]);
				free(new_info);
				return CRITICAL_ERROR;
			}
			for (unsigned int j = 0; j < img->width; ++j) {
				if (!i || i == img->height - 1 ||
					!j || j == img->width - 1 ||
					i < img->wa_y1 || i >= img->wa_y2 ||
					j < img->wa_x1 || j >= img->wa_x2) {
					new_info[i][j] = img->info[i][j];
				} else {
					apply_transformation_compute_new_pixel(&new_info[i][j],
														   transformation,
														   img->max_value,
														   img->info, i, j);
				}
			}
		}
		free_image(img);
		img->info = new_info;
		return NO_ERROR;
	}
	return OTHER_ERROR;
}
