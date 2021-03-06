#include "../src/lib/ccurl.h"
#include "../src/lib/curl.h"
#include "../src/lib/hash.h"
#include "../src/lib/util/converter.h"
#include "cunit_include.h"
#include "random_trits.h"
#include <stdio.h>
#include <string.h>

static const size_t length = STATE_LENGTH;
static const int length_2 = length;
static const trit_t trits_2[] = (const trit_t[]){
    0,  -1, 0,  -1, -1, -1, -1, -1, -1, 0,  -1, -1, -1, -1, -1, 0,  0,  -1, -1,
    -1, 0,  -1, -1, 0,  0,  -1, 0,  0,  -1, 0,  0,  -1, -1, -1, -1, 0,  -1, -1,
    0,  -1, 0,  -1, -1, -1, 0,  -1, 0,  0,  -1, -1, -1, -1, 0,  0,  -1, 0,  -1,
    0,  0,  -1, -1, -1, 0,  -1, -1, -1, -1, -1, 0,  -1, -1, -1, 0,  -1, 0,  0,
    -1, -1, 0,  0,  0,  -1, 0,  -1, -1, -1, 0,  0,  -1, -1, 0,  0,  0,  -1, 0,
    0,  0,  -1, 0,  0,  0,  0,  -1, 0,  0,  0,  -1, 0,  0,  0,  -1, 0,  0,  0,
    0,  0,  0,  0,  -1, -1, -1, -1, -1, -1, 0,  0,  -1, -1, 0,  0,  -1, 0,  0,
    0,  0,  0,  0,  -1, 0,  0,  -1, -1, -1, 0,  0,  -1, 0,  0,  -1, 0,  -1, -1,
    0,  0,  -1, -1, -1, -1, 0,  -1, -1, 0,  -1, 0,  -1, -1, 0,  -1, 0,  0,  0,
    0,  -1, 0,  0,  -1, 0,  0,  0,  0,  -1, 0,  -1, 0,  -1, 0,  0,  -1, -1, 0,
    0,  -1, -1, -1, -1, 0,  -1, -1, -1, -1, 0,  -1, 0,  0,  -1, -1, 0,  0,  0,
    0,  -1, 0,  0,  0,  0,  0,  0,  0,  0,  0,  -1, 0,  -1, -1, -1, -1, 0,  0,
    -1, -1, -1, 0,  -1, 0,  0,  0,  -1, -1, -1, -1, -1, 0,  0,  -1, 0,  0,  -1,
    0,  0,  0,  -1, -1, -1, -1, -1, -1, 0,  -1, 0,  0,  0,  0,  -1, -1, -1, 0,
    -1, -1, 0,  0,  -1, 0,  0,  0,  -1, 0,  -1, 0,  0,  -1, 0,  0,  -1, -1, -1,
    0,  0,  -1, 0,  0,  -1, -1, -1, -1, 0,  0,  -1, -1, 0,  0,  0,  -1, -1, -1,
    0,  -1, -1, 0,  -1, -1, -1, -1, 0,  -1, 0,  -1, -1, 0,  0,  0,  0,  -1, -1,
    0,  0,  0,  -1, 0,  0,  0,  -1, -1, -1, 0,  0,  -1, 0,  -1, -1, -1, -1, 0,
    -1, -1, 0,  -1, -1, 0,  -1, -1, -1, 0,  -1, 0,  0,  -1, -1, 0,  -1, 0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  -1, -1, 0,  -1, -1, 0,  -1, 0,  0,  -1, 0,
    -1, -1, 0,  0,  0,  -1, 0,  0,  -1, 0,  0,  0,  -1, 0,  0,  0,  0,  -1, 0,
    0,  -1, -1, -1, -1, 0,  -1, -1, -1, -1, -1, 0,  -1, 0,  0,  0,  -1, 0,  -1,
    0,  -1, -1, 0,  -1, 0,  -1, 0,  0,  0,  0,  0,  -1, -1, 0,  -1, 0,  -1, -1,
    0,  0,  -1, 0,  0,  0,  -1, -1, 0,  -1, 0,  0,  0,  0,  -1, -1, 0,  -1, -1,
    -1, -1, -1, 0,  0,  -1, -1, 0,  -1, 0,  -1, 0,  -1, -1, -1, -1, -1, 0,  0,
    0,  -1, 0,  -1, 0,  0,  -1, -1, 0,  -1, 0,  -1, -1, -1, 0,  -1, 0,  0,  0,
    0,  -1, -1, -1, 0,  -1, -1, -1, 0,  -1, -1, -1, 0,  0,  -1, 0,  0,  -1, 0,
    0,  0,  -1, -1, 0,  0,  0,  -1, -1, 0,  -1, 0,  -1, 0,  -1, -1, 0,  -1, -1,
    -1, 0,  -1, -1, 0,  -1, -1, 0,  0,  0,  0,  0,  0,  -1, 0,  0,  0,  -1, -1,
    -1, -1, 0,  0,  -1, 0,  -1, 0,  -1, -1, -1, -1, -1, -1, 0,  0,  -1, -1, 0,
    -1, -1, -1, 0,  0,  -1, 0,  0,  -1, -1, -1, 0,  0,  -1, -1, -1, -1, -1, 0,
    -1, -1, 0,  0,  -1, -1, -1, -1, 0,  0,  -1, 0,  -1, 0,  0,  0,  -1, -1, 0,
    -1, 0,  -1, -1, -1, -1, 0,  0,  -1, -1, -1, -1, -1, -1, -1, 0,  0,  0,  -1,
    0,  -1, 0,  -1, -1, 0,  0,  -1, 0,  0,  0,  -1, -1, 0,  0,  0,  0,  0,  0,
    -1, 0,  0,  0,  0,  0,  0,  -1, -1, 0,  -1, -1, 0,  -1, 0,  0,  -1, -1, 0,
    -1, 0,  0,  0,  0,  0,  -1, -1, 0,  -1, 0,  0,  0,  -1, 0,  -1, 0,  0,  0,
    -1, -1, -1, 0,  -1, 0,  0,  0,  0,  0,  -1, 0,  -1, -1, 0,  -1, 0,  -1, 0,
    0,  -1, -1, 0,  0,  0,  0,  -1, 0,  -1, -1, 0,  0,  -1, -1, -1, -1, -1, 0,
    -1, -1, 0,  -1, 0,  -1, 0};
