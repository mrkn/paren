#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef uintptr_t sexp_value_t;

#define SEXP_SPECIAL_VALUE_BITS 2
#define SEXP_SPECIAL_VALUE_MASK (1<<SEXP_SPECIAL_VALUE_BITS - 1)
#define SEXP_SPECIAL_P(sexp) ((((sexp_value_t)(sexp)) & SEXP_SPECIAL_VALUE_MASK) != 0)

enum sexp_special_values {
  SEXP_FALSE   = 0,
  SEXP_TRUE    = 1,
  SEXP_NIL     = 2,

  SEXP_UNKNOWN = (sexp_value_t)-1,
};

typedef struct sexp {
} sexp_t;

static char const *input_file = NULL;

static void
process_command_line(int argc, char** argv)
{
  if (argc < 2) {
    fprintf(stderr, "paren INPUT_FILE\n");
    exit(1);
  }

  input_file = argv[1];
}

static sexp_value_t
load(FILE *fp)
{
  sexp_value_t result = SEXP_UNKNOWN;
  int c;

  while (feof(fp) == 0) {
    c = fgetc(fp);
    switch (c) {
      case '(':
        c = fgetc(fp);
        if (c == ')') {
          result = SEXP_NIL;
        }
        else {
          ungetc(c, fp);
        }
        break;
      default:
        break;
    }
  }

  return result;
}

static sexp_value_t
load_file(char const *filename)
{
  sexp_value_t result;
  FILE *fp;

  if (strncmp("-", filename, 1) == 0) {
    fp = stdin;
  }
  else {
    fp = fopen(filename, "rb");
  }

  result = load(fp);

  if (fp != stdin) {
    fclose(fp);
  }

  return result;
}

int
main(int argc, char** argv)
{
  sexp_value_t result;

  process_command_line(argc, argv);

  result = load_file(input_file);

  switch (result) {
    case SEXP_FALSE:
      printf("#f\n");
      break;
    case SEXP_TRUE:
      printf("#t\n");
      break;
    case SEXP_NIL:
      printf("()\n");
      break;
    default:
      printf("ERROR\n");
      break;
  }

  return 0;
}
