// Copyright (C) 2022 Valentin-Ioan VINTILA (313CA / 2021-2022)

// Include the asscociated header file
#include "netpbm_save.h"

// This function saves an image to a given location.
// - - - - -
// image       *img = The image that has to be saved
// char  location[] = The location where the file should be saved
// - - - - -
// Return: error_t = NO_ERROR if the function finished its task
//                   OTHER_ERROR experienced an issue
error_t netpbm_save(image_ptr img, char location[BUFFER_SIZE])
{
	if (check_image(img) == NO_ERROR) {
		FILE *fout;
		if (filetype_is_ascii(img->ft))
			fout = fopen(location, "wt+");
		else
			fout = fopen(location, "wb+");

		fprintf(fout, "P%d\n%d %d\n%d\n",
				img->ft, img->width, img->height, img->max_value);

		unsigned char col[3];
		for (unsigned int i = 0; i < img->height; ++i) {
			for (unsigned int j = 0; j < img->width; ++j) {
				col[0] = clamp_double(round(img->info[i][j].color_r),
									  0, img->max_value);
				col[1] = clamp_double(round(img->info[i][j].color_g),
									  0, img->max_value);
				col[2] = clamp_double(round(img->info[i][j].color_b),
									  0, img->max_value);
				if (filetype_is_binary(img->ft)) { // binary format
					if (img->ft == BINARY_PGM)
						fwrite(col, sizeof(unsigned char), 1, fout);
					else // BINARY_PPM
						fwrite(col, sizeof(unsigned char), 3, fout);
				} else { // ASCII format
					if (img->ft == ASCII_PGM)
						fprintf(fout, "%u ", col[0]);
					else // ASCII_PPM
						fprintf(fout, "%u %u %u ", col[0], col[1], col[2]);
				}
			}
			if (filetype_is_ascii(img->ft))
				(void)fputc('\n', fout);
		}

		if (filetype_is_binary(img->ft))
			(void)fputc('\n', fout);

		fclose(fout);
		printf("Saved %s\n", location);
		return NO_ERROR;
	}
	return OTHER_ERROR;
}
