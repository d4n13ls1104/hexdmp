#include <stdio.h>

#define BUFFER_SIZE 16

void print_chunk(unsigned char* buffer, size_t file_len) {
	size_t i;
	for (i = 0; i < BUFFER_SIZE; i++) {
		if (i < file_len) {
			printf("%02X ", buffer[i]);
		} else { printf("  "); }

		if (i == 7) { printf(" "); }
	}
}

void print_dump(FILE* file) {
	unsigned char buffer[BUFFER_SIZE];
	size_t addr = 0;

	while (!feof(file)) {
		size_t bytes_read = fread(buffer, 1, BUFFER_SIZE, file);

		printf("%08zX: ", addr);
		print_chunk(buffer, bytes_read);

		addr += BUFFER_SIZE;
		printf("\n");
	}
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Usage: hexdmp <file>\n");
		return 1;
	}

	const char* file_name = argv[1];
	FILE* file = fopen(file_name, "rb");
	if (!file) {
		fprintf(stderr, "Failed to open file: %s\n", file_name);
		return 1;
	}

	print_dump(file);

	fclose(file);
	return 0;
}