// Copyright (C) 2022 Valentin-Ioan VINTILA (313CA / 2021-2022)

// Include the asscociated header file
#include "netpbm_base.h"

// This function frees the information dynamically stored in an image. It does
// NOT assumes that the image was dynamically allocated, so it doesn't free it.
// - - - - -
// image *img = The image which contains the information that should be freed
void free_image(image_ptr img)
{
	if (img && img->info) { // defensive programming
		for (unsigned int i = 0; i < img->height; ++i)
			free(img->info[i]);
		free(img->info);
	}
}

// This function (re)sets everything in an image to default values. Plase note
// that the function assumes that the information within the image was already
// freed by the free_image() function (that is, if necessary).
// - - - - -
// image *img = The image that should be (re)set
void init_image(image_ptr img)
{
	if (img) {
		img->info = NULL;
		img->width = 0;
		img->height = 0;
		img->ft = UNKNOWN;
		img->wa_x1 = 0;
		img->wa_x2 = 0;
		img->wa_y1 = 0;
		img->wa_y2 = 0;
	}
}

// This function checks if a filetype is in ASCII mode.
// - - - - -
// filetype ft = The filetype that should be checked
// - - - - -
// Return: bool = True only if the filetype is ASCII
extern bool filetype_is_ascii(filetype ft)
{
	return (ft >= 1 && ft <= 3);
}

// This function checks if a filetype is in binary mode
// - - - - -
// filetype ft = The filetype that should be checked
// - - - - -
// Return: bool = True only if the filetype is binary
extern bool filetype_is_binary(filetype ft)
{
	return (ft >= 4);
}
