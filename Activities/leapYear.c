//Amy Diaz
//Asks for a year, then determines if it is or isn't a leap year

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define CALENDAR_START 1582

int main ( void ) {
    int year;
    int isLeap;
    printf("please enter the year you are interested in:\n");
    scanf("%d", &year);
    
    assert (year >= CALENDAR_START);
    if((year % 4) == 0) {
        if (year % 400 == 0) {
            isLeap = 1;
        } else if (year % 100 == 0) {
            isLeap = 0;
        } else {
            isLeap = 1;
        }
    } else {
        isLeap = 0;
    }


    if(isLeap == 1) {
        printf("Is a leap year!\n");
    } 
    else {
        printf("Is not a leap year!\n");
    }
    return EXIT_SUCCESS;
}


