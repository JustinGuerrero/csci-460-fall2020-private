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


char askUserRotate(const char *program4, char ** arg_list4, char *r){
    //use the convert program here again with rotate function
	printf("How much do you want to rotate this photo: ");
    scanf("%[^\n]%*c", r);
    printf("the photo now has been rotated: %s \n", r);
		  pid_t child_pid = fork();
  if (child_pid != 0)
    return child_pid;      /* This is the parent process.  */
  else {
    execvp(program4, arg_list4);     /* Now execute PROGRAM */
	
	fprintf (stderr, "An error occurred in execvp\n");
    abort ();
  } 
    return *r;
}

char askForCaption(char c[]){
    //asks user for caption
    printf("What would you like to caption this photo: ");
    scanf("%[^\n]%*c", c);
    printf("the photo now has the caption: %s \n", c);
    return *c;
}


int makeHTML(char* c){
	// fprinf to print html code to the "index.html" file
	FILE *fptr = fopen("index.html","w");
	if(fptr==NULL){
		printf("Couldn't open file");
		return 0;
	}
	else{
		fprintf(fptr, "Content-Type: text/html\n\n");
		fprintf(fptr, "<html>\n\n");
		fprintf(fptr, "<head><title>Photo Album</title></head>\n\n");
		fprintf(fptr, "<body>here is your photo album, enjoy</body>\n\n");
		fprintf(fptr, "<div class='row'>\n\n");
		fprintf(fptr, "<img src='photos/newVedraPhotoThumb.png'>\n\n");
		fprintf(fptr, "</div class='row'>\n\n");
		fprintf(fptr, "<div class='row'>\n\n");
		fprintf(fptr, "<img src='photos/>\n\n");
		fprintf(fptr, "</div class='row'>\n\n");
	}
	return 0;
		
}


int main(int argc, char *argv[]) {
  // create arrays for the user input
  char c[90];	 // caption
  char rr[10];	 // rotate
  
  //input functions from user are placed here to gather values for arguments
  askForCaption(c);
  char *newC = strcat(c, "thumb.png");
  char str[100] = "photos/";
  char *newestC = strcat(str, newC);

  
  // create arg strings for function inputs and calls
  char *arg_list[] =  {"convert", argv[1], "-resize", "75%", argv[1], NULL};		// resize to 75%	
  char *arg_list2[] = {"convert", argv[1], "-resize", "25%", newestC, NULL};	// create thumbnail
  char *arg_list4[] = {"convert", argv[1], "-rotate", rr, "rotated.png", NULL};		// rotate image
  char *arg_list3[] = {"display", newestC ,NULL}; 												// display image	
  

  // call functions and hope they work
  
  askUserRotate("convert", arg_list4, rr); // concat string for thumb
  resizePhoto("convert", arg_list); 
  thumbNail("convert", arg_list2);
  sleep(5);
  displayPhoto("display", arg_list3);
  makeHTML(c);
  printf ("Main program exiting...\n");
  printf("hi");
  return 0; 
}
