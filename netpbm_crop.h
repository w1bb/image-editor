// Copyright (C) 2022 Valentin-Ioan VINTILA (313CA / 2021-2022)

#ifndef NETPBM_CROP_H
#define NETPBM_CROP_H

// This file contains the definition for the CROP command.

// General header file
#include "netpbm.h"

// This function crops an image into a given selection. However, if the
// selection covers the whole image, nothing happens.
// - - - - -
// image *img = The image that should be cropped
// - - - - -
// Return: error_t = CRITICAL_ERROR if safe_malloc() failed
//                   NO_ERROR if the function finished its task
//                   OTHER_ERROR experienced an issue
extern error_t netpbm_crop(image_ptr img);

#endif // NETPBM_CROP_H
