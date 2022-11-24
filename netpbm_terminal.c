// Copyright (C) 2022 Valentin-Ioan VINTILA (313CA / 2021-2022)

// Include the asscociated header file
#include "netpbm_terminal.h"

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
error_t netpbm_parse_command(image_ptr img,
							 char *command,
							 unsigned int argc,
							 char argv[MAX_ARGS][BUFFER_SIZE])
{
	error_t result;
	if (!command) { // No command is passed. Maybe ignore?
		printf(INVALID_COMMAND);
		result = OTHER_ERROR;
	} else if (strcmp(command, "EXIT") == 0 && argc == 0) {
		if (check_image(img) == NO_ERROR)
			(void)free_image(img);
		return OTHER_ERROR;
	} else if (strcmp(command, "LOAD") == 0 && argc == 1) {
		result = netpbm_load(img, argv[0]);
	} else if (strcmp(command, "SELECT") == 0 && argc == 1 &&
			   strcmp(argv[0], "ALL") == 0) {
		result = netpbm_select(img, 0, 0, img->width, img->height, true);
	} else if (strcmp(command, "SELECT") == 0 && argc == 4 &&
			   isnint(argv[0], BUFFER_SIZE) && isnint(argv[1], BUFFER_SIZE) &&
			   isnint(argv[2], BUFFER_SIZE) && isnint(argv[3], BUFFER_SIZE)) {
		// Allow at most 9 digits (8 if signed, doesn't matter since negative
		// values are illegal)
		int x1 = (!argv[0][9]) ? atoi(argv[0]) : -1;
		int y1 = (!argv[1][9]) ? atoi(argv[1]) : -1;
		int x2 = (!argv[2][9]) ? atoi(argv[2]) : -1;
		int y2 = (!argv[3][9]) ? atoi(argv[3]) : -1;
		result = netpbm_select(img, x1, y1, x2, y2, false);
	} else if (strcmp(command, "ROTATE") == 0 && argc == 1 &&
			   isnint(argv[0], BUFFER_SIZE)) {
		// Allow at most 4 digits / 3 if signed (doesn't matter since multiple
		// checks will occor in netpbm_rotate)
		result = netpbm_rotate(img, ((!argv[0][4]) ? atoi(argv[0]) : -1));
	} else if (strcmp(command, "CROP") == 0 && argc == 0) {
		result = netpbm_crop(img);
	} else if (strcmp(command, "APPLY") == 0) {
		// This command is an exception to the rules, and that is because this
		// is the error order that the problem asks for:
		// No image loaded > Invalid command
		if (check_image(img) == NO_ERROR) {
			if (argc == 1) { // said exception
				if (strcmp(argv[0], "EDGE") == 0) {
					result = apply_transformation_edge(img);
				} else if (strcmp(argv[0], "SHARPEN") == 0) {
					result = apply_transformation_sharpen(img);
				} else if (strcmp(argv[0], "BLUR") == 0) {
					result = apply_transformation_blur(img);
				} else if (strcmp(argv[0], "GAUSSIAN_BLUR") == 0) {
					result = apply_transformation_gaussian_blur(img);
				} else {
					printf(INVALID_APPLY);
					result = OTHER_ERROR;
				}
				if (result == NO_ERROR)
					printf("APPLY %s done\n", argv[0]);
			} else {
				printf(INVALID_COMMAND);
				result = OTHER_ERROR;
			}
		} else {
			result = OTHER_ERROR;
		}
	} else if (strcmp(command, "SAVE") == 0 &&
			   (argc == 1 || (argc == 2 && strcmp(argv[1], "ascii") == 0))) {
		if (argc == 2) { // Update to ASCII
			if (filetype_is_binary(img->ft))
				img->ft -= 3;
		} else if (filetype_is_ascii(img->ft)) { // Update to binary
			img->ft += 3;
		}
		result = netpbm_save(img, argv[0]);
	} else {
		printf(INVALID_COMMAND);
		result = OTHER_ERROR;
	}
	if (result == CRITICAL_ERROR) {
		free_image(img);
		return CRITICAL_ERROR;
	}
	return NO_ERROR;
}

// This function should run in main as it acts like a terminal emulator.
error_t netpbm_terminal(void)
{
	image img;
	init_image(&img);

	unsigned int argc;
	char buffer[BUFFER_SIZE],
		 command[BUFFER_SIZE],
		 argv[MAX_ARGS][BUFFER_SIZE],
		 *token;

	error_t keep_running;
	do {
		fgets(buffer, BUFFER_SIZE, stdin);
		// fgets is safe, meaning buffer ends in '\0'
		// See https://www.cplusplus.com/reference/cstdio/fgets/

		token = strtok(buffer, "\n ");
		if (!token) {
			// No command
			keep_running = netpbm_parse_command(NULL, NULL, 0, argv);
		} else {
			strncpy(command, token, BUFFER_SIZE);
			command[BUFFER_SIZE - 1] = '\0'; // defensive programming
			argc = 0;
			for (token = strtok(NULL, "\n "); argc < MAX_ARGS && token;
				 token = strtok(NULL, "\n "), ++argc) {
				strncpy(argv[argc], token, BUFFER_SIZE);
				argv[argc][BUFFER_SIZE - 1] = '\0'; // defensive programming
			}
			// Now, every argv will end in lots of zeros. This will be used to
			// count the number of digits of some parameters (where atoi is used
			// to convert to int)
			// See https://www.cplusplus.com/reference/cstring/strncpy/
			keep_running = netpbm_parse_command(&img, command, argc, argv);
		}
	} while (keep_running == NO_ERROR);

	if (keep_running == OTHER_ERROR)
		return NO_ERROR;
	return CRITICAL_ERROR;
}
