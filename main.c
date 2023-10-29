#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 16

void
print_chunk (char *buf, size_t fsize)
{
  size_t i;
  for (i = 0; i < BUF_SIZE; i++)
    {
      if (i < fsize)
        printf ("%02X ", buf[i]);
      if (i == 7)
        printf (" ");
    }
}

void
print_dump (FILE *f)
{
  char *buf = calloc (BUF_SIZE, sizeof (char));
  if (!buf)
    errx (EXIT_FAILURE, "failed malloc");
  size_t addr = 0;
  while (!feof (f))
    {
      printf ("%08zX: ", addr);
      size_t bytes_read = fread (buf, 1, BUF_SIZE, f);
      print_chunk (buf, bytes_read);
      addr += BUF_SIZE;
      printf ("\n");
    }
}

int
main (int argc, char *argv[])
{
  if (argc != 2)
    errx (EXIT_FAILURE, "usage: %s <file>", argv[0]);
  FILE *f = fopen (argv[1], "rb");
  if (!f)
    errx (EXIT_FAILURE, "failed to open file: %s\n", argv[1]);
  print_dump (f);
  fclose (f);
  return 0;
}