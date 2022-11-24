// Copyright (C) 2022 Valentin-Ioan VINTILA (313CA / 2021-2022)

#ifndef NETPBM_LOAD_H
#define NETPBM_LOAD_H

// This file provides the means to load a file safely into the memory.

// General header file
#include "netpbm.h"

// This function removes unnecessary comments hidden in a file.
// - - - - -
// FILE *fin = The input file
// - - - - -
// Return: error_t = CRITICAL_ERROR if there was an issue with the input file
//                   NO_ERROR if the function finished its task
// - - - - -
// Note: FILE * fin instead of FILE *fin due to cs/cs.sh
extern error_t remove_comments(FILE * fin);

// This function loads a new image in the memory.
// - - - - -
// image *img       = The image that will be loaded from the given file
// char  location[] = The location where the file is saved
// - - - - -
// Return: error_t = CRITICAL_ERROR if safe_malloc() failed or if there was an
//                   issue with the input file
//                   NO_ERROR if the function finished its task
//                   OTHER_ERROR experienced an issue
extern error_t netpbm_load(image_ptr img, char location[BUFFER_SIZE]);

#endif // NETPBM_LOAD_H
