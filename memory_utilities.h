// Copyright (C) 2022 Valentin-Ioan VINTILA (313CA / 2021-2022)

#ifndef MEMORY_UTILITIES_H
#define MEMORY_UTILITIES_H

// This file contains a safe (smart) defintions for some utilities. It makes
// sure memory can be allocated and provides a way to safely assert.

// These are the different types of errors that can be returned in case
// something very wrong happens
typedef enum {
	CRITICAL_ERROR = -1,
	NO_ERROR = 0,
	OTHER_ERROR = 1
} error_t;

// General header file
#include "netpbm.h"

// This macro specifies how many times should a failed attempt of memory
// (re)allocation be repeated.
#define ALLOC_RETRY 3

// The safe_malloc_utility SHOULD NOT be used by itself. safe_malloc should be
// used instead. It passes two additional arguments to the safe_malloc_utility,
// representing the line number where the allocation occours and the number of
// times the function should retry to allocate said memory in case it fails.
// - - - - -
// int n = The number of bytes that should be allocated
// - - - - -
// Return: void * = Pointer to the allocated memory (or NULL)
#define safe_malloc(n) safe_malloc_utility(n, __LINE__, ALLOC_RETRY)

// This function allocates memory safely (it verifies that said memory does
// indeed get allocated and retries for a few times)
// - - - - -
// int     n = The number of bytes that should be allocated
// int  line = The line number where the safe_malloc was called
// int retry = The number of times the function should retry to allocate said
//			   memory
// - - - - -
// Return: void * = Pointer to the allocated memory (or NULL)
extern void *safe_malloc_utility(int n, int line, int retry);

// The safe_realloc_utility SHOULD NOT be used by itself. safe_realloc should be
// used instead. It passes two additional arguments to the safe_realloc_utility,
// representing the line number where the reallocation occours and the number of
// times the function should retry to reallocate said memory in case it fails.
// - - - - -
// int n = The number of bytes that should be reallocated
// - - - - -
// Return: void * = Pointer to the reallocated memory (or NULL)
#define safe_realloc(ptr, n) safe_realloc_utility(ptr, n, __LINE__, ALLOC_RETRY)

// This function reallocates memory safely (it verifies that said memory does
// indeed get reallocated and retries for a few times)
// - - - - -
// int     n = The number of bytes that should be reallocated
// int  line = The line number where the safe_realloc was called
// int retry = The number of times the function should retry to reallocate said
//			   memory
// - - - - -
// Return: void * = Pointer to the reallocated memory (or NULL)
extern void *safe_realloc_utility(void *ptr, int n, int line, int retry);

#endif // MEMORY_UTILITIES_H
