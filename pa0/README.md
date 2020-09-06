#Justin Guerrero 
##README

Video walkthrough: [click here](https://montana.techsmithrelay.com/6q1E?tab=Privacy)


This assignment is meant to be a as Travis says "low stakes way to introduce me to this course" and some of the technologies we will use. By the end of this assignment I will have a setup with a suitable environment for completing assignments for this course.

The ultimate objectives of this assignment are:

* to give me an opportunity to weigh in on aspects of the course,
* to give me opportunities to practice with some of the course tools I’ll be using this semester. 

##Task 1
I took the survey

##Task 2: Github
I have been using github for quite some time and one thing I always find handy is the README section. This section usually includes install information, update information, FAQ, and troubleshooting information. 
I hope that I am able to utilize the same format that most of the popular repos I have looked at use such as what is listed above.

A few popular repos I looked at and forked I have listed below.

* [HackPlayers evil-winrm](https://github.com/Hackplayers/evil-winrm)
* Hack players has great instructions on how to use their repo
* [Cheat sheet for hacking tools](https://github.com/JustinGuerrero/Cheatsheet-God)
* Has a lot of information on how to build and use these tools in a Linux environment
* [Travis 460 course code](https://github.com/traviswpeters/cs460-code)
* Had a lot of good README files that I looked through making this




### What is in project 0?
Project 0 is intended to be the initial dipping of the chip into the salsa for the course. This will include instructions on setting up the Virtual environment and the program Vagrant for the ease of use within the virtualbox. Also, there will be familiarization with the command line and make files.

Included in the main repository you will find:

* Directories of the labs under "Lab #**"
* Sub directories inside of the Labs tag with code and instructions for the lab
* This README
* Other fun things like contributors and resources


##Task 3: Virtual Environment and Vagrant


In this task, you’ll get these tools setup on your machine. By the end of this task you should have a fully functional VM where you can run commands, compile software, etc. Subsequent tasks depend on this task, so please make sure you have this task completed before moving on.

###Install VirtualBox on your machine. 

* Select the relevant download for your OS and architecture under “VirtualBox X.Y.Z platform package.”
* Install Vagrant on your machine. Select the relevant download for your OS and architecture.
Download our Vagrantfile from class. 
* Put this file at the top level of whatever directory you plan to do your work in (e.g., ~/projects/cs460/).

  
> mkdir -p ~/projects/cs460/
> 
> cd ~/projects/cs460/
> 
> curl -O https://raw.githubusercontent.com/traviswpeters/cs460-code/master/Vagrantfile


NOTE: The commands above were run on a machine running macOS. It also assumes you have curl installed. Your mileage may vary.

* Open a terminal, navigate to where you stored your Vagrantfile, and run: vagrant up.
* After the machine has been created and successfully boots, run vagrant ssh.


####Run uname -a at the command line, what is this command doing? 

This command appears to give us the system information on the virtual box. The command shows the type of box it is, architecture, build and time is all shown.

##Task 4: The Command Line

The idea of the command line is simple, give control to the user and enter commands for the computer to process and execute. Running the following commands will give various results that I will explain below.

> cd ~ : change into the users home directory
> 
> pwd  : prints the current working directory
> 
> mkdir -p /tmp/this/is/a/sub/directory : makes a directory under the given name
> 
> ln -s /tmp/this/is/a/sub/directory ~/mydir : makes a symbolic link with the given directory
> 
> ls -al : lists all of the contents of the directory with attributes such as file type and permissions
> 
> env | grep PATH : prints the environment variable containing the word PATH
> 
> curl -O https://raw.githubusercontent.com/traviswpeters/cs460-code/master/week02/info : grabs the given webpage and writes into an output file in your local directory
> 
> cat info : will print the text from a file named "info"
> 
> sudo lshw -html > hardwareinfo.html : gives hardware information for html and redirects the info into a file named hardwareinfo.html


###How to figure things out without the internet if you're in a pinch!

The nice thing about Unix/Linux machines is they come with instructions! As do most programs. We call these live savers the man pages. The man pages are a tool that contain instructions, flag identifiers, and examples for virtually any command out there. There is a website you can use but if you don't have internet simply type in "man <name of command you wish to know>" and hit enter!

Throughout my time with the command line my most used tool is cat. It's amazing how you can see everything in a file without needing to open it or use a gui to see its contents!

#Part ll:
## Task 5: Makefiles


With makefiles seeming as a magic trick packed into a file I set out to explore just exactly how they work to get a better understanding of how the program runs with a makefile in play.

I decided to learn how to redirect output into new files first. Redirection is an important thing in the area of field I prefer to spend my time on, Security, and will be helpful to know how to work with it in all types of programming.

###1
What was done was simply adding the >> carrots to the original lines given to us in the code on Travis' github page.

> dress: trousers shoes jacket
>
>
>    @echo "All done. Let's go outside!" >> dressed.txt

This allowed me to redirect the output from the echo command into a new file, dressed.txt


###2
The next thing I wanted to do was make a clean function that would take out any of the targets I had assigned to it making my directory clean in any event I need to do such a thing.
What was needed to do was a simple make function.

>clean: dressed.txt

> $(RM) $(TARGET) $(OBJS)

I also set a taget up top equal to dressed.txt so the makefile didn't get confused. 

###3

The use of the .PHONY method is simple, using this type of method will avoid conflict with files that are named the same and also to increase performance of the makefile. The Phony target is not a file name, but rather just a pseudonym for a process to be executed when making a request.

###4
I decided to do a compression of my folder while I was playing around with my makefile. I found this to be useful because using the tar command we are able to compress the entire system if we wanted to and that there can be valuable. The route I chose to go was to compress a directory that included the practice files I was working with. 
I achieved this by running the following command inside of my makefile.

>zip: 
>
	tar -zcvf dressedUP.tar.gz subdir

this created a compressed copy of the directory that included my makefile and the dressed.txt output file created by the makefile also. I ran make zip, hit the enter button, and away it went!

#Part III
##Task 6

Here I am going to talk about the little code snip I wrote to free all the nodes in the stategame linked list. It's quite simple since we already had a node freeing piece of logic already written right above it.

>  void freeAllNodes(struct listnode *head)
> {
> 
>     struct listnode* tmp;
>     
>     while (head != NULL)
> 
>      {
> 		tmp = head;
> 		head = head->next;
> 		freeNode(tmp);
> 
>      }
> }

##Task 7
###GDB
In this task I set out to relearn the wonderful capabilities of the Gnu projects "debugger" and let me tell you, they built an...interesting... piece of software! So lets take a deeper look and see what we can come up with for this task.

I'm asked to look for the address of the variable head in the stategame by using gdb.
What I learned from security last year is just to use the following command

> (gdb) p &head
> 
> $2 = (struct listnode *) 0x7fffffffe3c0

The p &head basically says point to the location in memory of the "head" variable. and we get it's type and memory address in return.

Now lets see if I can rock some local variables from main!

First things first lets get this bad boy runnin'

> [vagrant@vbox][~/projects/week02/stategame]$ gdb -q stategame
> 
> Reading symbols from stategame...done.

Awesome, now lets put our foot on the gas and yell yeehaw while we put a break point at the main() function!

> (gdb) b main
> Breakpoint 1 at 0x555555554983: file stategame.c, line 35.
> 
> (gdb) run
>
> Starting program: /home/vagrant/projects/week02/stategame/stategame stategame
>
> Breakpoint 1, main () at stategame.c:35
> 
> 35      {

Use the handy backtrace function.......

> (gdb) bt
> 
> `#0  main () at stategame.c:35`

Now that we've gotten to this point lets look for local variables by using the "info locals" command.

> (gdb) info locals
> 
> head = {name = 0x7ffff7de59f0 <_dl_fini> "UH\211\345AWAVAUATSH\203\354(L\213%X\177!", next = 0x0}
> 
> lineLength = 0
> 
> line = "H\203"
> 
> n = 15775231
> 
> (gdb) 

And there you have it folks! Local variables in main from gdb.

###Valgrind

A programming tool that allows us to debug and look through memory. This is going to be particularly helpful for task 6 as I was tasked to free all the nodes in the list. 

What I did was run a command which essentially runs the game in a memory debugging state.
> myvalgrind ./stategame  

This got the game started up and I then proceeding to enter a few states before quitting. The next thing I was shown from myvalgrind was a report on the memory of the game.

> [vagrant@vbox][~/projects/week02/stategame]$ myvalgrind ./stategame
> 
> ==22768== Memcheck, a memory error detector
 
> ==22768== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
>
> ==22768== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
>
> ==22768== Command: ./stategame
>
> ==22768==
>
> montana
>
> idaho
>
> You have 2 states:
>
> idaho
>
> montana
>
> ==22768==
>
> ==22768== HEAP SUMMARY:
>
> ==22768==     in use at exit: 0 bytes in 0 blocks
>
> ==22768==   total heap usage: 6 allocs, 6 frees, 2,096 bytes allocated
>
> ==22768==
>
> ==22768== All heap blocks were freed -- no leaks are possible
>
> ==22768==
>
> ==22768== For counts of detected and suppressed errors, rerun with: -v
> 
> ==22768== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

##Task 8 Github

Done.