static const trit_t expect_2[] = (const trit_t[]){
    0,  1,  1,  0,  -1, 0,  1,  0,  1,  -1, -1, 0,  0,  1,  0,  -1, 1,  1,  -1,
    1,  -1, 1,  1,  1,  0,  -1, 0,  1,  -1, -1, 1,  0,  0,  -1, -1, -1, 1,  0,
    -1, 1,  1,  0,  0,  -1, 1,  -1, 1,  0,  0,  -1, 1,  0,  1,  1,  1,  1,  -1,
    1,  -1, 0,  1,  0,  1,  -1, 0,  0,  1,  1,  0,  0,  1,  0,  1,  0,  -1, -1,
    1,  -1, 1,  0,  1,  -1, -1, -1, 0,  -1, -1, 1,  1,  0,  0,  0,  -1, 1,  0,
    0,  0,  -1, 0,  0,  -1, -1, 1,  0,  1,  -1, 0,  0,  1,  1,  0,  -1, 0,  0,
    -1, -1, 1,  0,  -1, -1, -1, 0,  1,  -1, 0,  -1, 0,  1,  -1, -1, 0,  -1, 0,
    0,  0,  0,  0,  -1, -1, -1, -1, 0,  1,  -1, -1, 1,  0,  -1, 0,  -1, -1, 1,
    1,  0,  0,  1,  -1, -1, -1, 1,  1,  1,  1,  -1, -1, -1, 0,  -1, 1,  0,  -1,
    0,  1,  1,  0,  -1, -1, -1, -1, 1,  -1, 1,  -1, 0,  1,  1,  0,  1,  0,  0,
    0,  1,  1,  -1, 1,  -1, 1,  1,  0,  0,  1,  1,  -1, 0,  -1, 1,  -1, -1, 0,
    -1, -1, 0,  1,  -1, 0,  -1, 1,  -1, -1, 0,  0,  -1, 1,  0,  0,  1,  0,  -1,
    0,  1,  1,  1,  -1, 1,  0,  1,  1,  1,  1,  0,  1,  -1, -1, -1, 1,  0,  1,
    -1, 1,  1,  1,  1,  1,  0,  0,  1,  0,  -1, 1,  0,  1,  1,  1,  0,  0,  -1,
    0,  -1, -1, -1, 1,  1,  0,  0,  0,  0,  0,  -1, 1,  1,  1,  1,  1,  -1, -1,
    -1, 0,  -1, 0,  -1, 1,  0,  1,  1,  -1, 1,  0,  0,  -1, -1, 0,  -1, -1, 1,
    -1, 1,  -1, -1, -1, 1,  -1, 0,  0,  1,  0,  0,  1,  -1, -1, 0,  -1, -1, 0,
    -1, 1,  0,  0,  -1, -1, -1, 0,  0,  1,  0,  1,  0,  1,  -1, -1, 1,  0,  1,
    -1, 1,  -1, -1, -1, 0,  0,  0,  0,  -1, 1,  1,  1,  0,  1,  -1, 0,  -1, -1,
    0,  -1, 0,  0,  0,  0,  -1, 1,  -1, -1, 1,  0,  1,  -1, -1, 0,  -1, 1,  1,
    -1, -1, 1,  -1, 0,  1,  1,  1,  0,  -1, -1, -1, -1, 1,  0,  0,  0,  1,  1,
    1,  -1, 0,  0,  -1, 0,  1,  0,  -1, 0,  0,  -1, 1,  0,  1,  -1, 1,  0,  0,
    0,  1,  1,  1,  0,  -1, 1,  1,  -1, 0,  0,  -1, -1, 0,  -1, -1, 0,  -1, 0,
    -1, 1,  1,  0,  1,  0,  1,  -1, -1, 0,  -1, 1,  -1, -1, 0,  -1, 1,  1,  0,
    1,  0,  0,  -1, 0,  0,  1,  -1, 0,  -1, -1, -1, 1,  0,  -1, -1, 1,  0,  0,
    0,  1,  -1, 0,  1,  -1, 1,  -1, 0,  -1, 0,  -1, 0,  -1, 0,  0,  0,  0,  0,
    0,  -1, 0,  0,  1,  0,  -1, -1, 0,  -1, 0,  0,  0,  1,  0,  1,  0,  1,  1,
    0,  0,  -1, -1, 0,  1,  1,  -1, -1, -1, 1,  0,  1,  -1, -1, -1, 1,  1,  1,
    0,  -1, 0,  0,  0,  0,  0,  0,  1,  1,  -1, -1, 0,  0,  1,  0,  1,  1,  0,
    -1, 1,  0,  -1, 0,  1,  0,  1,  1,  1,  -1, 1,  0,  0,  0,  1,  0,  1,  0,
    -1, 1,  0,  1,  1,  -1, -1, -1, 0,  -1, -1, 1,  1,  1,  -1, 1,  1,  -1, -1,
    0,  0,  -1, 0,  1,  -1, -1, 1,  -1, -1, 1,  1,  -1, -1, 1,  -1, -1, -1, -1,
    0,  1,  1,  0,  -1, -1, -1, 0,  0,  0,  -1, 0,  0,  0,  1,  0,  -1, 0,  1,
    0,  -1, -1, 0,  1,  1,  1,  -1, -1, 1,  1,  -1, 1,  -1, -1, 1,  0,  0,  1,
    -1, 0,  -1, 1,  0,  -1, 1,  0,  1,  -1, 1,  1,  -1, -1, -1, 0,  1,  1,  0,
    1,  1,  -1, 0,  -1, 0,  0,  -1, 1,  1,  -1, 0,  1,  1,  1,  1,  1,  0,  -1,
    1,  0,  0,  -1, -1, -1, 1,  0,  -1, -1, 1,  0,  -1, 1,  -1, 1,  -1, 0,  1,
    1,  -1, 1,  0,  0,  1,  -1, -1, -1, 1,  1,  1,  1,  -1, 0,  0,  -1, 0,  1,
    -1, 0,  1,  1,  -1, -1, -1};

