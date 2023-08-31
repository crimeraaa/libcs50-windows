/**
 * CS50 Library for C
 * https://github.com/cs50/libcs50
 *
 * Based on Eric Roberts' genlib.c and simpio.c.
 *
 * Copyright (c) 2023
 * All rights reserved
 *
 * BSD 3-Clause License
 * http://www.opensource.org/licenses/BSD-3-Clause
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * * Neither the name of CS50 nor the names of its contributors may be used
 *   to endorse or promote products derived from this software without
 *   specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef CS50_FOR_WINDOWS_H
#define CS50_FOR_WINDOWS_H

#include <float.h>
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>

/**
 * Check for the _WIN32 macro. Even if you're on 64-bit Windows, this macro 
 * should (ideally, anyway) be defined. If you're on Windows but this isn't
 * defined somehow, something is very very wrong!
 * 
 * Also note that Microsoft specifically says it must be defined to be 1,
 * otherwise, any other value would probably lead to undefined behavior.
 */
#if defined(_WIN32) && (_WIN32 == 1)
    /**
     * The MAKE_DLL_EXPORTS macro should only be defined when buillding the library.
     * For GCC, use the -D flag. e.g. -D MAKE_DLL_EXPORTS
     * For MSVC, use the /D flag, e.g. /DMAKE_DLL_EXPORTS
     * 
     * Do note that the Makefile and .bat build scripts already take care of 
     * these parts for you!
      */
    #ifdef MAKE_DLL_EXPORTS
        /**
         * The CS50_API macro tells us whether to "export" the functions, 
         * as in building a DLL, or to simply "import" them, as in a user 
         * program that has the line #include <cs50.h>
          */
        #define CS50_API __declspec(dllexport)
    #else
        #define CS50_API __declspec(dllimport)
    #endif

    /**
     * Set the calling convention.
     * __cdecl means, well, the C calling convention for C and C++ programs.
     * Do note it's Microsoft-specific, hence we check for _WIN32.
     * I'm very new to DLLs so I'm unsure whether this is better than __stdcall.
      */
    #define CS50_CALL __cdecl

#else /* _WIN32 not defined. */
    #error If you are not on Windows (e.g. Linux, MacOS) please use the \
           original version of the CS50 Libary for C. \
           Otherwise, if you are on Windows, but see this error, please \
           file a bug report at my GitHub fork here: \
           https://github.com/crimeraaa/libcs50-windows
#endif /* _WIN32 */

#ifdef __GNUC__
    /**
     * The printf format attribute lets us check format string arguments on a 
     * stricter level. Specifically, it helps check if insufficient arguments
     * are supplied to the format string, OR if any one argument does not
     * match with the respective format specifier.
     * 
     * @param fmt The argument number of the format string.
     * @param arg The argument number where arguments to fmt start.
     */
    #define CS50_FMT(fmt, arg) __attribute__((format(printf, fmt, arg)))

    /** 
     * Example:     char *get_string(const char *fmt, ...) CS50_FMT(1, 2)
     * Explanation: The argument named "fmt" is argument #1.
     *              The variadic arguments "..." are considered argument 2.
     * 
     *              So this signals to GCC that it should verify if argument #1
     *              has the correct specifiers for the varargs in argument #2.
     */
#else /* __GNUC__ not defined. */

    /**
     * Set the CS50_FMT macro to be empty.
     * This is because that printf format attribute is a GNU extension.
     * 
     * So I set it to be empty if you're compiling this with say, MSVC,
     * so that the macro isn't completely undefined - it just does nothing.
      */
    #define CS50_FMT(fmt, arg)

#endif /* __GNUC__ */

/**
 * Our own type for (pointers to) strings.
 */
typedef char *string;

/**
 * Prompts user for a line of text from standard input and returns the
 * equivalent char; if text is not a single char, user is prompted
 * to retry. If line can't be read, returns CHAR_MAX.
 */
CS50_API char CS50_CALL get_char(const char *format, ...) CS50_FMT(1, 2);

/**
 * Prompts user for a line of text from standard input and returns the
 * equivalent double as precisely as possible; if text does not represent
 * a double or if value would cause underflow or overflow, user is
 * prompted to retry. If line can't be read, returns DBL_MAX.
 */
CS50_API double CS50_CALL get_double(const char *format, ...) CS50_FMT(1, 2);

/**
 * Prompts user for a line of text from standard input and returns the
 * equivalent float as precisely as possible; if text does not represent
 * a float or if value would cause underflow or overflow, user is prompted
 * to retry. If line can't be read, returns FLT_MAX.
 */
CS50_API float CS50_CALL get_float(const char *format, ...) CS50_FMT(1, 2);

/**
 * Prompts user for a line of text from standard input and returns the
 * equivalent int; if text does not represent an int in [-2^31, 2^31 - 1)
 * or would cause underflow or overflow, user is prompted to retry. If line
 * can't be read, returns INT_MAX.
 */
CS50_API int CS50_CALL get_int(const char *format, ...) CS50_FMT(1, 2);

/**
 * Prompts user for a line of text from standard input and returns the
 * equivalent long; if text does not represent a long in
 * [-2^63, 2^63 - 1) or would cause underflow or overflow, user is
 * prompted to retry. If line can't be read, returns LONG_MAX.
 */
CS50_API long CS50_CALL get_long(const char *format, ...) CS50_FMT(1, 2);

/**
 * Prompts user for a line of text from standard input and returns the
 * equivalent long long; if text does not represent a long long in
 * [-2^63, 2^63 - 1) or would cause underflow or overflow, user is
 * prompted to retry. If line can't be read, returns LLONG_MAX.
 */
CS50_API long long CS50_CALL get_long_long(const char *format, ...) CS50_FMT(1, 2);

/**
 * Prompts user for a line of text from standard input and returns
 * it as a string (char *), sans trailing line ending. Supports
 * CR (\r), LF (\n), and CRLF (\r\n) as line endings. If user
 * inputs only a line ending, returns "", not NULL. Returns NULL
 * upon error or no input whatsoever (i.e., just EOF). Stores string
 * on heap, but library's destructor frees memory on program's exit.
 */
CS50_API string CS50_CALL get_string(va_list *args, const char *format, ...) CS50_FMT(2, 3);

/**
 * User-facing macro for get_string. Treat it like:
 * get_string(const char *fmt, ...);
 * 
 * @param fmt The format string with 0 or more format specifiers.
 * @param ... The arguments for the string with respect to format specifiers. 
 */
#define get_string(...) get_string(NULL, __VA_ARGS__)

#endif /* CS50_FOR_WINDOWS_H */
