/* alloc.h: header file for alloc.c
 *
 * Copyright (C) 2025 JGHFunRun
 * 
 * This file is part of jgtsh - JGHFunRun's shell
 *
 * This program is free software, licensed under the MIT license. You may
 * distribute and/or modify it according to the terms of the MIT license.
 */

void *safeRealloc(void **restrict buf, size_t *restrict sz, size_t new_sz);
void *autoiRealloc(char **restrict buf, size_t *restrict sz, size_t i);
