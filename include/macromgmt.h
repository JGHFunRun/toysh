/* macromgmt.h: provide testing for various macros
 *
 * (no .c file exists)
 *
 * Copyright (C) 2025 JGHFunRun
 *
 * This file is part of ToySH - JGHFunRun's Toy Shell
 *
 * This program is free software, licensed under the MIT license. You may
 * distribute and/or modify it according to the terms of the MIT license.
 */

#ifndef NO_MACROMGMT_H

#ifndef MACROMGMT_H
#define MACROMGMT_H

#if __has_include(<unistd.h>)
# ifndef __unix__
#  define __unix__ 1
# endif // !__unix__
#endif // __has_include(<unistd.h>)

#ifdef _WIN32
# ifdef __unix__
#  define __unix__CMPT_WIN32 1
# else // __unix__
#  define PURE_WIN32 1
# endif // #else (__unix__)
#elifdef __unix__ // (_WIN32)
# define PURE__unix__ 1
#endif // __unix__

// TODO: There should be a flag to indicate if win+unix should prefer windows or
// unix methods
// Perhaps with values to indicate any of the following:
// * Use WIN32 code when both are perfect match,
//      but use POSIX code when non-equivalent
// * Always use WIN32 code
// * Always use POSIX code

#endif // MACROMGMT_H

#endif // !NO_MACROMGMT_H
