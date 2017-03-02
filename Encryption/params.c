#include "params.h"

#include <assert.h>

// Security level 2^??
// w 30
//                           01  02  03  04  05  06  07  08  09  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30
//const unsigned int B_k[] = { 24,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8};
//const unsigned int B_n[] = { 24, 40, 40, 40, 40, 40, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 64};

// Interesen balans pomegju brzina i dolzhina i security
// Security level 2^??
// w 30
//                           01  02  03  04  05  06  07  08  09  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30
//const unsigned int B_k[] = { 22, 10,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8};
//const unsigned int B_n[] = { 22, 40, 40, 40, 40, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 64};

// Interesen balans pomegju brzina i dolzhina i security
// Security level 2^??
// w 30
//                           01  02  03  04  05  06  07  08  09  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30
//const unsigned int B_k[] = { 20, 10, 10,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8};
//const unsigned int B_n[] = { 20, 40, 40, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 64};


// Interesen balans pomegju brzina i dolzhina i security
// Security level 2^??
// w 32
//                           01  02  03  04  05  06  07  08  09  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32
const unsigned int B_k[] = { 16,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8};
const unsigned int B_n[] = { 16, 32, 30, 32, 30, 32, 30, 32, 30, 32, 30, 32, 30, 32, 30, 32, 30, 32, 30, 32, 30, 32, 30, 32, 30, 32, 30, 32, 30, 32, 30, 70};


// Security level 2^??
// w 32
//                           01  02  03  04  05  06  07  08  09  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32
// const unsigned int B_k[] = {  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8};
// const unsigned int B_n[] = {  8, 16, 16, 16, 16, 48, 16, 32, 40, 40, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 64};


// Security level 2^??
// w 10
//                           01  02  03  04  05  06  07  08  09  10
// const unsigned int B_k[] = { 16,  8,  8,  8,  8,  8,  8,  8,  8, 16};
// const unsigned int B_n[] = { 16, 28, 28, 28, 28, 28, 28, 28, 28,176};


// Security level 2^??
// w 10
//                           01  02  03  04  05  06  07  08  09  10
// const unsigned int B_k[] = { 28,  8,  8,  8,  8,  8,  8,  8,  8, 16};
// const unsigned int B_n[] = { 28, 32, 32, 32, 32, 32, 32, 32, 32,300};


// Security level 2^80
// w 17
//                              01  02  03  04  05  06  07  08  09  10  11  12  13  14  15  16  17
// const unsigned int B_k[] = { 26,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8, 16};
// const unsigned int B_n[] = { 40, 42, 42, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,500};

// Security level 2^90
// w 17
//                           01  02  03  04  05  06  07  08  09  10  11  12  13  14  15  16  17
//const unsigned int B_k[] = { 32,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8};
//const unsigned int B_n[] = { 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,488};

// Security level 2^114
// w 36
//                              01  02  03  04  05  06  07  08  09  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36
// const unsigned int B_k[] = { 32,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8};
// const unsigned int B_n[] = { 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,616};

// Security level 2^124
// w 56
//                           01  02  03  04  05  06  07  08  09  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40  41  42  43  44  45  46  47  48  49  50  51  52  53  54  55  56
// const unsigned int B_k[] = { 32,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8};
// const unsigned int B_n[] = { 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,744};

const size_t NUMBER_OF_BLOCKS_K = ARRAY_SIZE(B_k);
const size_t NUMBER_OF_BLOCKS_N = ARRAY_SIZE(B_n);
const size_t NUMBER_OF_BLOCKS = ARRAY_SIZE(B_k);

