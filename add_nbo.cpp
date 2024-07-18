#include <stdio.h>
#include <stdint.h>

FILE *open_and_check_size(const char *filename, long expected_size) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        fprintf(stderr, "Cannot open %s\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    if (size != expected_size) {
        fprintf(stderr, "The size of %s is not %ld bytes\n", filename, expected_size);
        fclose(file);
        return NULL;
    }

    return file;
}

uint32_t ntohl(uint32_t net) {
    uint8_t data[4] = {};
    data[0] = (net >> 24) & 0xFF;
    data[1] = (net >> 16) & 0xFF;
    data[2] = (net >> 8) & 0xFF;
    data[3] = net & 0xFF;
    return ((uint32_t)data[3] << 24) | ((uint32_t)data[2] << 16) | ((uint32_t)data[1] << 8) | data[0];
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <file1> <file2>\n", argv[0]);
        return 1;
    }

    FILE *file1, *file2;
    uint32_t num1, num2, sum;

    file1 = open_and_check_size(argv[1], 4);
    if (file1 == NULL) {
        return 1;
    }

    file2 = open_and_check_size(argv[2], 4);
    if (file2 == NULL) {
        fclose(file1);
        return 1;
    }

    fread(&num1, sizeof(num1), 1, file1);
    fread(&num2, sizeof(num2), 1, file2);

    fclose(file1);
    fclose(file2);

    num1 = ntohl(num1);
    num2 = ntohl(num2);

    sum = num1 + num2;

    printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", num1, num1, num2, num2, sum, sum);

    return 0;
}
