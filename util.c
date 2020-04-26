#include "util.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

char *concat(const char *s1, const char *s2) {
  char *result = malloc(sizeof(char) * strlen(s1) + strlen(s2) +
                        1); // +1 for the null-terminator
  strcpy(result, s1);
  result[strlen(result) - 1] = '\0';
  strcat(result, s2);
  return result;
}

void sha256(const char *data, char *result) {
  BYTE *hash = (BYTE*)malloc(sizeof(BYTE)*64);
  SHA256_CTX *ctx = (SHA256_CTX *)malloc(sizeof(SHA256_CTX));
  sha256_init(ctx);
  sha256_update(ctx, (BYTE *)data, sizeof(data) / sizeof(char));
  sha256_final(ctx, hash);
  free(ctx);
  sprintf(result, "%s", (char*)hash);
}

time_t *get_timestamp() {
  time_t *now = (time_t *)malloc(sizeof(time_t));
  *now = time(NULL);
  return now;
}

char *substr(char *src, int n) {
  char *substr = malloc(sizeof(char) * n + 1);
  strncpy(substr, src + strlen(substr), n);
  substr[n] = '\0';
  return substr;
}

int difficulty_controller() {
    int r =  rand();
    return r % 1000;
}
