#include "block.h"

char *calculate_hash(Block *block) {
  char *result = (char *)malloc(sizeof(char) * 100);
  result = concat(block->data, block->previous_hash);
  result = concat(result, ctime(block->timestamp));
  char *index_str = (char *)malloc(sizeof(char) * 50);
  sprintf(index_str, "%u", block->index);
  result = concat(result, index_str);
  index_str = (char *)malloc(50 * sizeof(char));
  sprintf(index_str, "%d", block->nonce);
  result = concat(result, index_str);
  char *hash = (char *)malloc(sizeof(char) * 64);
  sha256(result, hash);
  free(index_str);
  free(result);
  return hash;
}

Block *make_block(uint32_t index, time_t *timestamp, const char *data,
                  const char *previous_hash, int32_t nonce) {
  Block *a = (Block *)malloc(sizeof(Block));
  a->nonce = nonce;
  a->index = index;
  a->timestamp = (time_t *)malloc(sizeof(time_t));
  a->timestamp = timestamp;
  a->data = (char *)malloc(sizeof(char) * strlen(data) + 1);
  strcpy(a->data, data);
  a->data[strlen(data)] = '\0';
  a->previous_hash = (char *)malloc(sizeof(char) * strlen(previous_hash) + 1);
  strcpy(a->previous_hash, previous_hash);
  a->previous_hash[strlen(previous_hash)] = '\0';
  a->hash = calculate_hash(a);
  return a;
}
