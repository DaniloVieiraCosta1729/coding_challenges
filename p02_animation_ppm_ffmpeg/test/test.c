#include "../header/Dimg.h"

int main()
{
    Context * c = initContext(800, 600);

    Color color = {255, 255, 1};
    clear(c, color);

    Vec2 startRect1 = {200, 50};
    Vec2 sizeRect1 = {300, 300};
    Color colorRect1 = {1, 100, 255};
    drawRect(c, startRect1, sizeRect1, colorRect1);

    Vec2 centerCirc1 = {200, 200};
    int radiusCirc1 = 50;
    Color colorCirc1 = {255, 1, 1};

    drawCircle(c, centerCirc1, radiusCirc1, colorCirc1);

    char * nameFile = "imgTest.ppm";
    paint(nameFile, c);

    destroyContext(c);
}
