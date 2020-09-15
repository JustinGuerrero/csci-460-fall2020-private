#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define A 500
#define B 600 
#define C 700
#define execve

    
int main (int argc, char **argv)
{   
    int i, j;
    long sum;

    int pid;
    int status, ret;
	char *myargs [] = { "magick convert photos/Es_Vedra_Sunset -resize 75% newPhoto1" };
    char *myenv [] = { NULL };
	execve ("photos/Es_Vedra_Sunset", myargs, myenv);
	

    for (j = 0; j < 30; j++ ) {
        for (i =0; i < 900000; i++) {
            sum = A * i + B * i * i + C;
            sum %= 543;
        }
    }

    printf ("Child: Work completed!\n");
    printf ("Child: Bye now.\n");

    exit (0);
}
