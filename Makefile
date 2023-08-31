# Change this to your compiler of choice! (except for MSVC, use msvc_build.bat)
CC = gcc

BASENAME = cs50
LIBNAME  = libcs50

# Since we're building a singular library, I suppose this works.
# In practice, though, we'd need more complicated variables and rules!
SRC 	:= src/$(BASENAME).c
INCLUDE := src/$(BASENAME).h
OBJ 	:= obj/$(BASENAME).o
DLL 	:= bin/$(BASENAME).dll

# Compiler Flags
# Need to define the MAKE_DLL_EXPORTS to, you know, actually export the funcs.
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c11 -D MAKE_DLL_EXPORTS

# Linker Flags
# Remember to surround this with quotes later, especially for PowerShell.
LDFLAGS = -Wl,--subsystem,windows,--out-implib

.PHONY: all clean

all: $(DLL)

clean:
	$(RM) $(wildcard bin/*.dll)
	$(RM) $(wildcard obj/*.o)
	$(RM) $(wildcard lib/*.a)

# Create the bin/cs50.dll and lib/libcs50.a files.
$(DLL): $(OBJ)
	$(CC) -o "$@" "$<" -shared -s "$(LDFLAGS),lib/$(LIBNAME).a"

# Create the obj/cs50.o object file which the .dll and .a files will need.
$(OBJ): $(SRC) $(INCLUDE)
	$(CC) -c -o "$@" "$<" $(CFLAGS)