static const trit_t trits_in_2[] = (const trit_t[]){
    0,  0,  -1, -1, 0,  0,  -1, 0,  -1, -1, -1, -1, 0,  -1, 0,  -1, 0,  -1, -1,
    0,  -1, -1, -1, 0,  -1, 0,  0,  -1, 0,  0,  0,  -1, 0,  0,  -1, 0,  0,  0,
    -1, 0,  -1, 0,  -1, -1, 0,  0,  -1, -1, -1, 0,  0,  0,  -1, 0,  -1, -1, -1,
    0,  0,  0,  0,  -1, 0,  -1, -1, 0,  -1, 0,  0,  0,  -1, 0,  0,  -1, -1, -1,
    0,  0,  0,  0,  -1, 0,  0,  0,  -1, 0,  0,  0,  -1, 0,  -1, -1, -1, -1, -1,
    0,  -1, -1, -1, 0,  -1, -1, 0,  -1, -1, -1, 0,  -1, 0,  0,  -1, -1, 0,  -1,
    0,  0,  0,  0,  0,  -1, 0,  0,  -1, -1, -1, -1, -1, -1, 0,  0,  -1, -1, -1,
    -1, -1, 0,  0,  -1, -1, -1, -1, 0,  0,  0,  -1, 0,  -1, -1, -1, -1, -1, 0,
    0,  0,  -1, 0,  -1, -1, -1, -1, -1, 0,  0,  -1, 0,  -1, -1, -1, -1, -1, -1,
    0,  -1, -1, -1, 0,  0,  0,  -1, -1, -1, -1, 0,  -1, 0,  -1, -1, -1, -1, 0,
    0,  0,  0,  0,  0,  -1, -1, 0,  0,  0,  -1, 0,  -1, -1, 0,  0,  -1, 0,  0,
    0,  0,  0,  0,  0,  0,  0,  -1, -1, -1, -1, -1, 0,  0,  0,  0,  -1, 0,  0,
    0,  0,  -1, 0,  -1, -1, 0,  -1, 0,  -1, -1, 0,  -1, -1, 0,  0,  0,  0,  0,
    0,  0,  -1, 0,  0,  -1, -1, -1, 0,  0,  0,  -1, 0,  -1, 0,  -1, 0,  -1, 0,
    0,  0,  -1, -1, 0,  0,  0,  0,  0,  -1, 0,  0,  -1, 0,  -1, -1, -1, -1, 0,
    -1, -1, -1, -1, -1, 0,  0,  -1, -1, -1, -1, -1, 0,  0,  -1, -1, -1, -1, 0,
    0,  -1, 0,  0,  0,  -1, 0,  0,  0,  0,  -1, 0,  0,  -1, -1, 0,  -1, 0,  0,
    -1, 0,  0,  -1, -1, -1, -1, 0,  0,  0,  0,  0,  0,  0,  0,  0,  -1, 0,  0,
    -1, 0,  -1, -1, 0,  -1, 0,  0,  0,  0,  0,  0,  -1, -1, -1, 0,  -1, -1, -1,
    -1, 0,  0,  0,  -1, -1, 0,  0,  -1, -1, -1, 0,  0,  -1, 0,  0,  0,  0,  -1,
    0,  -1, -1, 0,  -1, -1, 0,  0,  -1, -1, 0,  -1, 0,  0,  0,  -1, -1, 0,  -1,
    0,  0,  0,  0,  0,  -1, 0,  0,  -1, -1, -1, 0,  -1, -1, 0,  0,  -1, 0,  0,
    -1, 0,  0,  0,  -1, 0,  0,  -1, 0,  0,  -1, 0,  -1, -1, -1, -1, -1, 0,  -1,
    -1, -1, 0,  -1, -1, -1, 0,  -1, 0,  -1, 0,  -1, 0,  -1, 0,  -1, -1, 0,  0,
    -1, -1, -1, -1, 0,  -1, 0,  0,  -1, 0,  0,  -1, 0,  0,  -1, -1, 0,  0,  0,
    -1, 0,  0,  0,  -1, -1, 0,  -1, 0,  0,  -1, 0,  -1, 0,  -1, 0,  0,  -1, 0,
    0,  -1, -1, 0,  0,  0,  0,  -1, -1, 0,  0,  0,  -1, -1, 0,  0,  -1, 0,  -1,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  -1, 0,  0,  -1, 0,  0,  -1, 0,  -1, -1,
    0,  0,  -1, 0,  -1, -1, 0,  -1, -1, 0,  -1, 0,  0,  -1, -1, 0,  -1, -1, 0,
    -1, -1, 0,  -1, -1, -1, -1, 0,  0,  0,  -1, 0,  -1, -1, -1, -1, 0,  -1, 0,
    0,  -1, 0,  -1, 0,  -1, -1, -1, 0,  0,  0,  -1, 0,  0,  0,  0,  -1, -1, 0,
    -1, -1, 0,  0,  0,  0,  -1, 0,  -1, 0,  -1, 0,  -1, -1, 0,  -1, -1, 0,  -1,
    0,  0,  0,  0,  -1, 0,  0,  0,  -1, -1, -1, -1, -1, -1, -1, 0,  0,  0,  0,
    -1, -1, -1, -1, -1, 0,  0,  -1, 0,  -1, 0,  -1, -1, -1, -1, -1, -1, -1, 0,
    -1, 0,  0,  -1, -1, -1, -1, -1, 0,  -1, 0,  0,  0,  0,  -1, 0,  -1, 0,  0,
    -1, 0,  -1, -1, 0,  0,  0,  0,  0,  0,  -1, -1, 0,  -1, 0,  0,  -1, 0,  0,
    -1, -1, -1, -1, 0,  -1, -1, -1, 0,  0,  0,  -1, -1, 0,  -1, 0,  0,  -1, 0,
    -1, 0,  0,  0,  -1, 0,  -1, 0,  0,  0,  -1, -1, 0,  -1, 0,  0,  -1, 0,  0,
    -1, 0,  0,  -1, -1, -1, 0};
