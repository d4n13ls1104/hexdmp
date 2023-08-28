#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 16

void
print_chunk (char *buffer, size_t file_size)
{
	size_t i; for (i = 0; i < BUFFER_SIZE; i++)
	{
		if (i < file_size) printf("%02X ", buffer[i]);
		if (i == 7) printf(" ");
	}
}

void
print_dump (FILE *file)
{
	char *buffer = malloc(BUFFER_SIZE);
	if (!buffer)
	{
		fprintf(stderr, "Failed to allocate memory for file.");
		exit(EXIT_FAILURE);
	}

	size_t addr = 0;
	while (!feof(file))
	{
		size_t bytes_read = fread(buffer, 1, BUFFER_SIZE, file);
		printf("%08zX: ", addr);
		print_chunk(buffer, bytes_read);

		addr += BUFFER_SIZE;
		printf("\n");
	}
}

int
main (int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <file>", argv[0]);
		exit(EXIT_FAILURE);
	}

	FILE *file = fopen(argv[1], "rb");
	if (!file)
	{
		fprintf(stderr, "Failed to open file: %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	print_dump(file);

	fclose(file);
	return 0;
}
