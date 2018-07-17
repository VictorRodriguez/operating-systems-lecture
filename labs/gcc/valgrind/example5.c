#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main() {
  char *path = calloc(BUFSIZ, 1);
  strcat(path, getenv("HOME"));
  strcat(path, "/.bashrc");
  FILE *foo = fopen(path, "r");
  return foo == NULL;
}
