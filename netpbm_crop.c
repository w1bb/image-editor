// Copyright (C) 2022 Valentin-Ioan VINTILA (313CA / 2021-2022)

// Include the asscociated header file
#include "netpbm_crop.h"

// This function crops an image into a given selection. However, if the
// selection covers the whole image, nothing happens.
// - - - - -
// image *img = The image that should be cropped
// - - - - -
// Return: error_t = CRITICAL_ERROR if safe_malloc() failed
//                   NO_ERROR if the function finished its task
//                   OTHER_ERROR experienced an issue
error_t netpbm_crop(image_ptr img)
{
	if (check_image(img) == NO_ERROR) {
		unsigned int width = img->wa_x2 - img->wa_x1;
		unsigned int height = img->wa_y2 - img->wa_y1;

		// Save time - only compute cropped value for non-trivial images
		if (width != img->width || height != img->height) {
			pixel_ptr_ptr new_info;
			new_info = safe_malloc(sizeof(pixel_ptr) * height);
			if (!new_info)
				return CRITICAL_ERROR;

			for (unsigned int i = img->wa_y1; i < img->wa_y2; ++i) {
				unsigned int to_i = i - img->wa_y1;
				new_info[to_i] = safe_malloc(sizeof(pixel) * width);
				if (!new_info[to_i]) {
					for (unsigned int old_i = 0; old_i < to_i; ++old_i)
						free(new_info[old_i]);
					free(new_info);
					return CRITICAL_ERROR;
				}
				for (unsigned int j = img->wa_x1; j < img->wa_x2; ++j) {
					unsigned int to_j = j - img->wa_x1;
					new_info[to_i][to_j] = img->info[i][j];
				}
			}

			free_image(img);
			img->info = new_info;
			img->width = width;
			img->height = height;
			img->wa_x1 = 0;
			img->wa_y1 = 0;
			img->wa_x2 = width;
			img->wa_y2 = height;
		}

		printf("Image cropped\n");
		return NO_ERROR;
	}
	return OTHER_ERROR;
}
