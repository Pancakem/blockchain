#include "blockchain.h"

const char add[] = "add";
const char quit[] = "quit";
const char height[] = "height";
const char verify[] = "verify";
const char help[] = "help";

void log_create(Blockchain *chain) {
  Block *current = get_last_block(chain);
  printf("\nNew block at: %s\n", current->hash);
  printf("Block index is: %d\n", current->index);
  printf("Timestamp is: %s\n", ctime(current->timestamp));
  printf("Data is: %s\n", current->data);
  printf("Current difficulty is: %d", chain->difficulty);
}

char *readline(char *prompt) {
  char buffer[2048];
  fputs(prompt, stdout);
  fgets(buffer, 2048, stdin);
  char *cpy = malloc(strlen(buffer) + 1);
  strcpy(cpy, buffer);
  cpy[strlen(cpy) - 1] = '\0';
  return cpy;
}

void repl() {
  char *line = NULL;
  Blockchain *chain = (Blockchain *)malloc(sizeof(Blockchain));
  chain = make_chain();
  printf("\nGenesis block at: %s", get_last_block(chain)->hash);
  while (1) {
    line = readline("\nchain-repl> ");
    if (!line) {
      fprintf(stderr, "\nEOF in repl (%s:%d)\n", __FILE__, __LINE__);
      return;
    }

    if (!(strcmp(line, add) != 0)) {
      add_new_block(chain, "Hey");
      log_create(chain);
    } else if (!(strcmp(line, verify) != 0)) {
      if (is_chain_valid(chain)) {
        printf("\nChain is valid");
      } else {
        printf("\nChain not valid.");
      }

    } else if (!(strcmp(line, height) != 0)) {
      printf("\nChain height :%d", chain->height);
    } else if (!(strcmp(line, help) != 0)) {
      printf("\nchain v1.0.0");
      printf("\nhelp: show all supported commands");
      printf("\nheight: find out blockchain height");
      printf("\nverify: verifies blockchain");
      printf("\nadd: add a new block to the chain");
      printf("\nquit: exits program");
    } else if (!(strcmp(line, quit) != 0)) {
      if (chain == NULL) {
        printf("\nExiting.");
        exit(0);
      }
      // clean up
      for (int i = 0; i < get_height(chain); ++i) {
        free(chain->blocks[i]->data);
        free(chain->blocks[i]->timestamp);
        free(chain->blocks[i]->hash);
        free(chain->blocks[i]->previous_hash);
        free(chain->blocks[i]);
      }
      for (int i = get_height(chain)-1; i < MAX_BLOCKS; ++i) {
        free(chain->blocks[i]);
      }
      free(chain);
      printf("\nExiting.");
      exit(0);
    } else {
      if (line == NULL) {
        continue;
      }
      printf("\nCommand not recognized.");
    }

    free(line);
  }
}

int main() {
  srand(time(NULL));
  printf("Chain v1.0.0\nIs a simple blockchain implementation.");
  repl();
}
