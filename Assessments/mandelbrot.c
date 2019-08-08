/*
 *  mandelbrot.c
 *  1917 serve a mandelbrot set based on coordinates given
 *
 *  Conatining code created by Tim Lambert on 02/04/12.
 *  Containing code created by Richard Buckland on 28/01/11.
 * 
 *  Created by Andrey Avramenko and Jacob Lee 04/2019
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <math.h>
#include "pixelColor.h"
#include "mandelbrot.h"

#define SIMPLE_SERVER_VERSION 1.0
#define REQUEST_BUFFER_SIZE 1000
#define DEFAULT_PORT 1917
#define NUMBER_OF_PAGES_TO_SERVE 1000000

#define TRUE 1
#define FALSE 0
#define ROOT 0.5

#define BYTES_PER_PIXEL 3
#define SIZE_OF_HEADER 54
#define SIZE 512

#define BMP_FILE "almondbread.bmp"
#define SCALE_UP 2

#define BLACK 0
#define WHITE 255

#define AMPLIFY 3
#define AMPLIFY_SLIGHTLY 1.5
#define DIMINISH_SLIGHTLY 0.75
#define DIMINISH 0.5
#define DULL 0.2
#define DULL_HARD 0.05

#define NUM_SLASH_BEFORE_EXTRACT 3
#define FENCEPOST_ERROR 1

typedef unsigned char  bits8;
typedef unsigned short bits16;
typedef unsigned int   bits32;

typedef struct _triordinate {
   double x;
   double y;
   int z;
} triordinate;

int waitForConnection (int serverSocket);
int makeServerSocket (int portno);
void writeHeader (FILE *file);
void serveBMP (int socket, bits8 *bmp);
void createBMP (double xCoordinateGiven, double yCoordinateGiven,
int zoomGiven, bits8 *bytesInBMP);
triordinate extract (char *message);
double myAtoD (char *message);
long myAtoL (char *message);

// after serving this many pages the server will halt

int main (int argc, char *argv[]) {
      
   printf ("************************************\n");
   printf ("Starting simple server %f\n", SIMPLE_SERVER_VERSION);
   printf ("Serving bmps since 2012\n");   
   
   int serverSocket = makeServerSocket (DEFAULT_PORT);   
   printf ("Access this server at http://localhost:%d/\n", 
      DEFAULT_PORT);
   printf ("************************************\n");
   
   char request[REQUEST_BUFFER_SIZE];
   
   int numberServed = 0;

   bits8 bytesInBMP[SIZE * SIZE * BYTES_PER_PIXEL];

   while (numberServed < NUMBER_OF_PAGES_TO_SERVE) {
      
      printf ("*** So far served %d pages ***\n", numberServed);
      
      int connectionSocket = waitForConnection (serverSocket);
      // wait for a request to be sent from a web browser, open a new
      // connection for this conversation
      
      // read the first line of the request sent by the browser  
      int bytesRead;
      bytesRead = read (connectionSocket, request, (sizeof request)-1);
      assert (bytesRead >= 0); 
      // were we able to read any data from the connection?
      printf ("Request is %s\n", request);
      

      triordinate givenCoordinates = extract (request);
      printf ("%f %f %d\n", givenCoordinates.x, givenCoordinates.y, 
         givenCoordinates.z);

      createBMP (givenCoordinates.x, givenCoordinates.y, 
         givenCoordinates.z, bytesInBMP);

      
      printf ("First six bytes are %d, %d, %d, %d, %d, %d\n", 
         bytesInBMP[0], bytesInBMP[1], bytesInBMP[2], bytesInBMP[3], 
         bytesInBMP[4], bytesInBMP[5]);
      // Printing entire request to the console 
      printf (" *** Received http request ***\n %s\n", request);
      
      //send the browser a simple html page using http
      printf (" *** Sending http response ***\n");

      if (strstr(request, "mandelbrot") != NULL) {
          serveBMP(connectionSocket, bytesInBMP);
      } else {        
           char* message =
              "HTTP/1.0 200 OK\r\n"
              "Content-Type: text/html\r\n"
              "\r\n"
              "<script src=\"http://almondbread."
              "cse.unsw.edu.au/tiles.js\"></script>";      
           write (connectionSocket, message, strlen (message));
      }

      
      // Closing the connection after sending the page
      close(connectionSocket);
      
      numberServed++;
   } 

   printf ("** shutting down the server **\n");
   close (serverSocket);
   
   return EXIT_SUCCESS; 
}

void serveBMP (int socket, bits8 *bytesInBMP) {
   char* message;
   int i = 0;
   
   // First sending the http response header
   
   message = "HTTP/1.0 200 OK\r\n"
                "Content-Type: image/bmp\r\n"
                "\r\n";
   printf ("about to send=> %s\n", message);
   write (socket, message, strlen (message));
   
   // Now sendING the BMP
   unsigned char bmp[SIZE * SIZE * BYTES_PER_PIXEL + SIZE_OF_HEADER];
   bmp[0] = 0x42;
   bmp[1] = 0x4d;
   bmp[2] = 0x36;
   bmp[3] = 0x00;
   bmp[4] = 0x0c;
   bmp[5] = 0x00;
   bmp[6] = 0x00;
   bmp[7] = 0x00;
   bmp[8] = 0x00;
   bmp[9] = 0x00;
   bmp[10] = 0x36;
   bmp[11] = 0x00;
   bmp[12] = 0x00;
   bmp[13] = 0x00;
   bmp[14] = 0x28;
   bmp[15] = 0x00;
   bmp[16] = 0x00;
   bmp[17] = 0x00;
   bmp[18] = 0x00;
   bmp[19] = 0x02;
   bmp[20] = 0x00;
   bmp[21] = 0x00;
   bmp[22] = 0x00;
   bmp[23] = 0x02;
   bmp[24] = 0x00;
   bmp[25] = 0x00;
   bmp[26] = 0x01;
   bmp[27] = 0x00;
   bmp[28] = 0x18;
   bmp[29] = 0x00;
   bmp[30] = 0x00;
   bmp[31] = 0x00;
   bmp[32] = 0x00;
   bmp[33] = 0x00;
   bmp[34] = 0x00;
   bmp[35] = 0x00;
   bmp[36] = 0x0c;
   bmp[37] = 0x00;
   bmp[38] = 0x13;
   bmp[39] = 0x0b;
   bmp[40] = 0x00;
   bmp[41] = 0x00;
   bmp[42] = 0x13;
   bmp[43] = 0x0b;
   bmp[44] = 0x00;
   bmp[45] = 0x00;
   bmp[46] = 0x00;
   bmp[47] = 0x00;
   bmp[48] = 0x00;
   bmp[49] = 0x00;
   bmp[50] = 0x00;
   bmp[51] = 0x00;
   bmp[52] = 0x00;
   bmp[53] = 0x00;
   
   while (i != SIZE * SIZE * BYTES_PER_PIXEL) {
      bmp[i + 54] = bytesInBMP[i];
      i++;
   }    
   FILE *outputFile;

   outputFile = fopen("TestMan.bmp", "wb");
   fwrite(bmp, sizeof(bmp), 1, outputFile);
   fclose(outputFile);
   write (socket, bmp, sizeof(bmp));
}

// start the server listening on the specified port number
int makeServerSocket (int portNumber) { 
   
   // create socket
   int serverSocket = socket (AF_INET, SOCK_STREAM, 0);
   assert (serverSocket >= 0);   
   // error opening socket
   
   // bind socket to listening port
   struct sockaddr_in serverAddress;
   memset ((char *) &serverAddress, 0,sizeof (serverAddress));
   
   serverAddress.sin_family      = AF_INET;
   serverAddress.sin_addr.s_addr = INADDR_ANY;
   serverAddress.sin_port        = htons (portNumber);
   
   // let the server start immediately after a previous shutdown
   int optionValue = 1;
   setsockopt (
      serverSocket,
      SOL_SOCKET,
      SO_REUSEADDR,
      &optionValue, 
      sizeof(int)
   );

   int bindSuccess = 
      bind (
         serverSocket, 
         (struct sockaddr *) &serverAddress,
         sizeof (serverAddress)
      );
   
   assert (bindSuccess >= 0);
   // if this assert fails wait a short while to let the operating 
   // system clear the port before trying again
   
   return serverSocket;
}

// wait for a browser to request a connection,
// returns the socket on which the conversation will take place
int waitForConnection (int serverSocket) {
   // listen for a connection
   const int serverMaxBacklog = 10;
   listen (serverSocket, serverMaxBacklog);
   
   // accept the connection
   struct sockaddr_in clientAddress;
   socklen_t clientLen = sizeof (clientAddress);
   int connectionSocket = 
      accept (
      serverSocket, 
      (struct sockaddr *) &clientAddress, 
      &clientLen
    );
    
   assert (connectionSocket >= 0);
   // error on accept
   
   return (connectionSocket);
}

void createBMP (double xCoordinateGiven, double yCoordinateGiven, int zoomGiven, bits8 *bytesInBMP) {

   int numPixelsInRow = SIZE;
   int numPixelsInCol = SIZE;
   int numPixelsInQuadrant = SIZE / 2;

   int colPos = 0;
   int rowPos = 0;
   double xValue;
   double yValue;

   int i = 0;
   int steps;
   bits8 shadeOfBlue;
   bits8 shadeOfGreen;
    bits8 shadeOfRed;

   while (rowPos < numPixelsInRow) {
      colPos = 0;
         while (colPos < numPixelsInCol) {
            // Here, we're changing the number of pixels across we have
            // and plotting them as coordinates as if they were on a
            // plane of x and y, the range being from -256 to 256.
            xValue = colPos - numPixelsInQuadrant;
            yValue = rowPos - numPixelsInQuadrant;

            // Here, we're scaling so it becomes on a graph with ranges
            // of -2 to 2. This lets us properly work with it before
            // graphing.
            xValue = (xValue / numPixelsInQuadrant) * SCALE_UP;
            yValue = (yValue / numPixelsInQuadrant) * SCALE_UP;

            // This is the part were the coordinates are adjusted
            // to the given zoom and the given x and y coordinates.
            xValue = xValue * pow(2, -1 * (zoomGiven-7));
            yValue = yValue * pow(2, -1 * (zoomGiven-7));

            xValue = xValue + xCoordinateGiven;
            yValue = yValue + yCoordinateGiven;

            // This is where we put the coordinate of the pixel through
            // an escape steps function to determine if or when it 
            // escapes the set.
            steps = escapeSteps(xValue, yValue);

            // The 'i's in the following chunk are for each of the 
            // bytes, as there are 3 in a pixel

            // This is where we adjust the shade of blue of the pixel.
            shadeOfBlue = stepsToBlue(steps);
            bytesInBMP[i] = shadeOfBlue;
            i++;
            // This is where we adjust the shade of green of the pixel.
            shadeOfGreen = stepsToGreen(steps);
            bytesInBMP[i] = shadeOfGreen;
            i++;
            // This is where we adjust the shade of red of the pixel.
            shadeOfRed = stepsToRed(steps);
            bytesInBMP[i] = shadeOfRed;
            i++;

            // Moving to the next column...
            colPos++;
         }
      // Moving to the next row...
      rowPos++;
   }
}

int escapeSteps(double x, double y) {
   int counter = 0;
   double c[2];
   c[0] = x;
   c[1] = y;
   double z[2] = {0};
   double newZCoordinates[2];

   // Using arrays, we calculate how many iterations the given
   // coordinates take before escaping, returning the number
   // to adjust the color of the set.
   while ((z[0]*z[0]) + (z[1]*z[1])  <= 4 && counter < 256) {
      newZCoordinates[0] = ((z[0]*z[0]) + (z[1]*z[1]*(-1))) + c[0];
      newZCoordinates[1] = (z[0]*z[1]*2) + c[1];
      z[0] = newZCoordinates[0];
      z[1] = newZCoordinates [1];
      counter++;
   }
   counter = counter - FENCEPOST_ERROR;
   return counter;
}

triordinate extract (char *message) {
   // This function, given a link, gives back the coordinates and zoom
   // given. This adjusts the mandelbrot set.

   triordinate dat;
   dat.x = 0;
   dat.y = 0;
   dat.z = 0;
   int i = 0;
   int numSlash = 0;
   int numPointX = 0;
   int numPointY = 0;
   int decimalPlacesBackX = 10;
   int decimalPlacesBackY = 10;
   int negativeX = 0;
   int negativeY = 0;
   int negativeZ = 0;

   while (message[i] != '\0') {
      if (message[i] == '/') {
         numSlash++;
      } else if (numSlash == NUM_SLASH_BEFORE_EXTRACT) {
         dat.z = dat.z * 10;
         dat.z = dat.z + myAtoL (&message[i]);
         if (message[i] == '-') {
            negativeZ = TRUE;
         }
      } else if (numSlash == NUM_SLASH_BEFORE_EXTRACT + 1) {
         if (message[i] == '-') {
            negativeX = TRUE;
         } else if (message[i] == '.') {
            numPointX = 1;
         } else if (numPointX == 0 ) {
            dat.x = dat.x * 10;
            dat.x = dat.x + myAtoD (&message[i]);
         } else if (numPointX == 1) {
            dat.x = dat.x + (myAtoD (&message[i]) / decimalPlacesBackX);
            decimalPlacesBackX = decimalPlacesBackX * 10;
         }
      } else if (numSlash == NUM_SLASH_BEFORE_EXTRACT + 2) {
         if (negativeX == TRUE) {
            dat.x = dat.x * (-1);
            negativeX = FALSE;
         }
         if (negativeZ == TRUE) {
            dat.z = dat.z * (-1);
            negativeZ = FALSE;
         }
         if (message[i] == '-') {
            negativeY = TRUE;
         } else if (message[i] == '.') {
            numPointY = TRUE;
         } else if (numPointY == FALSE) {
            dat.y = dat.y * 10;
            dat.y = dat.y + myAtoD (&message[i]);
         } else if (numPointY == TRUE) {
            dat.y = dat.y + (myAtoD (&message[i]) / decimalPlacesBackY);
            decimalPlacesBackY = decimalPlacesBackY * 10;
         }
      } else if (numSlash == NUM_SLASH_BEFORE_EXTRACT + 3) {
         if (negativeY == TRUE) {
            dat.y = dat.y * (-1);
            negativeY = FALSE;
         }
      }
      i++;
   }
   return dat;
}

double myAtoD (char *message) {
   return (message[0] - '0');
}

long myAtoL (char *message) {
   return (message[0] - '0');
}

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



