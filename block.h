#ifndef BLOCK_H
#define BLOCK_H

#include "util.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {

  uint32_t index;
  char *previous_hash;
  time_t *timestamp;
  char *data;
  char *hash;
  int32_t nonce;
} Block;

Block *make_block(uint32_t index, time_t *timestamp, const char *data,
                  const char *previous_hash, int32_t nonce);
char *calculate_hash(Block *block);
#endif
