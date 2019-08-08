//Amy Diaz
//Asks for a year, then determines if it is or isn't a leap year

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define CALENDAR_START 1582

int isLeapYear (int year) {
    assert (year >= CALENDAR_START);
    if((year % 4) == 0) {
        if (year % 400 == 0) {
            return 1;
        } else if (year % 100 == 0) {
            return 0;
        } else {
            return 1;
        }
    } else {
        return 0;
    }
}

int main ( void ) {
    int year;
    printf("please enter the year you are interested in:\n");
    scanf("%d", &year);
    int isLeap = isLeapYear(year);
    if(isLeap == 1) {
        printf("Is a leap year!\n");
    } 
    else {
        printf("Is not a leap year!\n");
    }
    return EXIT_SUCCESS;
}


