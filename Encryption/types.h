#ifndef TYPES_H
#define TYPES_H

#include <string.h>
#include <inttypes.h>
#include <math.h>

#define ARRAY_SIZE(x) ((sizeof (x)) / (sizeof (x)[0]))
#define BYTES(x) (((size_t) ceil((x) / 8)) + 1)

#define SIG

#ifdef SIG
	#define ENCRYPTION false
	#define SIGNATURE true
#else
    #define ENCRYPTION true
	#define SIGNATURE false
#endif


#endif
