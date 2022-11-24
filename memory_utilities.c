// Copyright (C) 2022 Valentin-Ioan VINTILA (313CA / 2021-2022)

// Include the asscociated header file
#include "memory_utilities.h"

// This function allocates memory safely (it verifies that said memory does
// indeed get allocated and retries for a few times)
// - - - - -
// int     n = The number of bytes that should be allocated
// int  line = The line number where the safe_malloc was called
// int retry = The number of times the function should retry to allocate said
//			   memory
// - - - - -
// Return: void * = Pointer to the allocated memory (or NULL)
void *safe_malloc_utility(int n, int line, int retry)
{
	void *p = malloc(n);
	if (!p) {
		if (retry != 0)
			return safe_malloc_utility(n, line, retry - 1);

		// Error message
		fprintf(stderr, "[%s:%d] FATAL: Out of memory.\n", __FILE__, line);
		fprintf(stderr, "Tried to allocate: %d bytes", n);
		return NULL;
	}
	return p;
}

// This function reallocates memory safely (it verifies that said memory does
// indeed get reallocated and retries for a few times)
// - - - - -
// int     n = The number of bytes that should be reallocated
// int  line = The line number where the safe_realloc was called
// int retry = The number of times the function should retry to reallocate said
//			   memory
// - - - - -
// Return: void * = Pointer to the reallocated memory
void *safe_realloc_utility(void *ptr, int n, int line, int retry)
{
	void *p = realloc(ptr, n);
	if (!p) {
		if (retry != 0)
			return safe_realloc_utility(ptr, n, line, retry - 1);

		// Error message
		fprintf(stderr, "[%s:%d] FATAL: Out of memory.\n", __FILE__, line);
		fprintf(stderr, "Tried to reallocate: %d bytes", n);
		return NULL;
	}
	return p;
}
