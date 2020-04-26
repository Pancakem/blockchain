#ifndef UTIL_H
#define UTIL_H

#include "include/sha256.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

char *concat(const char *s1, const char *s2);
void sha256(const char *data, char *result);
time_t *get_timestamp();
char *substr(char *src, int n);
int difficulty_controller();

#endif
