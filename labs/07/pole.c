#include <stdio.h>
#include <math.h>

/*
https://www.matesfacil.com/ESO/geometria_plana/trigonometria/
    problemas-resueltos-trigonometria-secundaria-seno-coseno-triangulo-angulo.html
*/

int main(){

    int a = 20;
    int angle  = 30;
    int price = 12;
    double h = 0;

    h = a/sin((angle * M_PI)/180);

    double money = h * price;

    printf("%.2f\n",money);

    return 0;
}
