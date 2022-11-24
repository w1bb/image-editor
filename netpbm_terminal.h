// Copyright (C) 2022 Valentin-Ioan VINTILA (313CA / 2021-2022)

#ifndef NETPBM_TERMINAL_H
#define NETPBM_TERMINAL_H

// This file contains a definition for how the 'terminal'-like structure of the
// commands should be interpreted.

// General header file
#include "netpbm.h"

// This function parses a command once it knows its arguments. It makes sure the
// arguments have the required type.
// - - - - -
// image            *img = The image on which the operations should take place.
//                         This could be set to NULL in case the command pointer
//                         is also set to NULL
// char         *command = The command that was issued (e.g. SAVE)
// unsigned int     argc = The number of arguments for said command (similar to
//                         main's default arguments)
// char         argv[][] = The arguments that were
// - - - - -
// Return: error_t = CRITICAL_ERROR if safe_malloc() failed
//                   NO_ERROR if the program should keep running
//                   OTHER_ERROR if the program should end (EXIT)
extern error_t netpbm_parse_command(image_ptr img,
									char *command,
									unsigned int argc,
									char argv[MAX_ARGS][BUFFER_SIZE]);

// This function should run in main as it acts like a terminal emulator.
// - - - - -
// Return: error_t = CRITICAL_ERROR if safe_malloc() failed
//                   NO_ERROR if the program ended correctly
extern error_t netpbm_terminal(void);

#endif // NETPBM_TERMINAL_H
