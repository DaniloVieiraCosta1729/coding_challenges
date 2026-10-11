#include <stdio.h>
#include <stdint.h>

typedef struct {uint8_t r, g, b;} Color;

void paint(const char * name, int width, int height, uint8_t buffer);
void clearBG(FILE * f, const Color color, const int w, const int h);
void drawRec(Color * buffer, const Color color, const int w, const int h);

int main(int c, char * argv[])
{
    char * name = "output.ppm";
    FILE * outputFile = fopen(name, "wb");

    Color bg = {200, 20, 100};
    int width = 700;
    int height = 400;

    fprintf(outputFile,"P6\n%d %d\n255\n", width, height);   

    Color newSquare = {50, 100, 200};

    clearBG(outputFile, bg, width, height);

    fclose(outputFile);

    printf("%s created!\n", name);

    return 0;
}

void clearBG(FILE * f, const Color color, const int w, const int h)
{
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            fputc(color.r, f);
            fputc(color.g, f);
            fputc(color.b, f);
        }
    }
}

void drawRec(Color * buffer, const Color color, const int w, const int h)
{
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            buffer[i * h + j] = color;
        }
    }
}

void paint(const char * name, int width, int height, uint8_t buffer)
{
    FILE * f = fopen(name, "wb");
    fprintf(f, "P6\n%d %d\n255\n", width, height);

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            fputc(buffer[i * width + j], f);
        }
    }

    fclose(f);
}
