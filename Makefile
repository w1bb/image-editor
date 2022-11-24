# Copyright (C) 2021 Valentin-Ioan VINTILA (313CA / 2021-2022)

# Compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -lm # -ggdb3 -DDEBUG # Uncomment while testing

# Targets (.o files)
TARGETS=netpbm_apply.o netpbm_base.o netpbm_crop.o netpbm_errors.o \
netpbm_load.o netpbm_rotate.o netpbm_save.o netpbm_select.o netpbm_terminal.o \
memory_utilities.o misc_utilities.o

# Building process (general) - TIDY (removes auxiliar files)
build: $(TARGETS)
	$(CC) $(CFLAGS) -o image_editor $^ main.c -lm
	rm -f $(TARGETS)

# Building process (general) - UGLY (doesn't remove auxiliar files)
build-dirty: $(TARGETS)
	$(CC) $(CFLAGS) -o image_editor $^ main.c

# Building process > netpbm_apply
netpbm_apply.o: netpbm_apply.c
	$(CC) $(CFLAGS) -c -o $@ $^

# Building process > netpbm_base
netpbm_base.o: netpbm_base.c
	$(CC) $(CFLAGS) -c -o $@ $^

# Building process > netpbm_crop
netpbm_crop.o: netpbm_crop.c
	$(CC) $(CFLAGS) -c -o $@ $^

# Building process > netpbm_errors
netpbm_errors.o: netpbm_errors.c
	$(CC) $(CFLAGS) -c -o $@ $^

# Building process > netpbm_load
netpbm_load.o: netpbm_load.c
	$(CC) $(CFLAGS) -c -o $@ $^

# Building process > netpbm_rotate
netpbm_rotate.o: netpbm_rotate.c
	$(CC) $(CFLAGS) -c -o $@ $^

# Building process > netpbm_save
netpbm_save.o: netpbm_save.c
	$(CC) $(CFLAGS) -c -o $@ $^

# Building process > netpbm_select
netpbm_select.o: netpbm_select.c
	$(CC) $(CFLAGS) -c -o $@ $^

# Building process > netpbm_terminal
netpbm_terminal.o: netpbm_terminal.c
	$(CC) $(CFLAGS) -c -o $@ $^

# Building process > memory_utilities
memory_utilities.o: memory_utilities.c
	$(CC) $(CFLAGS) -c -o $@ $^

# Building process > misc_utilities
misc_utilities.o: misc_utilities.c
	$(CC) $(CFLAGS) -c -o $@ $^

# Cleaning process
clean:
	rm -f $(TARGETS) image_editor

# Packing process (to .ZIP)
pack:
	zip -FSr 313CA_VintilaValentinIoan_Tema3.zip README Makefile *.c *.h