static const trit_t trits_out_2[] = (const trit_t[]){
    1,  1,  1,  1,  1,  0,  0,  0,  1,  -1, 0,  -1, 0,  0,  0,  0,  1,  0,  1,
    0,  1,  -1, 1,  1,  1,  1,  1,  1,  1,  0,  1,  0,  -1, 1,  0,  -1, -1, 1,
    1,  0,  1,  1,  1,  1,  0,  -1, 0,  1,  0,  -1, 0,  0,  1,  1,  0,  0,  0,
    0,  -1, 0,  0,  1,  0,  -1, 1,  0,  1,  1,  1,  -1, 1,  1,  1,  1,  1,  0,
    1,  1,  -1, 1,  1,  1,  -1, 0,  1,  0,  1,  -1, -1, 0,  1,  1,  0,  1,  0,
    -1, 1,  1,  1,  0,  1,  0,  1,  1,  -1, -1, -1, -1, -1, 1,  -1, 0,  1,  1,
    0,  1,  0,  -1, -1, -1, -1, 0,  0,  1,  1,  0,  0,  1,  -1, 0,  1,  1,  1,
    -1, 0,  -1, 0,  -1, 1,  1,  1,  0,  1,  1,  -1, 0,  -1, -1, -1, 0,  0,  1,
    -1, -1, 0,  0,  -1, 1,  -1, 1,  0,  0,  -1, 1,  1,  1,  -1, -1, 1,  -1, 0,
    0,  -1, 1,  -1, -1, 0,  0,  1,  0,  0,  1,  0,  -1, -1, -1, 1,  1,  -1, 0,
    -1, 1,  -1, 0,  0,  0,  1,  -1, 1,  0,  1,  1,  1,  -1, -1, 0,  1,  -1, 1,
    0,  0,  0,  1,  -1, 0,  -1, 1,  1,  0,  0,  -1, -1, 1,  -1, 0,  -1, 0,  1,
    0,  1,  0,  -1, 0,  1,  -1, 0,  1,  1,  0,  -1, -1, -1, -1, 1,  0,  -1, 1,
    0,  -1, 0,  0,  0,  -1, 0,  -1, 0,  1,  0,  0,  0,  1,  1,  1,  1,  0,  1,
    -1, 1,  1,  -1, 0,  0,  -1, 1,  -1, -1, -1, -1, -1, -1, 0,  0,  -1, -1, 0,
    -1, 1,  0,  1,  1,  1,  -1, 0,  1,  0,  1,  1,  -1, -1, -1, 0,  1,  1,  -1,
    1,  0,  0,  0,  1,  1,  0,  -1, 0,  1,  1,  1,  0,  0,  0,  1,  -1, 1,  0,
    0,  0,  0,  -1, 1,  0,  0,  1,  0,  0,  0,  -1, -1, 1,  0,  1,  0,  0,  1,
    -1, -1, 0,  0,  0,  1,  0,  -1, 0,  -1, 1,  -1, -1, 0,  1,  1,  0,  -1, 1,
    -1, -1, 1,  1,  0,  -1, 0,  1,  -1, 1,  -1, 1,  1,  1,  0,  0,  -1, 0,  0,
    1,  -1, 1,  0,  -1, 0,  1,  1,  1,  0,  1,  0,  -1, 1,  1,  -1, -1, -1, 1,
    -1, -1, 1,  1,  -1, 0,  1,  -1, 0,  -1, 1,  1,  1,  1,  0,  1,  -1, 0,  0,
    1,  -1, 1,  -1, 1,  -1, -1, 0,  -1, 1,  0,  0,  0,  1,  0,  0,  0,  1,  0,
    1,  0,  -1, -1, -1, 0,  0,  -1, 1,  -1, -1, 1,  1,  0,  -1, 1,  0,  0,  1,
    -1, 1,  0,  1,  0,  1,  0,  1,  1,  0,  1,  0,  0,  -1, 0,  -1, 1,  1,  1,
    1,  1,  1,  1,  0,  -1, 0,  0,  0,  -1, 1,  1,  1,  1,  0,  1,  0,  1,  0,
    1,  0,  -1, 1,  1,  -1, 1,  1,  -1, 1,  -1, -1, 1,  -1, -1, -1, -1, 1,  -1,
    -1, 0,  -1, 0,  1,  1,  0,  -1, 1,  1,  0,  1,  1,  -1, 0,  0,  0,  -1, 1,
    -1, 1,  -1, 1,  -1, 0,  1,  -1, -1, -1, 0,  0,  1,  -1, -1, -1, 0,  0,  1,
    0,  1,  0,  -1, 0,  0,  0,  -1, 0,  0,  1,  1,  0,  -1, 0,  1,  1,  -1, 0,
    0,  1,  0,  1,  1,  -1, 1,  -1, 1,  0,  -1, 0,  0,  -1, 1,  0,  1,  -1, -1,
    0,  1,  0,  1,  0,  0,  -1, 1,  -1, -1, 1,  0,  -1, -1, 0,  1,  0,  0,  1,
    1,  1,  0,  1,  1,  1,  -1, 1,  1,  -1, 0,  -1, 1,  -1, 1,  1,  1,  1,  1,
    -1, -1, 0,  1,  0,  1,  -1, 1,  1,  -1, -1, -1, 0,  -1, 1,  1,  0,  0,  0,
    0,  0,  1,  0,  -1, -1, -1, 0,  0,  0,  -1, -1, -1, -1, 1,  -1, 0,  -1, 0,
    0,  0,  1,  1,  0,  -1, 1,  1,  -1, 0,  1,  0,  0,  -1, 0,  0,  0,  1,  1,
    0,  1,  -1, 1,  -1, 1,  -1, 0,  1,  1,  -1, -1, -1, -1, 1,  1,  0,  0,  1,
    0,  -1, 0,  0,  1,  0,  0,  0,  0,  1,  1,  -1, 1,  0,  0,  0,  0,  1,  0,
    0,  1,  0,  0,  -1, 0,  1};
