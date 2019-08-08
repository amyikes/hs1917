/*
 *  doomsday.c
 *  A program to test a function dayOfWeek which determines which
 *  day of the week a particular date falls on.
 *  (only for dates after the start of the Gregorian calendar).
 *
 *  Program stub created by Richard Buckland on 17/03/14
 *  This program by Amy Diaz
 *  Freely licensed under Creative Commons CC-BY-3.0
 *
 *
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
 
#define THURSDAY 0
#define FRIDAY   1
#define SATURDAY 2
#define SUNDAY   3
#define MONDAY   4
#define TUESDAY  5
#define WEDNESDAY 6
 
#define TRUE 1
#define FALSE 0
#define DAYS_PER_WEEK 7

#define JAN 1
#define FEB 2
#define MAR 3
#define APR 4
#define MAY 5
#define JUN 6
#define JUL 7
#define AUG 8
#define SEP 9
#define OCT 10
#define NOV 11
#define DEC 12

#define DOOM_APR 4
#define DOOM_JUN 6
#define DOOM_AUG 1
#define DOOM_OCT 3
#define DOOM_DEC 5

#define DOOM_MAR 0
#define DOOM_MAY 2
#define DOOM_JUL 4
#define DOOM_SEP 5
#define DOOM_NOV 0
 
#define DOOM_FEB 0
#define LEAP_DOOM_FEB 1
#define DOOM_JAN 3
#define LEAP_DOOM_JAN 4

int dayOfWeek (int doomsday, int leapYear, int month, int day);
 
int main (int argc, char *argv[]) {
    assert (dayOfWeek (THURSDAY,  FALSE,  4,  4) == THURSDAY);
    assert (dayOfWeek (FRIDAY,     FALSE,  6,  6) == FRIDAY);
    assert (dayOfWeek (MONDAY,     FALSE,  8,  8) == MONDAY);
    assert (dayOfWeek (WEDNESDAY, FALSE, 10, 10) == WEDNESDAY);
    assert (dayOfWeek (FRIDAY,     FALSE, 12, 12) == FRIDAY);
    assert (dayOfWeek (THURSDAY,  FALSE,  9,  5) == THURSDAY);
    assert (dayOfWeek (FRIDAY,     FALSE,  5,  9) == FRIDAY);
    assert (dayOfWeek (SUNDAY,     FALSE,  7, 11) == SUNDAY);
    assert (dayOfWeek (TUESDAY,    FALSE, 11,  7) == TUESDAY);
    assert (dayOfWeek (WEDNESDAY, FALSE,  3,  7) == WEDNESDAY);

    assert (dayOfWeek (THURSDAY, FALSE, 11, 21) == THURSDAY);   //some random days
    assert (dayOfWeek (TUESDAY, FALSE, 9, 12) == TUESDAY);      //
    assert (dayOfWeek (SUNDAY, FALSE, 7, 25) == SUNDAY);        //
    assert (dayOfWeek (FRIDAY, FALSE, 5, 23) == FRIDAY);        //my bday
    
    assert (dayOfWeek (THURSDAY,  FALSE,  4,  5) == FRIDAY);
    assert (dayOfWeek (SATURDAY,  FALSE,  6,  5) == FRIDAY);
    assert (dayOfWeek (MONDAY,    FALSE,  8,  9) == TUESDAY);
    assert (dayOfWeek (WEDNESDAY, FALSE, 10,  9) == TUESDAY);
    assert (dayOfWeek (FRIDAY,    FALSE, 12, 20) == SATURDAY);
    assert (dayOfWeek (FRIDAY,    FALSE,  5,  5) == MONDAY);
    assert (dayOfWeek (THURSDAY,  FALSE,  3, 30) == SATURDAY);
 
    assert (dayOfWeek (TUESDAY,    FALSE,  2,  28) == TUESDAY);
    assert (dayOfWeek (THURSDAY,  FALSE,  1,  3)  == THURSDAY);

    printf ("all tests passed - You are awesome!\n");
    return EXIT_SUCCESS;
}

// given the doomsday for a year, and whether or not it is a
// leap year, this function return the day of the week for any
// given month and day in the year.
 
int dayOfWeek (int doomsday, int leapYear, int month, int day) {
    int dayOfWeek;
    int x = 0;
        if (month >= MAR && month % 2 == 0) {

            if (month == APR) {                 //april - 4
                if (day % 7 == DOOM_APR) {
                    dayOfWeek = doomsday;
                } 
                while (x <= 6) {                    
                    if (day % 7 == DOOM_APR + x) {
                    dayOfWeek = doomsday + x;
                          
                    }
                    x = x + 1;
                }
            }
            if (month == JUN) {                 //june - 6
                if (day % 7 == DOOM_JUN) {
                    dayOfWeek = doomsday;
                } 
                else {
                    while (x <= 6) {                    
                        if (day % 7 == DOOM_JUN + x) {
                        dayOfWeek = doomsday + x;  
                        }
                        x = x + 1;
                    }
                }
            }
            if (month == AUG) {                //august - 8
                if (day % 7 == DOOM_AUG) {
                    dayOfWeek = doomsday;
                } 
                else {
                    while (x <= 6) {                    
                        if (day % 7 == DOOM_AUG + x) {
                        dayOfWeek = doomsday + x;  
                        }
                        x = x + 1;
                    }
                }
            }
            if (month == OCT) {               //october - 10
                if (day % 7 == DOOM_OCT) {
                    dayOfWeek = doomsday;
                } 
                else {
                    while (x <= 6) {                    
                        if (day % 7 == DOOM_OCT + x) {
                        dayOfWeek = doomsday + x;  
                        }
                        x = x + 1;
                    }
                }
            }
            if (month == DEC) {             //december - 12
                if (day % 7 == DOOM_DEC) {
                    dayOfWeek = doomsday;
                } 
                else {
                    while (x <= 6) {                    
                        if (day % 7 == DOOM_DEC + x) {
                        dayOfWeek = doomsday + x;  
                        }
                        x = x + 1;
                    }
                }
            }
        } else if (month >= MAR && month % 2 != 0) {

            if (month == MAR) {             //march - 3
                if (day % 7 == DOOM_MAR) {
                    dayOfWeek = doomsday;
                }
                else {
                    while (x <= 6) {                    
                        if (day % 7 == DOOM_MAR + x) {
                        dayOfWeek = doomsday + x;  
                        }
                        x = x + 1;
                    }
                }  
            }
            if (month == MAY) {             //may - 5
                if (day % 7 == DOOM_MAY) {
                    dayOfWeek = doomsday;
                }  
                else {
                    while (x <= 6) {                    
                        if (day % 7 == DOOM_MAY + x) {
                        dayOfWeek = doomsday + x;  
                        }
                        x = x + 1;
                    }
                }
            } 
            if (month == JUL) {         //july - 7
                if (day % 7 == DOOM_JUL) {
                    dayOfWeek = doomsday;
                } else {
                    while (x <= 6) {                    
                        if (day % 7 == DOOM_JUL + x) {
                        dayOfWeek = doomsday + x;  
                        }
                        x = x + 1;
                    }
                }
            }
            if (month == SEP) {         //september - 9
                if (day % 7 == DOOM_SEP) {
                    dayOfWeek = doomsday;
                } else {
                    while (x <= 6) {                    
                        if (day % 7 == DOOM_SEP + x) {
                        dayOfWeek = doomsday + x;  
                        }
                        x = x + 1;
                    }
                }
            }
            if (month == NOV) {         //november - 11
                if (day % 7 == DOOM_NOV) {
                    dayOfWeek = doomsday;
                } else {
                    while (x <= 6) {                    
                        if (day % 7 == DOOM_NOV + x) {
                        dayOfWeek = doomsday + x;  
                        }
                        x = x + 1;
                    }
                }
            }
        } else if (leapYear == FALSE) {
            if (month == FEB) {
                if (day % 7 == DOOM_FEB) {
                    dayOfWeek = doomsday;
                } else {
                    while (x <= 6) {                    
                        if (day % 7 == DOOM_FEB + x) {
                        dayOfWeek = doomsday - x;  
                        }
                        x = x + 1;
                    }
    
                }
            }
            if (month == JAN) {
                if (day % 7 == DOOM_JAN) {
                    dayOfWeek = doomsday;
                } else {
                    while (x <= 6) {                    
                        if (day % 7 == DOOM_JAN + x) {
                        dayOfWeek = doomsday + x;  
                        }
                        x = x + 1;
                    }
                }
            }
        } else if (leapYear == TRUE) {
            if (month == FEB) {
                if (day % 7 == LEAP_DOOM_FEB) {
                    dayOfWeek = doomsday;
                } else {
                    while (x <= 6) {                    
                        if (day % 7 == LEAP_DOOM_FEB + x) {
                        dayOfWeek = doomsday + x;  
                        }
                        x = x + 1;
                    }
                }
            } if (month == JAN) {
                if (day % 7 == LEAP_DOOM_JAN) {
                    dayOfWeek = doomsday;
                } else {
                    while (x <= 6) {                    
                        if (day % 7 == LEAP_DOOM_JAN + x) {
                        dayOfWeek = doomsday + x;  
                        }
                        x = x + 1;
                    }
                }
            }
        }
    return dayOfWeek;
}
