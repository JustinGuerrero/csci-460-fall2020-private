//
// Created by Justin Guerrero on 9/12/2020.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int resizePhoto(const char * program, char ** arg_list) { 
    //use the command line convert program from imagemagick
	
  pid_t child_pid = fork();
  if (child_pid != 0)
    return child_pid;      /* This is the parent process.  */
  else {
    execvp(program, arg_list);     /* Now execute PROGRAM */
	
	fprintf (stderr, "An error occurred in execvp\n");
    abort ();
  } 
}

int thumbNail(const char * program2, char ** arg_list2){
  pid_t child_pid = fork();
  if (child_pid != 0)
    return child_pid;      /* This is the parent process.  */
  else {
    execvp(program2, arg_list2);     /* Now execute PROGRAM */
	
	fprintf (stderr, "An error occurred in execvp\n");
    abort ();
  } 
}
int displayPhoto(const char *program3, char ** arg_list3){
	  pid_t child_pid = fork();
  if (child_pid != 0)
    return child_pid;      /* This is the parent process.  */
  else {
    execvp(program3, arg_list3);     /* Now execute PROGRAM */
	
	fprintf (stderr, "An error occurred in execvp\n");
    abort ();
  } 
}

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

int makeHTML(){
	//do html stuff here
	FILE *fptr = fopen("index.html","w");
	if(fptr==NULL){
		printf("Couldn't open file");
		return 0;
	}
	else{
		fprintf(fptr, "Content-Type: text/html\n\n");
		fprintf(fptr, "<html>");
		fprintf(fptr, "<head><title>Photo Album</title></head>");
		fprintf(fptr, "<body>here is a body</body>");
	}
	return 0;
		
}

int main() { 
  makeHTML();
  char *arg_list3[] = {"display", "photos/newVedraPhotoThumb.png",NULL};  
  char *arg_list2[] = {"convert", "photos/Es_Vedra_Sunset.jpg", "-resize", "25%", "photos/newVedraPhotoThumb.png",NULL};  
  char *arg_list[] = {"convert", "photos/Es_Vedra_Sunset.jpg", "-resize", "75%", "photos/newVedraPhoto.png",NULL};
  resizePhoto("convert", arg_list); 
  thumbNail("convert", arg_list2);
  displayPhoto("display", arg_list3);
  printf ("Main program exiting...\n");
  return 0; 
}