static const trit_t trits_in_1[] = (const trit_t[]){
    -1, -1, 0,  0,  -1, 0,  -1, -1, -1, -1, -1, -1, 0,  0,  -1, -1, 0,  -1, 0,
    0,  0,  -1, -1, -1, 0,  0,  -1, 0,  0,  0,  0,  -1, 0,  0,  0,  -1, -1, 0,
    -1, -1, -1, 0,  0,  0,  -1, -1, 0,  -1, 0,  -1, -1, 0,  -1, 0,  -1, -1, -1,
    0,  0,  0,  0,  -1, -1, -1, -1, -1, 0,  0,  -1, -1, -1, -1, 0,  0,  0,  -1,
    0,  -1, 0,  -1, 0,  0,  -1, 0,  0,  -1, -1, 0,  -1, -1, -1, -1, 0,  -1, 0,
    0,  -1, -1, 0,  -1, -1, -1, 0,  -1, 0,  0,  0,  -1, -1, -1, -1, -1, 0,  0,
    -1, -1, -1, -1, -1, 0,  -1, -1, 0,  0,  -1, -1, 0,  0,  0,  0,  -1, -1, 0,
    -1, -1, -1, 0,  -1, 0,  0,  -1, 0,  -1, -1, 0,  0,  -1, -1, -1, -1, 0,  0,
    0,  -1, -1, 0,  0,  -1, 0,  0,  -1, 0,  0,  -1, -1, 0,  -1, -1, 0,  -1, -1,
    -1, 0,  0,  -1, -1, -1, -1, 0,  -1, 0,  0,  0,  -1, -1, -1, 0,  -1, -1, -1,
    0,  0,  -1, 0,  -1, 0,  -1, 0,  0,  -1, 0,  -1, -1, 0,  -1, 0,  -1, -1, 0,
    -1, 0,  0,  0,  -1, -1, -1, -1, -1, 0,  0,  0,  -1, -1, -1, 0,  0,  0,  0,
    0,  -1, 0,  0,  0,  0,  -1, 0,  -1, 0,  0,  -1, 0,  -1, 0,  0,  0,  0,  0,
    0,  -1, -1, -1, 0,  -1, 0,  0,  -1, 0,  -1, -1, 0,  0,  -1, -1, -1, 0,  0,
    0,  0,  0,  0,  0,  -1, 0,  0,  -1, -1, -1, 0,  -1, 0,  -1, -1, -1, -1, 0,
    -1, -1, 0,  -1, 0,  0,  -1, 0,  -1, 0,  0,  -1, -1, -1, -1, 0,  -1, 0,  0,
    -1, 0,  0,  0,  0,  -1, -1, 0,  0,  -1, 0,  -1, -1, 0,  -1, -1, -1, -1, 0,
    -1, -1, 0,  -1, 0,  -1, 0,  0,  -1, 0,  0,  0,  -1, 0,  0,  0,  0,  -1, 0,
    -1, 0,  -1, -1, -1, -1, 0,  -1, -1, 0,  -1, -1, -1, -1, 0,  -1, -1, -1, 0,
    0,  0,  -1, -1, 0,  0,  0,  -1, -1, 0,  0,  -1, 0,  -1, -1, 0,  -1, 0,  0,
    0,  -1, 0,  0,  0,  0,  -1, 0,  0,  -1, 0,  -1, -1, -1, -1, 0,  -1, -1, -1,
    0,  -1, 0,  0,  0,  -1, -1, 0,  0,  -1, 0,  0,  -1, 0,  0,  -1, 0,  -1, -1,
    -1, -1, -1, 0,  -1, 0,  0,  -1, 0,  -1, -1, 0,  -1, -1, -1, -1, 0,  -1, 0,
    0,  -1, -1, -1, 0,  0,  0,  -1, -1, 0,  -1, 0,  0,  -1, 0,  0,  0,  0,  0,
    0,  -1, -1, 0,  -1, -1, -1, 0,  -1, 0,  0,  0,  -1, 0,  0,  -1, 0,  0,  0,
    -1, -1, -1, 0,  -1, 0,  -1, -1, 0,  0,  -1, -1, 0,  0,  -1, 0,  -1, -1, 0,
    -1, -1, 0,  0,  -1, 0,  -1, -1, -1, -1, 0,  -1, 0,  0,  -1, 0,  0,  -1, -1,
    -1, -1, 0,  0,  -1, 0,  -1, 0,  0,  -1, -1, 0,  -1, 0,  0,  0,  0,  0,  0,
    -1, 0,  -1, 0,  -1, -1, 0,  0,  0,  0,  -1, 0,  0,  -1, -1, -1, -1, 0,  0,
    -1, -1, 0,  -1, -1, -1, -1, -1, -1, -1, -1, 0,  -1, 0,  0,  -1, -1, 0,  0,
    0,  0,  -1, 0,  0,  -1, -1, -1, 0,  0,  0,  -1, 0,  -1, 0,  0,  0,  0,  0,
    -1, -1, 0,  -1, 0,  -1, 0,  0,  -1, -1, 0,  0,  0,  -1, -1, 0,  -1, 0,  0,
    0,  0,  -1, -1, -1, 0,  -1, -1, -1, -1, 0,  0,  0,  0,  -1, -1, -1, 0,  -1,
    -1, 0,  0,  -1, 0,  -1, -1, -1, 0,  -1, 0,  0,  0,  0,  0,  0,  0,  0,  0,
    -1, -1, 0,  0,  -1, -1, -1, 0,  0,  -1, -1, 0,  0,  -1, -1, 0,  0,  -1, -1,
    -1, 0,  -1, 0,  -1, 0,  -1, -1, -1, 0,  -1, 0,  -1, -1, -1, 0,  -1, 0,  -1,
    0,  -1, -1, -1, 0,  -1, 0,  0,  0,  0,  -1, -1, -1, -1, 0,  0,  -1, 0,  -1,
    0,  0,  0,  -1, -1, -1, 0,  0,  0,  -1, -1, 0,  0,  0,  0,  -1, -1, 0,  0,
    0,  0,  -1, 0,  0,  0,  -1};
