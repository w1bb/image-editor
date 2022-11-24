// Copyright (C) 2022 Valentin-Ioan VINTILA (313CA / 2021-2022)

#ifndef NETPBM_BASE_H
#define NETPBM_BASE_H

// This file contains the most important parts of the program. Without it, all
// the other header files would have to redefine what an image actually means.

// These are the acceped filetypes
typedef enum {
	UNKNOWN,
	ASCII_PGM = 2, ASCII_PPM = 3,
	BINARY_PGM = 5, BINARY_PPM = 6
} filetype;

// A pixel is defined by its red, green and blue channels. A 'gray' pixel will
// have only a single value occupied (the others could be garbage).
typedef struct {
	double color_r, color_g, color_b;
} pixel;

// Due to "errors" in the evaluation, these types need to be defined
// See https://curs.upb.ro/2021/mod/forum/discuss.php?d=6612#p18362
typedef pixel * pixel_ptr;
typedef pixel_ptr * pixel_ptr_ptr;

// An image has these properties
typedef struct {
	filetype ft; // the image's filetype (futureproofing)
	unsigned int width, height; // the size of the image
	pixel_ptr_ptr info; // a matrix of pixels
	unsigned int max_value; // a pixel's maximum value
	unsigned int wa_x1, wa_x2, wa_y1, wa_y2; // the current selection
} image;

// Due to "errors" in the evaluation, this type needs to be defined
// See https://curs.upb.ro/2021/mod/forum/discuss.php?d=6612#p18362
typedef image * image_ptr;

// General header file
#include "netpbm.h"

// This function frees the information dynamically stored in an image. It does
// NOT assumes that the image was dynamically allocated, so it doesn't free it.
// - - - - -
// image *img = The image which contains the information that should be freed
extern void free_image(image_ptr img);

// This function (re)sets everything in an image to default values. Plase note
// that the function assumes that the information within the image was already
// freed by the free_image() function (that is, if necessary).
// - - - - -
// image *img = The image that should be (re)set
extern void init_image(image_ptr img);

// This function checks if a filetype is in ASCII mode.
// - - - - -
// filetype ft = The filetype that should be checked
// - - - - -
// Return: bool = True only if the filetype is ASCII
extern bool filetype_is_ascii(filetype ft);

// This function checks if a filetype is in binary mode
// - - - - -
// filetype ft = The filetype that should be checked
// - - - - -
// Return: bool = True only if the filetype is binary
extern bool filetype_is_binary(filetype ft);

#endif // NETPBM_BASE_H
