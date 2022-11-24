// Copyright (C) 2022 Valentin-Ioan VINTILA (313CA / 2021-2022)

#ifndef NETPBM_ERRORS_H
#define NETPBM_ERRORS_H

// This file contains all the error messages that have to be outputed in case
// something goes wrong.

// General header file
#include "netpbm.h"

// These are requested by the problem
#define INVALID_COMMAND "Invalid command\n"
#define FAIL_LOAD "Failed to load %s\n"
#define NO_IMAGE "No image loaded\n"
#define INVALID_SELECT "Invalid set of coordinates\n"
#define INVALID_APPLY "APPLY parameter invalid\n"
#define INVALID_DEG "Unsupported rotation angle\n"
#define INVALID_ROTATE "The selection must be square\n"
#define INVALID_IMAGE_TYPE "Easy, Charlie Chaplin\n"

// These were made for debugging purposes
#define CRITICAL_FSEEK "CRITICAL: Fseek failed\n"

// This function checks if an image was loaded or not.
// - - - - -
// image *img = The image that should be checked
// - - - - -
// Return: error_t = NO_ERROR if the function finished its task
//                   OTHER_ERROR experienced an issue
extern error_t check_image(image_ptr img);

// This function checks if a PPM (color) image was loaded
// - - - - -
// image *img = The image that should be checked
// - - - - -
// Return: error_t = NO_ERROR if the function finished its task
//                   OTHER_ERROR experienced an issue
extern error_t check_ppm(image_ptr img);

#endif // NETPBM_ERRORS_H
