/* invocation.h: Provides the command used to invoke toysh
 *
 * (no .c file exists, although "owned" by main.c)
 *
 * Copyright (C) 2025 JGHFunRun
 *
 * This file is part of ToySH - JGHFunRun's Toy Shell
 *
 * This program is free software, licensed under the MIT license. You may
 * distribute and/or modify it according to the terms of the MIT license.
 */

#ifndef INVOCATION_H
#define INVOCATION_H 1

#ifndef CONST_OUTSIDE_MAIN_C
# ifdef IN_MAIN_C
#  define CONST_OUTSIDE_MAIN_C /* not constant */
# else // IN_MAIN_C
#  define CONST_OUTSIDE_MAIN_C const
# endif // #else (IN_MAIN_C)
#endif // !def CONST_OUTSIDE_MAIN_C

/// @brief The command used to invoke ToySH, or at least what the invoking
/// program wants us to think was used; the first argument provided.
///
/// This should be used only for logging purposes; other methods must be used to
/// acquire the path to internal files such as translations.
extern char const *CONST_OUTSIDE_MAIN_C invoked_as;

#endif // INVOCATION_H
