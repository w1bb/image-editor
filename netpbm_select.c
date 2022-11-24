// Copyright (C) 2022 Valentin-Ioan VINTILA (313CA / 2021-2022)

// Include the asscociated header file
#include "netpbm_select.h"

// This function makes a certain selection in the image, as instructed by the
// SELECT command
// - - - - -
// image   *img = The image where the selection takes place
// int   x1, y1 = First point (could be top-left corner)
// int   x2, y2 = Second point (could be bottom-right corner)
// bool  is_all = true only if the command was SELECT ALL
// - - - - -
// Return: error_t = NO_ERROR if the function finished its task
//                   OTHER_ERROR experienced an issue
error_t netpbm_select(image_ptr img,
					  int x1, int y1, int x2, int y2,
					  bool is_all)
{
	if (check_image(img) == NO_ERROR) {
		if (x1 > x2)
			swap_int(&x1, &x2);
		if (y1 > y2)
			swap_int(&y1, &y2);
		if (x1 < 0 || y1 < 0 ||
			(unsigned int)x2 > img->width || (unsigned int)y2 > img->height ||
			x1 == x2 || y1 == y2) {
			printf(INVALID_SELECT);
			return OTHER_ERROR;
		}
		img->wa_x1 = x1;
		img->wa_x2 = x2;
		img->wa_y1 = y1;
		img->wa_y2 = y2;
		if (is_all)
			printf("Selected ALL\n");
		else
			printf("Selected %d %d %d %d\n", x1, y1, x2, y2);
		return NO_ERROR;
	}
	return OTHER_ERROR;
}
