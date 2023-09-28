/*
 * hsl2rgb
 *
 * Convert colour from HSL colourspace to RGB.
 *
 * Luke McCarthy 2023-09-26
 */

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define RGB(r, g, b) (((r) & 0xFF) | (((g) & 0xFF) << 8) | (((b) & 0xFF) << 16))
#define RED(rgb) ((rgb) & 0xFF)
#define GRN(rgb) (((rgb) >> 8) & 0xFF)
#define BLU(rgb) (((rgb) >> 16) & 0xFF)

uint32_t rgb_from_hsl(float hue, float sat, float lig)
{
    float C = (1.0f - fabsf(2.0f * lig - 1.0f)) * sat; // chroma
    float H = hue / 60.0f;
    float X = C * (1.0f - fabsf(fmodf(H, 2.0f) - 1));
    float R, G, B;
    switch ((int)H) {
        default:
        case 0: R = C, G = X, B = 0; break;
        case 1: R = X, G = C, B = 0; break;
        case 2: R = 0, G = C, B = X; break;
        case 3: R = 0, G = X, B = C; break;
        case 4: R = X, G = 0, B = C; break;
        case 5: R = C, G = 0, B = X; break;
    }
    float m = lig - C / 2.0f;
    int r = (R + m) * 255.0f;
    int g = (G + m) * 255.0f;
    int b = (B + m) * 255.0f;
    return RGB(r, g, b);
}

int main(int argc, const char *const *argv)
{
    if (argc != 4) {
        fprintf(stderr, "usage: %s HUE SATURATION LIGHTNESS\n", argv[0]);
        return 1;
    }
    float hue = strtof(argv[1], NULL);
    float sat = strtof(argv[2], NULL);
    float lig = strtof(argv[3], NULL);
    uint32_t rgb = rgb_from_hsl(hue, sat, lig);
    printf("HSL(%.2f, %.2f, %.2f) = RGB(%u, %u, %u)\n", hue, sat, lig, RED(rgb), GRN(rgb), BLU(rgb));
    return 0;
}
