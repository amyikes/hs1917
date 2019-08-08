#include <stdio.h>
#include <stdlib.h>

int getlittle (int one, int two, int three) {
    if(one <= two) {
        if(one <= three) {
            return one;
        }
    }
    if(two <= one) {
        if(two <= three) {
            return two;
        }
    }
    return three;
}

int getbig (int one, int two, int three) {
    if(one >= two) {
        if(one >= three) {
            return one;
        }
    }
    if(two >= one) {
        if(two >= three) {
            return two;
        }
    }
    return three;
}

int getmiddle(int one, int two, int three) {
    if(one >= two) {
        if(one <= three) {
            return one;
        }
    }
    if(two >= one) {
        if(two <= three){
            return two;
        }
    }
    if(one >= three) {
        if(one <= two) {
            return one;
        }
    }
    if(two >= three) {
        if(two <= one){
            return two;
        }
    }
    return three;
}

int main () {
    int one, two, three;
    scanf ("%d %d %d", &one, &two, &three);
    int little = getlittle(one, two, three);
    int middle = getmiddle(one, two, three);
    int big = getbig(one, two, three);
    printf("%d \n", little);
    printf("%d \n", middle);
    printf("%d \n", big);
    return EXIT_SUCCESS;
}
