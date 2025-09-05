/* sstring.c: TODO: short desc
 */

#include "sstring.h"

#include "alloc.h"
#include "filemgmt.h"

ssize_t ssgetline(SString *restrict sstr, FILE *restrict fp) {
	ssize_t rval = getline(&sstr->buf, &sstr->sz, fp);

	if (rval == -1) {
		sstr->len = 0;
	} else {
		sstr->len = rval;
	}

	return rval;
}

char *ssautoiAlloc(SString *sstr, size_t i) {
	return autoiAlloc(&sstr->buf, &sstr->sz, i);
}

char *ssset(SString *sstr, size_t i, char c) {
	char *rval = ssautoiAlloc(sstr, i);

	if (rval != NULL) {
		sstr->len = i+1 > sstr->len ? i+1 : sstr->len;
		sstr->buf[i] = c;
	}

	return rval;
}
