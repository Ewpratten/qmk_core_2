#include "vortex.h"
#include "proto.h"
#include "quantum.h"
#include "raw_hid.h"
#include "debug.h"

#define ER 0x80
#define LK(k,s) ((k & 0xFF) | ((s & 0xFF) << 8))

const uint8_t keymap_layouts[NUM_LAYOUTS][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_60_ansi(
        1,  2,  3,  4,  5,  6,  7,  8,  9,  10,  11, 12, 13, 14,
        15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41,
        42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53,
        54, 55, 56, 57, 58, 59, 60, 61
    ),
    LAYOUT_60_ansi_split_lshift(
        1,  2,  3,  4,  5,  6,  7,  8,  9,  10,  11, 12, 13, 14,
        15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41,
        42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54,
        55, 56, 57, 58, 59, 60, 61, 62
    ),
    LAYOUT_60_ansi_split_rshift(
        1,  2,  3,  4,  5,  6,  7,  8,  9,  10,  11, 12, 13, 14,
        15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41,
        42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54,
        55, 56, 57, 58, 59, 60, 61, 62
    ),
    LAYOUT_60_ansi_split_lshift_rshift(
        1,  2,  3,  4,  5,  6,  7,  8,  9,  10,  11, 12, 13, 14,
        15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41,
        42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55,
        56, 57, 58, 59, 60, 61, 62, 63
    ),
};

const char *layout_names =
    "ansi60,"           // ansi 60%
    "ansi60_spls,"      // split left shift
    "ansi60_sprs,"      // split right shift
    "ansi60_splsrs,"    // split left and right shift
;