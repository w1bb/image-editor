// Copyright (C) 2022 Valentin-Ioan VINTILA (313CA / 2021-2022)

// Include the asscociated header file
#include "netpbm_load.h"

// This function removes unnecessary comments hidden in a file.
// - - - - -
// FILE *fin = The input file
// - - - - -
// Return: error_t = CRITICAL_ERROR if there was an issue with the input file
//                   NO_ERROR if the function finished its task
error_t remove_comments(FILE *fin)
{
	char c = '\n';
	do {
		while (c != '\n')
			fscanf(fin, "%c", &c);
		fscanf(fin, "%c", &c);
	} while (c == '#');

	if (fseek(fin, -1, SEEK_CUR)) { // defensive programming
		// This should NEVER be reached
		fprintf(stderr, CRITICAL_FSEEK);
		return CRITICAL_ERROR;
	}
	return NO_ERROR;
}

// This function loads a new image in the memory.
// - - - - -
// image *img       = The image that will be loaded from the given file
// char  location[] = The location where the file is saved
// - - - - -
// Return: error_t = CRITICAL_ERROR if safe_malloc() failed or if there was an
//                   issue with the input file
//                   NO_ERROR if the function finished its task
//                   OTHER_ERROR experienced an issue
error_t netpbm_load(image_ptr img, char location[BUFFER_SIZE])
{
	free_image(img);
	init_image(img);
	FILE *fin = fopen(location, "rt+");
	if (!fin) {
		printf(FAIL_LOAD, location);
		return OTHER_ERROR;
	}
	char type[3];
	if (remove_comments(fin) != NO_ERROR)
		return CRITICAL_ERROR;
	fscanf(fin, "%s", type);
	if (remove_comments(fin) != NO_ERROR)
		return CRITICAL_ERROR;
	fscanf(fin, "%u", &img->width);
	if (remove_comments(fin) != NO_ERROR)
		return CRITICAL_ERROR;
	fscanf(fin, "%u", &img->height);
	if (remove_comments(fin) != NO_ERROR)
		return CRITICAL_ERROR;
	fscanf(fin, "%u", &img->max_value);
	if (remove_comments(fin) != NO_ERROR)
		return CRITICAL_ERROR;
	// Set the values that can be set based on the current info
	img->ft = (filetype)(type[1] - '0');
	img->wa_x2 = img->width;
	img->wa_y2 = img->height;
	if (img->ft >= 5) { // Prepare file for binary read
		long last_pos = ftell(fin);
		fclose(fin);
		fin = fopen(location, "rb+");
		if (!fin) { // defensive programming
			fprintf(stderr, FAIL_LOAD, location);
			return CRITICAL_ERROR;
		} else if (fseek(fin, last_pos + 1, SEEK_SET)) {
			fprintf(stderr, CRITICAL_FSEEK);
			return CRITICAL_ERROR;
		}
	}
	unsigned char col[3];
	img->info = safe_malloc(sizeof(pixel_ptr) * img->height);
	if (!img->info) // safe_malloc failed
		return CRITICAL_ERROR;
	for (unsigned int i = 0; i < img->height; ++i) {
		img->info[i] = safe_malloc(sizeof(pixel) * img->width);
		if (!img->info[i]) { // safe_malloc failed
			img->height = i;
			free_image(img);
			return CRITICAL_ERROR;
		}
		for (unsigned int j = 0; j < img->width; ++j) {
			if (img->ft >= 5) { // binary format
				if (img->ft == BINARY_PGM) {
					fread(&col[0], sizeof(unsigned char), 1, fin);
					col[1] = col[0];
					col[2] = col[0];
				} else { // BINARY_PPM
					fread(col, sizeof(unsigned char), 3, fin);
				}
			} else { // ASCII format
				if (img->ft == ASCII_PGM) {
					fscanf(fin, "%hhu", &col[0]);
					col[1] = col[0];
					col[2] = col[0];
				} else { // ASCII_PPM
					fscanf(fin, "%hhu", &col[0]);
					fscanf(fin, "%hhu", &col[1]);
					fscanf(fin, "%hhu", &col[2]);
				}
			}
			img->info[i][j].color_r = (double)col[0];
			img->info[i][j].color_g = (double)col[1];
			img->info[i][j].color_b = (double)col[2];
		}
	}
	printf("Loaded %s\n", location);
	fclose(fin);
	return NO_ERROR;
}
