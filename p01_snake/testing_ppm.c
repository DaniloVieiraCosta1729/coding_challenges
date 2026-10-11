#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {uint8_t r, g, b;} Color;
typedef struct
{
    int width;
    int height;
    Color * buffer;
} Context;

Context * initializeContext(int width, int height);
void destroyContext(Context * c);
void paint(const char * name, int width, int height, Color * buffer);
void clearBG(FILE * f, const Color color, const int w, const int h);
void drawRec(Color * buffer, const Color color, const int w, const int h);
void esmeraldaFunction(Context * c, char colorType);

int main(int c, char * argv[])
{
    if(c != 6)
    {
        printf("usage: %s <width> <height> <red0-255> <green> <blue>\n", argv[0]);
        return -1;
    }

    int w, h;
    uint8_t r, g, b;

    if((w = atoi(argv[1])) < 1)
    {
        printf("All values need to be positive.\n");
        return -1;
    }

    if((h = atoi(argv[2])) < 1)
    {
        printf("All values need to be positive.\n");
        return -1;
    }


    if(((r = atoi(argv[3])) < 1) || (r > 255))
    {
        printf("The range for r is 1 to 255 \"Normally, for rgb, 0 would be included, but not here.\"\n");
        return -1;
    }
    
    if(((g = atoi(argv[4])) < 1) || (r > 255))
    {
        printf("The range for r is 1 to 255 \"Normally, for rgb, 0 would be included, but not here.\"\n");
        return -1;
    }
    if(((b = atoi(argv[5])) < 1) || (r > 255))
    {
        printf("The range for r is 1 to 255 \"Normally, for rgb, 0 would be included, but not here.\"\n");
        return -1;
    }

    char * name = "output.ppm";

    Color * buffer = malloc(w*h * sizeof(Color));
    Color bg = {r, g, b};
    drawRec(buffer, bg, w, h);
    paint(name, w, h, buffer);

    Context * primeiroContexto = initializeContext(800, 800);
    esmeraldaFunction(primeiroContexto, 'r');

    char * test = "Eteste.ppm";

    paint(test, primeiroContexto->width, primeiroContexto->height, primeiroContexto->buffer);

    destroyContext(primeiroContexto);

    printf("%s created!\n", name);
    printf("%s created!\n",test);

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

void paint(const char * name, int width, int height, Color * buffer)
{
    FILE * f = fopen(name, "wb");
    fprintf(f, "P6\n%d %d\n255\n", width, height);

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            fputc(buffer[i * width + j].r, f);
            fputc(buffer[i * width + j].g, f);
            fputc(buffer[i * width + j].b, f); 
        }
    }

    fclose(f);
}

Context * initializeContext(int width, int height)
{
    Color * buf = malloc(width * height * sizeof(Color));
    if(buf == NULL)
    {
        perror("malloc");
        return NULL;
    }
    
    Context * context = malloc(sizeof(Context));
    if(context == NULL)
    {
        perror("malloc");
        return NULL;
    }

    context->width = width;
    context->height = height;
    context->buffer = buf;

    return context;
}

void destroyContext(Context * c)
{
    free(c->buffer);
    free(c);
}

void esmeraldaFunction(Context * c, char colorType)
{
    int w = c->width;
    int h = c->height;
    Color * b = c->buffer;

    switch (colorType)
    {
        case 'r':
        case 'R':
            for(int i = 0; i < h; i++)
            {
                for(int j = 0; j < w; j++)
                {
                    b[i * w + j].r = (i * w + j) % 255;
                }
            }
            break;
        
        case 'g':
        case 'G':
            for(int i = 0; i < h; i++)
            {
                for(int j = 0; j < w; j++)
                {
                    b[i * w + j].g = (i * w + j) % 255;
                }
            }

        case 'b':
        case 'B':
            for(int i = 0; i < h; i++)
            {
                for(int j = 0; j < w; j++)
                {
                    b[i * w + j].b = (i * w + j) % 255;
                }
            }

        default:
            break;
    }   
}