static const trit_t trits_out_1[] = (const trit_t[]){
    0,  -1, 1,  1,  1,  -1, -1, 0,  0,  -1, 1,  0,  0,  1,  -1, 1,  0,  -1, 1,
    0,  0,  -1, -1, -1, 1,  1,  -1, 1,  1,  -1, 1,  -1, -1, 0,  1,  -1, 0,  0,
    0,  -1, 0,  1,  1,  0,  1,  -1, 0,  -1, -1, 1,  0,  1,  0,  -1, -1, 1,  1,
    -1, 1,  0,  -1, -1, 1,  1,  0,  0,  0,  1,  -1, 1,  0,  1,  0,  -1, -1, -1,
    -1, 1,  -1, 1,  -1, -1, -1, 1,  0,  0,  0,  -1, -1, 1,  1,  1,  0,  0,  0,
    0,  0,  -1, 1,  0,  1,  0,  -1, -1, 0,  1,  -1, 0,  -1, 1,  1,  -1, -1, 0,
    0,  0,  1,  1,  0,  -1, 1,  0,  0,  -1, 1,  -1, 1,  0,  1,  -1, 1,  1,  1,
    1,  0,  0,  1,  1,  -1, -1, 1,  -1, 1,  -1, -1, -1, -1, 0,  -1, -1, 0,  0,
    1,  0,  -1, 1,  1,  1,  -1, 1,  0,  0,  0,  0,  1,  0,  -1, 1,  -1, -1, -1,
    -1, -1, -1, 1,  -1, 0,  -1, 1,  0,  1,  0,  0,  -1, 1,  1,  -1, 0,  1,  1,
    0,  0,  -1, 0,  -1, 1,  -1, -1, -1, -1, 0,  -1, -1, 0,  1,  1,  1,  -1, 1,
    -1, 1,  1,  0,  1,  1,  0,  0,  0,  1,  1,  1,  0,  0,  1,  1,  1,  0,  0,
    -1, 0,  1,  0,  1,  -1, -1, 1,  0,  -1, 1,  0,  0,  0,  -1, 0,  -1, -1, 0,
    0,  -1, 0,  0,  0,  0,  0,  0,  -1, 1,  1,  1,  -1, -1, 1,  -1, -1, -1, 1,
    -1, 1,  1,  0,  0,  1,  -1, 0,  -1, -1, 0,  -1, 1,  1,  1,  0,  1,  -1, -1,
    0,  -1, -1, 1,  0,  0,  -1, 0,  0,  1,  1,  -1, 0,  1,  -1, 0,  0,  -1, -1,
    0,  0,  1,  -1, 1,  -1, -1, -1, 0,  0,  -1, -1, -1, 1,  1,  -1, -1, -1, 1,
    0,  -1, -1, 1,  -1, 1,  1,  1,  1,  0,  1,  1,  1,  -1, 1,  1,  -1, 1,  0,
    -1, -1, 1,  0,  0,  0,  1,  1,  0,  0,  0,  0,  1,  0,  -1, -1, -1, 0,  -1,
    1,  1,  0,  1,  -1, -1, -1, -1, 0,  1,  1,  1,  0,  0,  0,  0,  0,  1,  0,
    0,  -1, 1,  0,  0,  1,  1,  1,  -1, 0,  0,  0,  0,  1,  1,  -1, 1,  -1, -1,
    -1, 0,  1,  0,  0,  0,  1,  1,  -1, 0,  0,  0,  1,  1,  1,  -1, 1,  -1, 1,
    1,  -1, 0,  0,  -1, -1, -1, -1, -1, -1, -1, 1,  -1, -1, -1, 1,  1,  0,  -1,
    0,  0,  0,  0,  1,  1,  0,  -1, -1, -1, 0,  -1, -1, -1, -1, -1, -1, 0,  1,
    1,  0,  1,  0,  0,  1,  1,  0,  1,  1,  -1, -1, 1,  0,  0,  1,  1,  -1, 1,
    0,  1,  1,  0,  -1, 1,  -1, 0,  0,  0,  0,  -1, 1,  1,  0,  0,  1,  1,  1,
    0,  -1, 1,  1,  0,  0,  1,  1,  0,  -1, -1, 1,  0,  0,  1,  1,  -1, -1, 0,
    -1, -1, 1,  1,  -1, -1, 1,  -1, -1, 1,  0,  -1, 0,  -1, 0,  0,  1,  0,  0,
    1,  -1, 0,  1,  1,  -1, -1, 0,  -1, -1, 1,  0,  1,  -1, 0,  -1, 0,  1,  0,
    -1, 1,  1,  1,  -1, 0,  1,  -1, -1, -1, 1,  1,  0,  0,  -1, 0,  -1, -1, -1,
    1,  0,  1,  0,  1,  1,  0,  -1, 0,  0,  1,  -1, -1, 0,  1,  0,  -1, -1, -1,
    0,  1,  1,  -1, -1, 1,  -1, 0,  0,  -1, 1,  1,  1,  -1, 1,  -1, 0,  -1, 0,
    1,  -1, 1,  -1, 0,  1,  -1, -1, -1, 1,  0,  -1, 0,  0,  1,  0,  0,  0,  1,
    -1, 1,  1,  -1, -1, -1, 0,  -1, 1,  1,  -1, 1,  1,  0,  1,  -1, 1,  0,  0,
    0,  0,  0,  1,  0,  0,  0,  0,  1,  1,  -1, 0,  0,  0,  -1, 0,  -1, 0,  -1,
    0,  0,  0,  1,  1,  1,  0,  0,  1,  -1, -1, -1, -1, 1,  -1, 0,  -1, -1, 1,
    1,  -1, -1, -1, -1, -1, 1,  0,  0,  0,  0,  1,  1,  0,  1,  -1, -1, -1, -1,
    -1, 0,  -1, -1, 1,  1,  0,  0,  0,  0,  1,  1,  -1, 0,  1,  0,  -1, 0,  0,
    1,  0,  0,  0,  0,  1,  -1};

