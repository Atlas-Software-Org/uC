#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	printf("Hello, World!\n\r");

	FILE *fp = fopen("Test.txt", "r");

	fseek(fp, 0, SEEK_END);
	size_t size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	char* buffer = (char*)malloc(size);

	fread(buffer, size, 1, fp);

	puts(buffer);

	printf("Hello, %s\n\r", "World");

	return 0;
}
