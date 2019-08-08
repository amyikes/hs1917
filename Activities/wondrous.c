//Amy Diaz
//12th March
//wondrous function

#include <stdio.h>
#include <stdlib.h>

int printWondrous (int num) {   
    int number = num;
    int len = 0;
    while (num > 1) {
        if (num % 2 == 0) {
            num = num/2;
            printf("%d ", num);  
            len++;
            if (len >= 20) {
                return len;
            }
        } else {
            num = (num*3) + 1;
            printf("%d ", num);
            len++;
            if (len >= 20) {
                return len;
            }
        }
        num = number;
        number++;
    }
    printf("\n");
        len = 0;
    int hm = 1;
    return hm;
}

int main () {
    int num;
    num = 2;
    int length = printWondrous(num);
    printf("%d",length);
    return EXIT_SUCCESS;
}

