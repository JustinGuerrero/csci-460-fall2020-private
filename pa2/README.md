# Justin Guerrero : Operating Systems CS460
## Programming assignment 2 : Bridger to Bozeman
## Overview
The idea of this project is to gain familiarity with threading and synchronized programming by using mutual exclusion locks and condition variables. 
We will make great use of the ```pthreads``` package. 

## Assignment

Suppose that a road crew needs to clear snow off of Bridger Canyon Road to repair some damaged road between Bozeman and Bridger Bowl. This construction requires closing one lane of traffic, making it a **one-way road** for a section of Bridger Canyon Road. As a result, traffic may only traverse the single lane road in one direction at a time. To further complicate matters, the integrity of the road has been weakened due to the damage. Thus, only a small number of cars can be on the damaged section of Bridger Canyon Road at any given time, limiting its capacity to at most ```MAXCARS``` vehicles. (E.g., try ```MAXCARS``` = 3.)

## I/O
The program should require two command like arguments, the ```NUMCARS``` function and the ```MAXCARS``` function. These ensure the the program knows how many cars there are and how many can go through the construction zone at one. The program will accept up to four arguments, the final two being ```RANDSEED``` which is the seed number for randomly generating numbers and ```VERBOSITY``` which changed the output mode.

Essentially I made a few while loops that allowed this functionality to work.

## Synchronization 
This was the hard part. Finding ways to lock threads appropriately while you're running processes (simulating the one way traffic while you're driving) to prevent collisions. How I cam to achieve this process was by carefully and strategically placing locks, unlocks, and signal mutex functions. 

This works by locking a thread (car) in a function allowing it to run it's course. I start my ```MAXCAR``` counter at zero. While the cars were running across they increment the counter that allows only three (or whatever ```MAXCARS`` is set to) to go through at a time. Then unlocking the thread to get the car across the construction zone. 

The next thing is to signal the next line of cars it is their turn. When I ran the increment it kept count of ```MAXCAR``` value whenever that number is reached it will send a signal to "swap directions". 