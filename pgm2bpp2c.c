/*
 * pgm2bpp2c
 *
 * Converts a 2bpp PGM format image to C source code array.
 * 
 * Luke McCarthy 2023-09-27
 */

#include <stdint.h>
#include <stdio.h>

int main(int argc, char *const *const argv)
{
    if (argc != 3) {
        fprintf(stderr, "usage: %s FILENAME ARRAYNAME\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    // Read PGM header
    char magic[3];
    int width, height, maxval;
    if (fscanf(file, "%2s %d %d %d", magic, &width, &height, &maxval) != 4) {
        fputs("Invalid PGM format\n", stderr);
        goto fail;
    }
    if (magic[0] != 'P' || magic[1] != '2') {
        fputs("Invalid PGM header magic\n", stderr);
        goto fail;
    }
    if (maxval > 3) {
        fputs("Maximum grayscale value must be 3 or less\n", stderr);
        goto fail;
    }
    if (width % 4 != 0) {
        fputs("Width of image must be a multiple of 4\n", stderr);
        goto fail;
    }

    int num_bytes = (width * height) / 4;

    // Read image data
    printf("static const unsigned char %s[%d] = {", argv[2], num_bytes);
    for (int i = 0; i < num_bytes; i++) {
        uint8_t byte = 0;
        //Read 4 2-bit pixels and pack in to a byte
        for (int j = 0; j < 4; j++) {
            int pixel;
            if (fscanf(file, "%d", &pixel) != 1) {
                fputs("Unexpected end of data\n", stderr);
                goto fail;
            }
            if (pixel > maxval) {
                fprintf(stderr, "Invalid pixel value %d\n", pixel);
                goto fail;
            }
            byte |= (pixel & 0x3) << (6 - 2 * j);
        }
        printf("0x%02X", byte);
        if (i < num_bytes - 1) {
            putchar(',');
        }
    }
    puts("};");

    fclose(file);
    return 0;
fail:
    fclose(file);
    return 1;
}
