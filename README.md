# Image Editor (PCLP-Homework-03)
This repository is intended to store a PPM/PGM image manipulation software, designed for advanced filtering and algebraic transformations. 

## License

This project is available under the MIT license. For more info about the author or the cod, please check out <a href="https://v-vintila.com">my personal website</a>.

## Documentation

In order to complete this homework, I've split the task into multiple parts that
could be solved individually. I'll cover them separately in this file.

### 0. Pre-prerequisites (1) - memory_utilities

This task requires some dynamically allocated memory. This is the reason    
why a safer technique should be used instead of the standard malloc()
function.

To accomplish this, I've created the 'memory_utilities' header, which
defines two functions, safe_malloc_utility() and safe_realloc_utility().

Whenever malloc() is called, it returns NULL if said memory could not be
allocated. To prevent a runtime error caused by this,
safe_malloc_utility() tries to dynamically allocate for a few times and,
if it doesn't succeed, it gives up and outputs an error message.

The header also provides a way to communicate to other functions that a
critical error took place - error_t:

* CRITICAL_ERROR = Something very bad happened, such as:

  * malloc() failed
  * realloc() failed
  * fseek() failed
  * fopen() failed
  
* NO_ERROR = Everything went smooth!
* OTHER_ERROR = This is not a critical error, this usually means that a certain task could not be completed because no image was loaded, the arguments weren't correct etc.

The header also provides macro functions for said utilities - these
should ALWAYS be used instead of the _utility() versions themselves.

There is a safe_realloc() function in there too; however, it is never
actually used.
    
### 0. Pre-prerequisites (2) - misc_utilities

These are useful utilities that provide the functionality required by
other operations. A full documentation of each of these is provided in
the header file itself.

There are swapping functions (swap_int, swap_unsigned, swap_pixel),
clamping functions (clamp_int, clamp_double) and a special function that
verifies safely if a string is actually a number (isnint).

### 1. Prerequisites - netpbm_base

This is where the basic definition of what an 'image' is. Without this
header, there is no way to complete any action at all.

Am image should contain:
    
* a filetype, which could be:

  * UNKNOWN, meaning it was not decided yet;
  * ASCII_PGM, meaning a grayscale ASCII image;
  * ASCII_PPM, meaning a color ASCII image;
  * BINARY_PGM, meaning a grayscale binary image;
  * BINARY_PPM, meaning a color binary image;

* a file's dimensions (a width and a height, both integers);
* a matrix of pixels, where each pixel (1) is defined by:
  * color_r, its red channel;
  * color_g, its green channel;
  * color_b, its blue channel
* a maximum value (2);
* an image's current selection, defined by:
  * wa_y1, wa_x1 - the top left corner
  * wa_y2, wa_x2 - the bottom right corner
    
(1): In case of a grayscale image, a single channel is used (in my
implementation, all the channels are used - this is to futureproof my
work; however, my program's specifications will state that the red
channel should be used, the others could be undefined).

(2): The original format uses this value; even if the homework states that
no value other than 255 will be used as the maximum value, my
implementation is a little bit broader.

The header also provides a way to free an image's content, to initialize
it ant to verify if a certain filetype is set in ASCII or binary mode.

### 2. A terminal-like behaviour - netpbm_terminal

Because these commands are similiar to a series of commands passed to a
terminal, I emulate this behaviour inside the netpbm_terminal()
function. This converts non-stop the user's input into a command and its
arguments. These are then parsed by the netpbm_parse_command() function.

No assumptions are made, making these functions super safe! The
arguments are verified as strings and only then converted in case they
are correct!

### 3. SELECT - netpbm_select

The SELECT function applies the selection directly in the loaded file.
For further details, please reffer to the netpbm_select.h file.

**Time complexity:  O(1)**

**Space complexity: O(1)**

### 4. ROTATE - netpbm_select

The ROTATE function creates a new image based on a repeated 90 degrees
clockise rotation. The algorithm's idea can be found on geeksforgeeks :)

The function makes sure that the matrix to be resized does actually exist.

**Time complexity:** O(width_of_selection * height_of_selection)

**Space complexity:** O(1) in case of a selection, O(height * width) in case of the whole image

### 5. CROP - netpbm_crop

This function crops the current selection. It accomplishes its task by
creating a new image of width_of_selection * height_of_selection size
and copies the content of the old image inside it.

**Time complexity:**  O(width_of_selection * height_of_selection)

**Space complexity:** O(width_of_selection * height_of_selection)

### 6. APPLY - netpbm_apply

This function applies a transformation on the image. There are some
predefined operations, such as:
* apply_transformation_edge
* apply_transformation_sharpen
* apply_transformation_blur
* apply_transformation_gaussian_blur
    
...but any other can be created using the apply_transformation()
function.

Each pixel is modified under the hood using the (not long enough named)
apply_transformation_compute_new_pixel() function.

**Time complexity:**  O(width_of_selection * height_of_selection)

**Space complexity:** O(width * height)

### 7. SAVE - netpbm_save

This function provides a safe way to save an image inside a file. It is
broad enough that it can save in all 4 possible filetypes.

**Time complexity:** O(width * height)

**Space complexity:** O(1)

### 8. EXIT

The memory is freed and the program ends.

## A final word

Please reffer to each of the header files for more in depth info about how
each function opperates. Other info can be found on <a href="https://v-vintila.com/">my personal website</a>.
