//Amy Diaz
//13th March
//swaps two numbers, x and y

#include <stdio.h>
#include <stdlib.h>

void swap(int *first, int *second);

int main(int argc, char *argv[]) {
    //change int values to swap different numbers
    int x = 3;
    int y = 4;
    swap(&x, &y);
    printf("%d %d \n", x, y);
    return EXIT_SUCCESS;
}

void swap(int *first, int *second){
    int x;
    x = *first;
    *first = *second;
    *second = x;
}
