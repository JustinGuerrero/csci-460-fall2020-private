<<<<<<< HEAD
# README For Programming Assignment 1
## By Justin Guerrero
The purpose of this README is to inform the reader of the tasks, strategies, and ideas that are involved in program 1 for Operating Systems.

The way I separated this document is in tasks. Each task is in the order of how I approached the assignment. 
### VIDEO LINK: https://montana.techsmithrelay.com/Cb1e?tab=Privacy
## Description
### Objective: Create A Web-Based Digital Photo Album
Write a C program that allows a user to peruse a set of large images downloaded from a digital camera, and produce an HTML photo album and  practical experience with the topics listed below, in a way that’s tangible and (hopefully) a bit fun.

### Topics covered:
- processes,
- system calls (via library calls) that manipulate them, and
- various system goals we might achieve by using concurrent processes.

### Requirements: 
For each photo in this input set, the program should:


- Generate a thumbnail version (25%) of the photo (using the Linux command-line convert       program).
- Display the thumbnail to the user (using the Linux command-line display program).
- Ask the user whether or not it should be rotated / how much it should be rotated; if so, do it (using the Linux command-line convert program).
- Ask the user for a caption, and collect it.
Generate a properly oriented 75% version of the photo (using the Linux command-line convert program)
- When done, the program should leave the following in the directory in which it was invoked. (That is, if you were in foo/ when you invoked album, then all these things go into foo/)
- a file index.html containing, for each photo:
- a properly oriented thumbnail
- a caption
- a link from the thumbnail to a properly oriented medium-size version of the photo
the thumbnails and medium-size versions.
(And, optionally, any support files for your HTML file; e.g., a CSS file.)

## Task 1
The initial task of creating system calls without using the "system()" function led me to want to do a bit of research. I decided using exec() suite of commands was the best bet. The program is intended for us to understand processes more and to understand how forking a a child works. 

The first place I started was by writing the code to break this down into chunks. Below is a snip of how the fork() function works.

    int displayPhoto(const char *program3, char ** arg_list3){
    	pid_t child_pid = fork();
      	if (child_pid != 0)
    		return child_pid;  /* This is the parent process.  */
      else {
    		execvp(program3, arg_list3); /* Now execute PROGRAM */
    	
    		fprintf (stderr, "An error occurred in execvp\n");
      abort ();
      } 
    } 

Note at the second line of code we are initiating a variable to fork() a process. This starts the child process which runs in parallel with the parent process. While the parent process is waiting we see in the else{} statement we call execvp(). This is a system call that executes commands that we give it. In this case you will see a list of commands below that we use to work with "imagemagick", the particular suite of tools we used during this project.



## Task 2
The next step once the fork() and exec() process has been executed was to work with the list of commands I spoke about above. The idea of the program is to execute commands in a child process so we pass them to exec through a string of commands.

      char *arg_list[] = {"convert", "photos/Es_Vedra_Sunset.jpg", "-resize", "75%", "photos/newVedraPhoto.png",NULL};

The way this works is it will pass this "strings" in as arguments to execvp. Each argument gets read and will then execute. So here in this instance we see that convert gets run first and then the rest will run one after another. I used a similar lines of strings to run the required converts for the PA1 assignment.
 
## Task 3
This is where I decided to make some HTML code by printing to a file a bunch of html code (Which seemed very unnecessary to do it this way in my opinion).
We are able to use the fprinf() function and inside type html commands. I have included a sample below of how to do this sort of thing. 

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

Notice how I saved the file as "index.html" and chose the "w" option to be able to write to this file. 
Everything that gets executed in the fprintf function writes to the file and after it's all written to we are able to serve the file using apache2 server on linux, or any other web server service that you choose.

## Task 4
This next part of the lab is where we worked on command line usage. This means we took arguments from the command line to pass into our functions. This was pretty straight forward using the argv[] option that is offered in C programming and many other programming languages. The idea is simple, it works by passing in files, options, or commands through the CL interface after your program name. 
For instance, if your program is named "album" and you run ./album then you would simply follow it by whatever arguments you're trying to pass in. 




    ``` ./album argument1 argument2 .... argument(n) ```

I will include a portion of my main function here for context also.

    ```int main(int argc, char *argv[]) {
      // create arrays for the user input
      char c[90];	 // caption
      char rr[10];	 // rotate


      // create arg strings for function inputs and calls
      char *arg_list[] =  {"convert", argv[1], "-resize", "75%", res,NULL};
      char *arg_list2[] = {"convert", argv[2], "-resize", "25%", newestC, NULL};
      char *arg_list4[] = {"convert", argv[3], "-rotate", rr, newestC, NULL};
      char *arg_list3[] = {"display", newestC ,NULL};  
    ```

You'll see that the argv commands are listed in the arg_list[] strings where we want to place something from the command line. In this case it will refer to the photos that we are converting.

## Task 5: Lifeline diagram
See github for diagram pdf.


