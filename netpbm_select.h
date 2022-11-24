// Copyright (C) 2022 Valentin-Ioan VINTILA (313CA / 2021-2022)

#ifndef NETPBM_SELECT_H
#define NETPBM_SELECT_H

// This header provides a way to select a section of the image.

// General header file
#include "netpbm.h"

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
extern error_t netpbm_select(image_ptr img,
							 int x1, int y1, int x2, int y2,
							 bool is_all);

#endif // NETPBM_SELECT_H