// static const char trit_hash =
// "BPFFJDLS9CSEZCUXPLDPLDASUL9PTJVFZEBNHRE9TWLUJKNCBYSMXWJYMBYFXRDJUZJDQRIXHRWBY9999";

#define nocl_pd_trans                                                          \
  "99999999999999999999999999999999999999999999999999999999999999999999999999" \
  "99999999999999999999999999999999999999999999999999999999999999999999999999" \
  "99999999999999999999999999999999999999999999999999999999999999999999999999" \
  "99999999999999999999999999999999999999999999999999999999999999999999999999" \
  "99999999999999999999999999999999999999999999999999999999999999999999999999" \
  "99999999999999999999999999999999999999999999999999999999999999999999999999" \
  "99999999999999999999999999999999999999999999999999999999999999999999999999" \
  "99999999999999999999999999999999999999999999999999999999999999999999999999" \
  "99999999999999999999999999999999999999999999999999999999999999999999999999" \
  "99999999999999999999999999999999999999999999999999999999999999999999999999" \
  "99999999999999999999999999999999999999999999999999999999999999999999999999" \
  "99999999999999999999999999999999999999999999999999999999999999999999999999" \
  "99999999999999999999999999999999999999999999999999999999999999999999999999" \
  "99999999999999999999999999999999999999999999999999999999999999999999999999" \
  "99999999999999999999999999999999999999999999999999999999999999999999999999" \
  "99999999999999999999999999999999999999999999999999999999999999999999999999" \
  "99999999999999999999999999999999999999999999999999999999999999999999999999" \
  "99999999999999999999999999999999999999999999999999999999999999999999999999" \
  "99999999999999999999999999999999999999999999999999999999999999999999999999" \
  "99999999999999999999999999999999999999999999999999999999999999999999999999" \
  "99999999999999999999999999999999999999999999999999999999999999999999999999" \
  "99999999999999999999999999999999999999999999999999999999999999999999999999" \
  "99999999999999999999999999999999999999999999999999999999999999999999999999" \
  "99999999999999999999999999999999999999999999999999999999999999999999999999" \
  "99999999999999999999999999999999999999999999999999999999999999999999999999" \
  "99999999999999999999999999999999999999999999999999999999999999999999999999" \
  "99999999999999999999999999999999999999999999999999999999999999999999999999" \
  "99999999999999999999999999999999999999999999999999999999999999999999999999" \
  "99999999999999999999999999999999999999999999999999999999999999999999999999" \
  "99999999999999999999999999999999999999999999999999999999999999999999999999" \
  "99999999999999999999999999999999999999999999999999999999999999999999999999" \
  "99999999999999999999999999999999999999999999999999999999999999999999999999" \
  "99999999999999999999999999999999999999999999999999999999999999999999999999" \
  "99999999999999999999999999999999999999999999999999999999999999999999999999" \
  "99999999999999999999999999999999999999999999999999999999999999999999999999" \
  "99T99999999999999999999999999999999999999999999999999999OLOB99999999999999" \
  "999999999"
#define nocl_pd_hash                                                           \
  "TAQCQAEBHLLYKAZWMNSXUPWQICMFSKWPEGQBNM9AQMGLFZGME9REOZTQIJQRKYHDANIYSMFYPV" \
  "ABX9999"
