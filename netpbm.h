// Copyright (C) 2022 Valentin-Ioan VINTILA (313CA / 2021-2022)

#ifndef NETPBM_H
#define NETPBM_H

// This file contains everything that has to be included in order to provide the
// needed functionality. This file also contains important macro definitions.

// This is the general buffer size of a character array
#define BUFFER_SIZE 512

// This is the maximum number of arguments that can be passed to a command
#define MAX_ARGS 5

// Standard library dependencies
#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Most important headers
#include "memory_utilities.h"
#include "netpbm_base.h"
#include "misc_utilities.h"
#include "netpbm_errors.h"

// The main operations
#include "netpbm_apply.h"
#include "netpbm_crop.h"
#include "netpbm_load.h"
#include "netpbm_save.h"
#include "netpbm_select.h"
#include "netpbm_rotate.h"

// The terminal
#include "netpbm_terminal.h"

#endif // NETPBM_H
