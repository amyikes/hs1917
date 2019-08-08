// pixelColor.c
// color scheme for mandelbrot set
// Andrey Avramenko and Jacob Lee

#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include "pixelColor.h"
#include "mandelbrot.h"

typedef unsigned char  bits8;

#define BLACK 0

#define AMPLIFY 3
#define AMPLIFY_SLIGHTLY 1.5
#define DIMINISH_SLIGHTLY 0.75
#define DIMINISH 0.5
#define DULL 0.2
#define DULL_HARD 0.05

unsigned char stepsToBlue (int steps) {
   bits8 shade;
   if (steps == 255) {
      shade = BLACK;
   } else if (steps > 220) {
      shade = BLACK;
   } else if (steps > 200) {
      shade = steps * DULL_HARD;
   } else if (steps > 192) {
      shade = steps * DULL;
   } else if (steps > 186) {
      shade = steps * DIMINISH;
   } else if (steps > 180) {
      shade = steps * DIMINISH_SLIGHTLY;
   } else if (steps > 130) {
      shade = steps;
   } else if (steps > 105) {
      shade = steps * DIMINISH_SLIGHTLY;
   } else if (steps > 95) {
      shade = steps * DIMINISH;
   } else if (steps > 89) {
      shade = steps * DULL;
   } else if (steps > 75) {
      shade = steps * DULL_HARD;
   } else {
      shade = BLACK;
   }
   return shade;
}

unsigned char stepsToGreen (int steps) {
   /* We want to make this trailing off in the distance.
    * We'll have this prominent around the lower values
    */
   bits8 shade;

   if (steps == 255) {
      shade = BLACK;
   } else if (steps < 64) {
      shade = steps * AMPLIFY * AMPLIFY;
   } else if (steps < 128) {
      shade = steps * DIMINISH;
   } else if (steps < 150) {
      shade = steps * DULL;
   } else {
      shade = steps * DULL_HARD;
   }
   return shade;
}

unsigned char stepsToRed (int steps) {
   bits8 shade;
   if (steps == 255) {
      shade = BLACK;
   } else if (steps < 64) {
      shade = steps * DULL_HARD;
   } else if (steps < 130) {
      shade = steps * DIMINISH;
   } else if (steps < 180) {
      shade = steps * DIMINISH_SLIGHTLY;
   } else {
      shade = steps;
   }
   return shade;
}
