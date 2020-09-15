//
// Created by Justin Guerrero on 9/12/2020.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


    //use the command line convert program from imagemagick
	//use fork and exec so user doesn't wait-
	//FILE *outputFile = fopen("photos/Es_Vedra_Sunset.jpg", "r");
	// if(outputFile == NULL){
		// printf("Error: Failed to open stuff\n");
		// return 1;
	// }
	// char *resize[80];
	// resize[0] = "magick convert argv[1] -resize 75% newPhoto1.png";
	// resize[1] = NULL;
	// execve(resize[0], resize, NULL);
	// return 0;
// }

// void thumbNail(){
    // //use the command line display program from imagemagick
	
	// FILE *fopen =(const char *photos/Es_Vedra_Sunset.jpg, const char *"r");
	// photo[0] = FILE;
	// char *resize[80];
	// resize[0] = "magick convert argv[1] -resize 75% newPhoto1.png";
	// resize[1] = NULL;
	// execlp(resize[0], resize, NULL);
// }

// void askUserRotate(){
    // //use the convert program here again with rotate function
// }

// char askForCaption(){
    // char captionInput[80];
    // //asks user for caption
    // printf("What would you like to caption this photo: ");
    // scanf("%[^\n]%*c", captionInput);
    // printf("the photo now has the caption: %s \n", captionInput);
    // return(0);
// }

// void orientatePhoto(){

    // // use convert program here
// }
int resizePhoto(const char * program, char ** arg_list) { 
  pid_t child_pid = fork();
  if (child_pid != 0)
    return child_pid;      /* This is the parent process.  */
  else {
    execvp (program, arg_list);     /* Now execute PROGRAM */
    fprintf (stderr, "An error occurred in execvp\n");
    abort ();
  } 
}
int main() { 
  char *arg_list[] = {"magick", "convert", "photos/Es_Vedra_Sunset", "-resize", "75%", "newPhoto", NULL};
  resizePhoto("ls", arg_list); 
  printf ("Main program exiting...\n");
  return 0; 
}