/*
#define trits_in
"999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999ZDWNRTMICEUJKUZIZGXKNUXGTFQTGNXHYHYYQYLWPPWKRWFVTIOBFGMVLKGCOGHF9LINGNLPHQBO9UHSE999999999999999999999999999999999999999999999999999999CAAUHVD99999999999999999999HRNCLJOVIU999QYHADTTFLUMTDSUAYKUUBWCWACGEPWZQUHQDWSGMFFKNHAIUUVQHPXOTHFFGLUUMYRMKPYHODCQSKTYJBNXYLMDXGTAIDMXNNXZPCJZD9PAXVITTAPLDDDAVZXHVY9QABYMTFGODIGFV9JZFW9999UNBHOV9VMEMRMBPJLEIJLUMXNFTSOMQ9JLNPAKOPIXALNXQHOMNRJPSRJOQYYWWXZJJX9FYOSKB999999TCKFGDZLRGMOMLDTQZOQ9DVUCNWGAXKOWCQDLLGMZAZKYYKIIQBT9XRFIKTMPPOAN9UJYKKBGNSWAZVHJ"
#define hash_out
"CAGIYKAKEMWFOLFPYUFHNWUP9FHQIXPGLDQ9NUTCXQG9YHVKZZSFACQ9HKSFJTCNADLBWSQJWKAGY9999"
*/

int init_suite(void) {
  init_converter();
  return 0;
}
int clean_suite(void) { return 0; }

void test_curl_absorb(void);

void test_curl_absorb(void) {
  trit_t my_trits_1[STATE_LENGTH];

  Curl curl;
  init_curl(&curl);

  int length_1 = STATE_LENGTH;
  memcpy(my_trits_1, trits_in_2, length_1 * sizeof(trit_t));

  for (int i = 0; i < 3; i++) {
    absorb(&curl, my_trits_1, i * HASH_LENGTH, HASH_LENGTH);
  }
  squeeze(&curl, my_trits_1, 0, length_1);
  reset(&curl);
  CU_ASSERT(memcmp(my_trits_1, trits_in_2, STATE_LENGTH * sizeof(trit_t)) != 0);
  CU_ASSERT(memcmp(my_trits_1, trits_out_2, STATE_LENGTH * sizeof(trit_t)) ==
            0);

  length_1 = STATE_LENGTH;
  memcpy(my_trits_1, trits_in_1, length_1 * sizeof(trit_t));
  CU_ASSERT(memcmp(my_trits_1, trits_in_1, STATE_LENGTH * sizeof(trit_t)) == 0);

  absorb(&curl, my_trits_1, HASH_LENGTH, HASH_LENGTH);
  length_1 = STATE_LENGTH;
  squeeze(&curl, my_trits_1, 0, length_1);

  CU_ASSERT(memcmp(my_trits_1, trits_out_1, length_1 * sizeof(trit_t)) == 0);
}

void test_curl_reset() {

  trit_t my_trits_2[length_2];

  Curl curl;
  init_curl(&curl);

  memcpy(my_trits_2, trits_2, length_2 * sizeof(trit_t));

  absorb(&curl, my_trits_2, 0, length_2);
  squeeze(&curl, my_trits_2, 0, length_2);
  CU_ASSERT(memcmp(my_trits_2, expect_2, length_2 * sizeof(trit_t)) == 0);

  reset(&curl);
  memcpy(my_trits_2, trits_2, length_2 * sizeof(trit_t));

  absorb(&curl, my_trits_2, 0, length_2);
  squeeze(&curl, my_trits_2, 0, length_2);
  CU_ASSERT(memcmp(my_trits_2, expect_2, length_2 * sizeof(trit_t)) == 0);
}

void test_curl_noreset_fail() {
  trit_t my_trits_2[length_2];

  Curl curl;
  init_curl(&curl);
  memcpy(my_trits_2, trits_2, length_2 * sizeof(trit_t));
  memcpy(my_trits_2, trits_2, length_2 * sizeof(trit_t));

  absorb(&curl, my_trits_2, 0, length_2);
  squeeze(&curl, my_trits_2, 0, length_2);
  CU_ASSERT(memcmp(my_trits_2, expect_2, length_2 * sizeof(trit_t)) == 0);

  int length = HASH_LENGTH;
  absorb(&curl, my_trits_2, 0, length);
  squeeze(&curl, my_trits_2, 0, length);
  CU_ASSERT_FALSE(memcmp(my_trits_2, expect_2, HASH_LENGTH * sizeof(trit_t)) ==
                  0);
}

void test_curl_hash_works() {
  Curl curl;
  init_curl(&curl);

  trit_t* mytrits = trits_from_trytes(nocl_pd_trans, TRANSACTION_LENGTH / 3);

  trit_t myhash[HASH_LENGTH];

  absorb(&curl, mytrits, 0, TRANSACTION_LENGTH);
  squeeze(&curl, myhash, 0, HASH_LENGTH);
  char* hashtrytes = trytes_from_trits(myhash, 0, HASH_LENGTH);

  CU_ASSERT(strcmp(hashtrytes, nocl_pd_hash) == 0);
  free(hashtrytes);
  free(mytrits);
}

void test_export_hash_trytes(void) {
  CU_ASSERT(strcmp(ccurl_digest_transaction(nocl_pd_trans), nocl_pd_hash) == 0);
}

static CU_TestInfo tests[] = {
    {"Curl Absorb Test", test_curl_absorb},
    {"Curl Reset Test", test_curl_reset},
    {"Curl NoReset Fail Test", test_curl_noreset_fail},
    {"Curl Hash Fail Test", test_curl_hash_works},
    {"Curl export digest test", test_export_hash_trytes},
    CU_TEST_INFO_NULL,
};

static CU_SuiteInfo suites[] = {
    {"suitename1", init_suite, clean_suite, NULL, NULL, tests},
    CU_SUITE_INFO_NULL,
};

int main() { return run_tests(suites); }
