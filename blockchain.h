#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "block.h"
#include <stdlib.h>

#define MAX_BLOCKS 20

typedef struct {
  Block **blocks;
  uint32_t difficulty;
  int height;

} Blockchain;

Blockchain *make_chain();
void add_new_block(Blockchain *chain, char *data);
int is_chain_valid(Blockchain *chain);
Block *get_last_block(Blockchain *chain);
Block *create_genesis_block();
int get_height(Blockchain *chain);
Block *mine_block(Blockchain *chain, char *data);

#endif
