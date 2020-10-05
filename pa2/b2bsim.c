/*
 * This is the b2bsim.c starter file!
 *
 * A program that simulates the traffic of a one way on bridger canyon
 *
 * Author: Justin Guerrero
 *
 * sites & resources that helped me do this project:
 *
 * Example code from the projects file on vagrant VM
 *
 * This dudes youtube channel https://www.youtube.com/channel/UCwd5VFu4KoJNjkWJZMFJGHQ
 * https://www.tutorialspoint.com/multithreading-in-c#:~:text=A%20multithreaded%20program%20contains%20two,in%20support%20for%20multithreaded%20applications.
 * https://robotics.ee.uwa.edu.au/courses/adv-comp-arch/labs/pthreads/POSIX%20Threads%20Programming.pdf
 *https://computing.llnl.gov/tutorials/pthreads/
 *https://www.traviswpeters.com/cs460-2020-fall/files/intro2threads-andrew-birrell-1989.pdf
 *https://stackoverflow.com/questions/14888027/mutex-lock-threads
 */

// includes (add more as you need them!)
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdbool.h>



// constants

// global data shared by threads (e.g., the "oneway")
#define TO_BRIDGER 0
#define TO_BOZEMAN 1
#define wait 
// global synchronization primitives (e.g., mutexes, condition variables)
//static ints
static int MAXCARS;
// static int NUMCARS;
// static int VERBOSITY;
static int crossedIt;
// static int changeDir;
static int changedDirCount;
static int carsDrivingOneWay = 0;
static bool drivingOneWay;
static volatile int currentDir = TO_BRIDGER;
//static int TO_BRIDGER;
//threading tools for one way safety
pthread_mutex_t crossedLocker; // lock pthread for one way safety
pthread_cond_t crossed; // crossed condition thread
pthread_mutex_t oneWay; // manage locking the traffic
pthread_cond_t oneWayUnlock; //unlock the oneway for next wave of traffic
pthread_mutex_t dirChangeCount; // counting which direction traffic is flowing
pthread_cond_t dirChanged; // 1 or 0 for direction "boolean"
//pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
// typedefs/structs
struct trafficLine{
    pthread_mutex_t mutex;
    pthread_cond_t done;
    int id;
    int direction;
};
typedef struct trafficLine trafficLine_t;
 
char* directionToString(int direction);

char* directionToString(int direction){
    char dir[10];
    if(direction == TO_BOZEMAN){
        strcpy(dir, "Bozeman");
    }else{
        strcpy(dir, "Bridger");
    }

    char * rtn_ptr = dir;
    return rtn_ptr;
}

int arriveOneWay(int carCount, int direction)
{	
	int rc;
	rc = 0;
	
	pthread_mutex_lock(&oneWay);
	printf("car %d has arrived to the one way facing %s\n", carCount, directionToString(direction));
	
	while((carsDrivingOneWay >= MAXCARS) || (currentDir != direction) || drivingOneWay)
	{
		
		if(rc)
		{
			if(carsDrivingOneWay < 1)
			{
				drivingOneWay = false;
				currentDir = (currentDir + 1)%2;
				printf("direction is %d\n" , currentDir);
			}
			else if(changedDirCount >= crossedIt)
			{
				drivingOneWay = true;
				changedDirCount = 0;
			}
		}
		rc = pthread_cond_wait(&oneWayUnlock, &oneWay);

	}
	pthread_mutex_lock(&dirChangeCount); // lock direction change
    changedDirCount++; // update the direction to the other way
    pthread_mutex_unlock(&dirChangeCount); // unlock direction change
    pthread_cond_signal(&dirChanged); // send signal to others
	printf("putting car(s) on the road towards %s\n", directionToString(direction)); // print some garbage
	carsDrivingOneWay++; // add a car to the one way
	pthread_mutex_unlock(&oneWay); // unlock oneway function
	pthread_cond_signal(&oneWayUnlock);//signal it's okay to continue traffic
	return 0;
}

int onOneWay(int carCount, int direction)
{
	
	printf("car %d is on the road going towards %s\n", carCount, directionToString(direction));
	return 0;
}
int exitOneWay(int carCount, int direction)
{
	pthread_mutex_lock(&oneWay);
	printf("car %d has left the construction and is heading towards %s\n", carCount, directionToString(direction));
	carsDrivingOneWay -= 1;
	printf("cars in construction: %d \n", carsDrivingOneWay);
	pthread_mutex_unlock(&oneWay);
	
	pthread_mutex_lock(&crossedLocker);
	crossedIt++;
	pthread_mutex_unlock(&crossedLocker);
	pthread_cond_signal(&crossed);
	pthread_cond_signal(&dirChanged);
	return 0;
}
 // TODO: Implement oneVehicle.