## Task 6 
See attached file "Testing" for gdb test results.
=======
# README For Programming Assignment 1
## By Justin Guerrero
The purpose of this README is to inform the reader of the tasks, strategies, and ideas that are involved in program 1 for Operating Systems.

The way I separated this document is in tasks. Each task is in the order of how I approached the assignment. 
### VIDEO LINK: https://montana.techsmithrelay.com/Cb1e?tab=Privacy
## Description
### Objective: Create A Web-Based Digital Photo Album
Write a C program that allows a user to peruse a set of large images downloaded from a digital camera, and produce an HTML photo album and  practical experience with the topics listed below, in a way that’s tangible and (hopefully) a bit fun.

### Topics covered:
- processes,
- system calls (via library calls) that manipulate them, and
- various system goals we might achieve by using concurrent processes.

### Requirements: 
For each photo in this input set, the program should:


- Generate a thumbnail version (25%) of the photo (using the Linux command-line convert       program).
- Display the thumbnail to the user (using the Linux command-line display program).
- Ask the user whether or not it should be rotated / how much it should be rotated; if so, do it (using the Linux command-line convert program).
- Ask the user for a caption, and collect it.
Generate a properly oriented 75% version of the photo (using the Linux command-line convert program)
- When done, the program should leave the following in the directory in which it was invoked. (That is, if you were in foo/ when you invoked album, then all these things go into foo/)
- a file index.html containing, for each photo:
- a properly oriented thumbnail
- a caption
- a link from the thumbnail to a properly oriented medium-size version of the photo
the thumbnails and medium-size versions.
(And, optionally, any support files for your HTML file; e.g., a CSS file.)

## Task 1
The initial task of creating system calls without using the "system()" function led me to want to do a bit of research. I decided using exec() suite of commands was the best bet. The program is intended for us to understand processes more and to understand how forking a a child works. 

The first place I started was by writing the code to break this down into chunks. Below is a snip of how the fork() function works.

    int displayPhoto(const char *program3, char ** arg_list3){
    	pid_t child_pid = fork();
      	if (child_pid != 0)
    		return child_pid;  /* This is the parent process.  */
      else {
    		execvp(program3, arg_list3); /* Now execute PROGRAM */
    	
    		fprintf (stderr, "An error occurred in execvp\n");
      abort ();
      } 
    } 

Note at the second line of code we are initiating a variable to fork() a process. This starts the child process which runs in parallel with the parent process. While the parent process is waiting we see in the else{} statement we call execvp(). This is a system call that executes commands that we give it. In this case you will see a list of commands below that we use to work with "imagemagick", the particular suite of tools we used during this project.



## Task 2
The next step once the fork() and exec() process has been executed was to work with the list of commands I spoke about above. The idea of the program is to execute commands in a child process so we pass them to exec through a string of commands.

      char *arg_list[] = {"convert", "photos/Es_Vedra_Sunset.jpg", "-resize", "75%", "photos/newVedraPhoto.png",NULL};

The way this works is it will pass this "strings" in as arguments to execvp. Each argument gets read and will then execute. So here in this instance we see that convert gets run first and then the rest will run one after another. I used a similar lines of strings to run the required converts for the PA1 assignment.
 
## Task 3
This is where I decided to make some HTML code by printing to a file a bunch of html code (Which seemed very unnecessary to do it this way in my opinion).
We are able to use the fprinf() function and inside type html commands. I have included a sample below of how to do this sort of thing. 

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

Notice how I saved the file as "index.html" and chose the "w" option to be able to write to this file. 
Everything that gets executed in the fprintf function writes to the file and after it's all written to we are able to serve the file using apache2 server on linux, or any other web server service that you choose.

## Task 4
This next part of the lab is where we worked on command line usage. This means we took arguments from the command line to pass into our functions. This was pretty straight forward using the argv[] option that is offered in C programming and many other programming languages. The idea is simple, it works by passing in files, options, or commands through the CL interface after your program name. 
For instance, if your program is named "album" and you run ./album then you would simply follow it by whatever arguments you're trying to pass in. 




    ``` ./album argument1 argument2 .... argument(n) ```

I will include a portion of my main function here for context also.

    ```int main(int argc, char *argv[]) {
      // create arrays for the user input
      char c[90];	 // caption
      char rr[10];	 // rotate


      // create arg strings for function inputs and calls
      char *arg_list[] =  {"convert", argv[1], "-resize", "75%", res,NULL};
      char *arg_list2[] = {"convert", argv[2], "-resize", "25%", newestC, NULL};
      char *arg_list4[] = {"convert", argv[3], "-rotate", rr, newestC, NULL};
      char *arg_list3[] = {"display", newestC ,NULL};  
    ```

You'll see that the argv commands are listed in the arg_list[] strings where we want to place something from the command line. In this case it will refer to the photos that we are converting.

## Task 5: Lifeline diagram
See github for diagram pdf.


## Task 6 
See attached file "Testing" for gdb test results.
>>>>>>> 0453ffae993d168f1e5dcbccc37ccbb8a9bde253
