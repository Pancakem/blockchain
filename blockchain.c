#include "blockchain.h"

Blockchain *make_chain() {
  Blockchain *chain = (Blockchain *)malloc(sizeof(Blockchain));
  chain->difficulty = 1;
  chain->height = 1;
  chain->blocks = (Block **)malloc(sizeof(Block *) * MAX_BLOCKS);
  for (int i = 0; i < MAX_BLOCKS; ++i) {
    chain->blocks[i] = NULL;
  }
  chain->blocks[chain->height - 1] = create_genesis_block();
  return chain;
}

void add_new_block(Blockchain *chain, char *data) {
  chain->blocks[get_last_block(chain)->index + 1] = mine_block(chain, data);
}
int is_chain_valid(Blockchain *chain) {
  int total_length = get_height(chain);
  for (int i = 1; i < total_length; ++i) {
    Block *current_block = chain->blocks[i];
    if (current_block->hash != calculate_hash(current_block)) {
      return 0;
    }

    Block *previous_block = chain->blocks[i - 1];
    if (previous_block->hash != calculate_hash(previous_block)) {
      return 0;
    }
  }
  return 1;
}

Block *get_last_block(Blockchain *chain) {
  return chain->blocks[get_height(chain) - 1];
}

Block *create_genesis_block() {
    return make_block(0, get_timestamp(), "Genesis Block", "Starting chain", 1);
}

int get_height(Blockchain *chain) { return chain->height; }

Block *mine_block(Blockchain *chain, char *data) {
  char *cstr = (char *)malloc(sizeof(char) * chain->difficulty + 1);
  for (int32_t i = 0; i < chain->difficulty; ++i) {
    cstr[i] = '0';
  }
  cstr[chain->difficulty] = '\0';
  Block *previous_block = get_last_block(chain);
  printf("%d", chain->height);
  int32_t nonce = previous_block->nonce;
  Block *new_block = (Block *)malloc(sizeof(Block));
  new_block = make_block(previous_block->index + 1, get_timestamp(), data,
                         previous_block->previous_hash, 0);
  int i = 0;
  do {
    nonce++;
    new_block->hash = calculate_hash(new_block);
    i++;
  } while (i < chain->difficulty);

  chain->difficulty += 9 * difficulty_controller();
  new_block->hash[64] = '\0';
  new_block->nonce = nonce;
  free(cstr);
  chain->height += 1;
  return new_block;
}