void *oneVehicle(void *arg){
	int carCount;

	pthread_mutex_lock(&(*(trafficLine_t*)(arg)).mutex); //this locks the traffic line moving on the road so other threads (cars) can't run in concurrency
	carCount = (*(trafficLine_t*)(arg)).id; // gets the car number
	int direction = (*(trafficLine_t*)(arg)).direction; // gets direction of cars
	pthread_mutex_unlock(&(*(trafficLine_t*)(arg)).mutex); //unlocks the structure for the next wave of cars
	pthread_cond_signal(&(*(trafficLine_t*)(arg)).done);
	
	//call functions to get this mf on the road
	arriveOneWay(carCount, direction); // car arrives at one way
	onOneWay(carCount, direction); //car is on the one way road
	exitOneWay(carCount, direction); // car has left the one way road
	
	pthread_exit(NULL); // exit threading
	
}
// ////////////////////////////////////////////////////////////////////////// //
//                                   Main                                     //
// ////////////////////////////////////////////////////////////////////////// //

int main(int argc, char* argv[]){
    // Initializes iterator
    int iter;
    int NUMCARS;
    int changeDirCount;
    int RANDSEED;
    int crossed = 0;
    changeDirCount = 0;
    drivingOneWay = false;

    // Helps with generating car ids.
    trafficLine_t trafficLine;
	printf("hi");
    pthread_mutex_init (&trafficLine.mutex, NULL);
    pthread_cond_init (&trafficLine.done, NULL);

    if( argc < 4){
        // Set up values to a feault configuration rather than specified thread count/car max.
        NUMCARS = 10;
        MAXCARS = 3;
        changeDirCount = 15;
        // Default run has a random RANDSEED.
        RANDSEED = time(NULL);
        printf("Not enough arguements, using default values.\n");
    } else{
        // Initializes the maximum about of threads allowed.
        NUMCARS = atoi(argv[1]);
        if(NUMCARS < 1){
            printf("The number of Cars cannot be below 1. Defaulting value to: 1.\n");
            NUMCARS = 1;
        }

        // initializes the maximum threshold of cars the one way can handle at a time.
        MAXCARS = atoi(argv[2]);
        if(MAXCARS < 1){
            printf("Max_Cars value cannot be below 1. Defaulting value to: 1.\n");
            MAXCARS = 1;
        }

        // Initializes the number of cars to generate
        changeDirCount = atoi(argv[3]);
        if(changeDirCount < 1){
            printf("The limit of Cars per direction change cycle can't be less than 1, setting to 1...\n");
            changeDirCount = 1;
        }

        // Sets the random RANDSEED value for generating car's directions.
        RANDSEED = atoi(argv[4]);
    }

    srand(RANDSEED);

    printf("Bridger to Bozeman simulator\n this was no fun \n");

    printf("1) Initializing with %d Cars.\n", NUMCARS);
    printf("2) Maximum # of cars allowed on the one way: %d\n", MAXCARS);
    printf("3) Maximum # of cars per one way cycle: %d\n\n", changeDirCount);

    // Create the threads
    pthread_t threads[NUMCARS];

    // Lock the mutex for car generator
    pthread_mutex_lock(&trafficLine.mutex);



    for(iter = 0; iter < NUMCARS; iter++){
        // Checks the return value of the thread creation to make sure it was able to initialize sucessfully.

        // Changes the current car generator id value
        trafficLine.id = iter;
        // randomly generates from seeded value.
        trafficLine.direction = rand() % 2;

        int thread_creation_check = pthread_create(&threads[iter], NULL, oneVehicle, &trafficLine);

        pthread_cond_wait(&trafficLine.done, &trafficLine.mutex);

        if(thread_creation_check){
            printf("ERROR CREATING THREAD: %d\n", thread_creation_check);
            exit(-1);
        }
    }

    sleep(.01);

    printf("Finished making threads.\n");

    // Join all the threads
    for(iter = 0; iter < NUMCARS; iter++){
        int thread_join_error_check = pthread_join(threads[iter], NULL);
        if(thread_join_error_check){
            printf("ERROR Joining threads.\n");
        }
    }
    printf("Finished Joining Threads.\n");

    // Cleans up
    pthread_mutex_destroy(&trafficLine.mutex);
    pthread_cond_destroy (&trafficLine.done);

    printf("TOTAL CARS CROSSED: %d\n", crossed);
    return 0;
}
