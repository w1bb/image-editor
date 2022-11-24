// Copyright (C) 2021 Valentin-Ioan VINTILA (313CA / 2021-2022)

#ifndef NETPBM_SAVE_H
#define NETPBM_SAVE_H

// This file contains the means for saving an image.

// General header file
#include "netpbm.h"

// This function saves an image to a given location.
// - - - - -
// image       *img = The image that has to be saved
// char  location[] = The location where the file should be saved
// - - - - -
// Return: error_t = NO_ERROR if the function finished its task
//                   OTHER_ERROR experienced an issue
extern error_t netpbm_save(image_ptr img, char location[BUFFER_SIZE]);

#endif // NETPBM_SAVE_H
