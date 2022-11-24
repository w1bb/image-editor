// Copyright (C) 2022 Valentin-Ioan VINTILA (313CA / 2021-2022)

// Include the asscociated header file
#include "netpbm_rotate.h"

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
error_t netpbm_rotate(image_ptr img, int deg)
{
	if (check_image(img) == NO_ERROR) {
		if (deg % 90 != 0 || deg < -360 || deg > 360) {
			// This used to check if deg == 0, however, because tests
			// wouldn't pass even tho they should...
			printf(INVALID_DEG);
			return OTHER_ERROR;
		}
		int original_deg = deg; // for the fake message
		// -360 <= deg <= 360  ==>  deg = {0, 90, 180, 270}
		deg = (deg + 360) % 360;
		// deg = {0, 90, 180, 270} ==> deg = {0, 1, 2, 3}
		deg /= 90;
		if (deg) {
			// Check if selection is square or the whole image
			if (img->wa_x2 - img->wa_x1 == img->wa_y2 - img->wa_y1) {
				do {
					netpbm_rotate_square_90deg_clockwise(img);
				} while (--deg);
				printf("Rotated %d\n", original_deg);
				return NO_ERROR;
			} else if (!img->wa_x1 && !img->wa_y1 &&
					img->wa_x2 == img->width &&
					img->wa_y2 == img->height) {
				do {
					error_t aux = netpbm_rotate_full_90deg_clockwise(img);
					if (aux != NO_ERROR)
						return aux;
				} while (--deg);
				printf("Rotated %d\n", original_deg);
				return NO_ERROR;
			}
			printf(INVALID_ROTATE);
			return OTHER_ERROR;
		}
		// Fake output message (no change, no problem ;) )
		printf("Rotated %d\n", original_deg);
		return NO_ERROR;
	}
	return OTHER_ERROR;
}

// This function rotates the selection of an image 90 degrees clockwise.
// - - - - -
// image *img = The image that contains the square that has to be rotated
void netpbm_rotate_square_90deg_clockwise(image_ptr img)
{
	for (unsigned int i = img->wa_y1; i < img->wa_y2; ++i)
		for (unsigned int j = img->wa_x1 + i - img->wa_y1;
			 j < img->wa_x2; ++j) {
			unsigned int auxi = j + img->wa_y1 - img->wa_x1;
			unsigned int auxj = i + img->wa_x1 - img->wa_y1;
			swap_pixel(&img->info[i][j], &img->info[auxi][auxj]);
		}

	for (unsigned int k = img->wa_y1; k < img->wa_y2; ++k) {
		int i = img->wa_x1, j = img->wa_x2 - 1;
		while (i < j) {
			swap_pixel(&img->info[k][i], &img->info[k][j]);
			++i;
			--j;
		}
	}
}

// This function rotates a whole image 90 degrees clockwise.
// - - - - -
// image *img = The image that has to be rotated
// - - - - -
// Return: error_t = CRITICAL_ERROR if safe_malloc() failed
//                   NO_ERROR if the function finished its task
error_t netpbm_rotate_full_90deg_clockwise(image_ptr img)
{
	pixel_ptr_ptr new_info;
	new_info = safe_malloc(sizeof(pixel_ptr) * img->width);
	if (!new_info) // safe_malloc failed
		return CRITICAL_ERROR;

	for (unsigned int i = 0; i < img->width; ++i) {
		new_info[i] = safe_malloc(sizeof(pixel) * img->height);
		if (!new_info[i]) { // safe_malloc failed
			for (unsigned int old_i = 0; old_i < i; ++old_i)
				free(new_info[old_i]);
			free(new_info);
			return CRITICAL_ERROR;
		}
		for (unsigned int j = 0; j < img->height; ++j)
			new_info[i][j] = img->info[img->height - j - 1][i];
	}

	free_image(img);
	swap_unsigned(&img->width, &img->height);
	swap_unsigned(&img->wa_x1, &img->wa_y1);
	swap_unsigned(&img->wa_x2, &img->wa_y2);
	img->info = new_info;
	return NO_ERROR;
}
