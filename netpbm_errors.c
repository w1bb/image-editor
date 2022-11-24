// Copyright (C) 2022 Valentin-Ioan VINTILA (313CA / 2021-2022)

// Include the asscociated header file
#include "netpbm_errors.h"

// This function checks if an image was loaded or not.
// - - - - -
// image *img = The image that should be checked
// - - - - -
// Return: error_t = NO_ERROR if the function finished its task
//                   OTHER_ERROR experienced an issue
error_t check_image(image_ptr img)
{
	// As a sanity check, multiple verifications are made
	if (!(img->width) || !(img->height) || !(img->info)) {
		printf(NO_IMAGE);
		return OTHER_ERROR;
	} else {
		return NO_ERROR;
	}
}

// This function checks if a PPM (color) image was loaded
// - - - - -
// image *img = The image that should be checked
// - - - - -
// Return: error_t = NO_ERROR if the function finished its task
//                   OTHER_ERROR experienced an issue
error_t check_ppm(image_ptr img)
{
	if (check_image(img) == NO_ERROR) {
		if (img->ft % 3 == 2) {
			printf(INVALID_IMAGE_TYPE);
			return OTHER_ERROR;
		} else {
			return NO_ERROR;
		}
	}
	return OTHER_ERROR; // check_image error
}
