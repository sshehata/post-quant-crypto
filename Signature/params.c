#include "params.h"

#include <assert.h>

#ifdef SIG

// Najnovi na Simona
// w 4 
//                           01  02  03  04
//const unsigned int B_k[] = {112, 20, 20, 32};
//const unsigned int B_n[] = { 32, 20, 20, 112};


// Najnovi na Simona
// w 4 
//                           01  02  03  04
//const unsigned int B_k[] = {152, 20, 20, 32};
//const unsigned int B_n[] = { 32, 20, 20, 152};


// Najnovi na Simona
// w 5  - ne dava brzo
//                           01  02  03  04  05 
const unsigned int B_k[] = {152, 14, 14, 14, 32};
const unsigned int B_n[] = {32, 14, 14, 14, 152};


// Security level 2^80
// w 6
//                             01  02  03  04  05  06
// const unsigned int B_k[] = {82, 48, 48, 48, 48, 30};
// const unsigned int B_n[] = {48, 48, 48, 48, 48, 88};

// Security level 2^87
// w 6
//                             01  02  03  04  05  06
// const unsigned int B_k[] = {84, 48, 48, 48, 48, 30};
// const unsigned int B_n[] = {48, 48, 48, 48, 48,104};

// Security level 2^94
// w 7
//                             01  02  03  04  05  06  07
// const unsigned int B_k[] = {94, 48, 48, 48, 48, 48, 32};
// const unsigned int B_n[] = {48, 48, 48, 48, 48, 48,112};

// Security level 2^101
// w 8
//                           01  02  03  04  05  06  07  08
// const unsigned int B_k[] = {104, 48, 48, 48, 48, 48, 48, 34};
// const unsigned int B_n[] = { 48, 48, 48, 48, 48, 48, 48,112};

// Security level 2^125
// w 12
//                              01  02  03  04  05  06  07  08  09  10  11  12
// const unsigned int B_k[] = {144, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 42};
// const unsigned int B_n[] = { 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48,152};

#else
// Security level 2^80
// w 17
//                              01  02  03  04  05  06  07  08  09  10  11  12  13  14  15  16  17
// const unsigned int B_k[] = { 26,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8, 16};
// const unsigned int B_n[] = { 40, 42, 42, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,500};

// Security level 2^90
// w 17
//                              01  02  03  04  05  06  07  08  09  10  11  12  13  14  15  16  17
// const unsigned int B_k[] = { 32,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8};
// const unsigned int B_n[] = { 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,488};

// Security level 2^114
// w 36
//                              01  02  03  04  05  06  07  08  09  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36
// const unsigned int B_k[] = { 32,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8};
// const unsigned int B_n[] = { 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,616};

// Security level 2^124
// w 56
//                           01  02  03  04  05  06  07  08  09  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40  41  42  43  44  45  46  47  48  49  50  51  52  53  54  55  56
const unsigned int B_k[] = { 32,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8};
const unsigned int B_n[] = { 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,744};

#endif

const size_t NUMBER_OF_BLOCKS_K = ARRAY_SIZE(B_k);
const size_t NUMBER_OF_BLOCKS_N = ARRAY_SIZE(B_n);
const size_t NUMBER_OF_BLOCKS = ARRAY_SIZE(B_k);

