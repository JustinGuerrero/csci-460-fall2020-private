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

// typedefs/structs
typedef struct{
    pthread_mutex_t mutex;
    pthread_cond_t done;
    int id;
    int direction;
}trafficLine_t;

// constants

// global data shared by threads (e.g., the "oneway")
#define TO_BRIDGER 0
#define TO_BOZEMAN 1
#define wait 
// global synchronization primitives (e.g., mutexes, condition variables)
//static ints
static int MAXCARS;
// static int NUMCARS;
static int RADNSEED;
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

 

int arriveOneWay(int carCount, int direction)
{	
	int rc;
	rc = 0;
	
	pthread_mutex_lock(&oneWay);
	printf("car %d is on the one way facing %d", carCount, direction);
	
	while((carsDrivingOneWay >= MAXCARS) || (currentDir != direction) || drivingOneWay)
	{
		
		if(rc)
		{
			if(carsDrivingOneWay < 1)
			{
				drivingOneWay = false;
				currentDir = (currentDir + 1)%2;
				printf("direction is %d" , currentDir);
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
	printf("putting car on the road towards %d\n", direction); // print some garbage
	carsDrivingOneWay++; // add a car to the one way
	pthread_mutex_unlock(&oneWay); // unlock oneway function
	pthread_cond_signal(&oneWayUnlock);//signal it's okay to continue traffic
	return 0;
}

int onOneWay(int carCount, int direction)
{
	
	printf("car %d is on the road going towards %d", carCount, direction);
	return 0;
}
int exitOneWay(int carCount, int direction)
{
	pthread_mutex_lock(&oneWay);
	printf("car %d has left the construction and is heading towards %d", carCount, direction);
	carsDrivingOneWay -= 1;
	printf("cars in construction: %d ", carsDrivingOneWay);
	pthread_mutex_unlock(&oneWay);
	
	pthread_mutex_lock(&crossedLocker);
	crossedIt++;
	pthread_mutex_unlock(&crossedLocker);
	
	pthread_cond_signal(&dirChanged);
	return 0;
}
 // TODO: Implement oneVehicle.
void *oneVehicle(void *arg){
	int carCount;
	printf("in oneVehicle");

	pthread_mutex_lock(&(*(trafficLine_t*)(arg)).mutex); //this locks the traffic line moving on the road so other threads (cars) can't run in concurrency
	carCount = (*(trafficLine_t*)(arg)).id; // gets the car number
	int direction = (*(trafficLine_t*)(arg)).direction; // gets direction of cars
	pthread_mutex_unlock(&(*(trafficLine_t*)(arg)).mutex); //unlocks the structure for the next wave of cars
	
	
	//call functions to get this mf on the road
	arriveOneWay(carCount, direction); // car arrives at one way
	onOneWay(carCount, direction); //car is on the one way road
	exitOneWay(carCount, direction); // car has left the one way road
	
	pthread_exit(NULL); // exit threading
	
}
// ////////////////////////////////////////////////////////////////////////// //
//                                   Main                                     //
// ////////////////////////////////////////////////////////////////////////// //

int main(int argc, char* argv[]) {
	int iterator; //did i spell this right
	int NUMCARS;
	int RANDSEED;
	int VERBOSITY;
	int MAXCARS;
	int r = rand() % 20;
	crossedIt = 0;
	changedDirCount = 0;
	drivingOneWay = false;
	
	trafficLine_t trafficLine;
	pthread_mutex_init(&trafficLine.mutex, NULL);
	pthread_cond_init(&trafficLine.done, NULL);
	
	if(argc<2)
	{
		NUMCARS = 15;
		MAXCARS = 3;
		VERBOSITY = 0;
		RANDSEED = r;
		
	}
	else
	{
		NUMCARS = atoi(argv[1]);
		MAXCARS = atoi(argv[2]);
		RADNSEED = atoi(argv[3]);
		VERBOSITY = atoi(argv[4]);
	}
	//create threads and some print statements
	    // TODO: main loop that drives the simulation
    // In each iteration of the loop...
	
	
	printf("Bridger to Bozeman traffic simulation\n");
	printf("this was a horrible assignment\n");
	printf("maximum number of cars allowed on the one way %d  :\n ", MAXCARS);
	
	    //   - create a thread (car) that starts running "oneVehicle"
	pthread_t threads[NUMCARS];
	pthread_mutex_lock(&trafficLine.mutex);
	//threads for each car
	for(iterator = 0; iterator<NUMCARS; iterator++)
	{
		trafficLine.id = iterator;
		trafficLine.direction = rand() %2;
		int thread_creation = pthread_create(&threads[iterator], NULL, oneVehicle, &trafficLine);
		if(thread_creation)
		{
			printf("couldn't create thread %d\n", thread_creation);
			exit(-1);
		}
	}
		sleep(.01);
		printf("threads are made\n");
	
	
		//creating joins on threads 
			// TODO: main loop that drives the simulation
		// In each iteration of the loop...
		for(iterator=0; iterator < NUMCARS; iterator++)
		{
			printf("we are here");
			int thread_err_check = pthread_join(threads[iterator],NULL);
			if(thread_err_check)
			{
				printf("couldn't join threads");
			}
		}
		// TODO: wait for car threads to finish & cleanup.
		pthread_mutex_destroy(&trafficLine.mutex);
		printf("we destroyed");
		pthread_cond_destroy (&trafficLine.done);
		printf("we con destroyed");

		printf("TOTAL CARS CROSSED: %d\n", crossedIt);
    return 0;


   
}