/* alloc.c: Convenient functions for memory allocation
 *
 * Copyright (C) 2025 JGHFunRun
 *
 * This file is part of ToySH - JGHFunRun's Toy Shell
 *
 * This program is free software, licensed under the MIT license. You may
 * distribute and/or modify it according to the terms of the MIT license.
 */

#include <alloc.h>

#include <assert.h>
#include <errno.h>
#include <stdlib.h>

/// @brief Attempts to reallocate \p *buf to be at least \p new_sz bytes and
/// updates \p *buf and \p *sz if successful
///
/// Returns the new buffer location, which will be `NULL` if unsuccessful.
/// Causes of errors and `errno` values are the same as for `realloc()`, with
/// the additional error that if \p buf is `NULL`, `errno = EFAULT` will be set
/// on release builds, and an `assert()` will fail on debug builds.
///
/// @param buf Buffer to reallocate. Must not be `NULL`, although `*buf` may be.
/// @param sz Current size of buffer. Can be set to `NULL` if you don't want to
/// update any size-containing variables.
/// @param new_sz New desired size
void *safeRealloc(void **restrict buf, size_t *restrict sz, size_t new_sz) {
	assert(buf != NULL);

	if (buf == NULL) {
		errno = EFAULT;
		return NULL;
	}

	void *new_buf = realloc(*buf, new_sz);

	if (new_buf != NULL) {
		*buf = new_buf;
		if (sz != NULL)
			*sz = new_sz;
	}

	return new_buf;
}

#define ALLOC_SIZE (4)
#define ALLOC_N (8)
#define MIN_ALLOC_N (4)
/// @brief Reallocates \p *buf if attempting to write `(*buf)[i]` would be a
/// buffer overrun.
///
/// Returns the new/current \p *buf location if writing `(*buf)[i]` is now safe
/// or a `NULL` pointer if reallocation is necessary and has failed, that is to
/// say if writing to `(*buf)[i]` would still be a buffer overrun even after
/// calling this function. Causes of errors and `errno` values are the same as
/// `realloc()`, with the addition that if \p buf or \p sz is `NULL`, it will
/// error with `errno = EFAULT` on release builds, and an `assert()` will fail
/// on debug builds.
///
/// @param buf Buffer to ensure safe indexing into. Cannot be `NULL`, although
/// \p *buf may be.
/// @param sz Current size of buffer. Cannot be `NULL`.
char *autoiAlloc(char **restrict buf, size_t *restrict sz, size_t i) {
	assert(buf != NULL);
	assert(sz != NULL);

	if (buf == NULL ||
	    sz == NULL) {
		errno = EFAULT;
		return NULL;
	}

	return i >= *sz ? safeReallocArr(buf, sz, i) : *buf;
}
