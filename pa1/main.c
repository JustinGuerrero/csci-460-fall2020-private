//
// Created by Justin Guerrero on 9/12/2020.
//
#include <stdio.h>
#include <string.h>
#include "photoStruct.h"

photoStruct photo[10];
int resizePhoto(photoStruct photo[], int arrLength){
	FILE = *outputFile;
    //use the command line convert program from imagemagick
	//use fork and exec so user doesn't wait-
	outputFile = fopen(const char *photos/Es_Vedra_Sunset.jpg, const char *"r");
	if(outputFile == NULL){
		printf(stderr, "Error: Failed to open stuff\n")
		return 1;
	}
	photo[0] = FILE;
	char *resize[80];
	resize[0] = "magick convert argv[1] -resize 75% newPhoto1.png";
	resize[1] = NULL;
	execve(resize[0], resize, NULL);
	return 0;
}

void thumbNail(photoStruct photo[], int arrLength){
    //use the command line display program from imagemagick
	
	FILE *fopen =(const char *photos/Es_Vedra_Sunset.jpg, const char *"r");
	photo[0] = FILE;
	char *resize[80];
	resize[0] = "magick convert argv[1] -resize 75% newPhoto1.png";
	resize[1] = NULL;
	execlp(resize[0], resize, NULL);
}

void askUserRotate(photoStruct photo[], int arrLength){
    //use the convert program here again with rotate function
}

char askForCaption(photoStruct photo[]){
    char captionInput[80];
    //asks user for caption
    printf("What would you like to caption this photo: ");
    scanf("%[^\n]%*c", captionInput);
    printf("the photo now has the caption: %s \n", captionInput);
    return(0);
}

void orientatePhoto(photoStruct photo[], int arrLength){

    // use convert program here
}



int main(int argc, char *argv[]){
	askForCaption(photoStruct photo[]);
	resizePhoto(photoStruct photo[]);
//   printf(argv[1]);
	return 0;
}
