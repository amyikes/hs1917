//Amy Diaz
//14th March
//Prints a Danish Flag

#include <stdio.h>
#include <stdlib.h>

void showDanish ( void ) {
    int lineNumber = 1;
    int lines = 5;

    while (lineNumber != lines) {
        //I was not completely sure of what I was doing, and I had some trouble with while loops. Hopefully this is correct!!
        while (lineNumber <= 2) {
            printf("** ********* \n");
            lineNumber = lineNumber + 1;
        } 
        printf("\n");
        while (lineNumber <= 4) {
            printf("** ********* \n");
            lineNumber = lineNumber + 1;
        }
    return;
    }
}
                

int main() {
    showDanish();
    printf("yay");
    return 0;
}
