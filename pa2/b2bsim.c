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
static int NUMCARS;
static int RADNSEED;
static int VERBOSITY;
static int crossedIt;
static int changeDir;
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

 
 // TODO: Implement oneVehicle.
void *oneVehicle(void *arg){
	int carCount;
	
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
int arriveOneWay(int carCount, int direction)
{	

	struct timespec timeLeftWaiting;
	struct timeval theTime;
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
			rc = pthread_cond_timedwait(&oneWayUnlock, &oneWay, &timeLeftWaiting);

	}
	pthread_mutex_lock(&changeDir); // lock direction change
    changedDirCount++; // update the direction to the other way
    pthread_mutex_unlock(&changeDir); // unlock direction change
    pthread_cond_signal(&dirChanged); // send signal to others
	printf("putting car on the road towards %s\n", direction); // print some garbage
	carsDrivingOneWay++; // add a car to the one way
	pthread_mutex_unlock(&oneWay); // unlock oneway function
	pthread_cond_signal(&oneWayUnlock);//signal it's okay to continue traffic
}

int onOneWay(int carCount, int direction)
{
	wait(1);
	printf("car %d is on the road going towards %d", carCount, direction);
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
}
// ////////////////////////////////////////////////////////////////////////// //
//                                   Main                                     //
// ////////////////////////////////////////////////////////////////////////// //

int main(int argc, char* argv[]) {

	
    // TODO: handle input arguments (print help statement if needed)

    // TODO: initializations for simulation

    // TODO: main loop that drives the simulation
    // In each iteration of the loop...
    //   - initalize/update any info for keeping track of threads (cars)
    //   - create a thread (car) that starts running "oneVehicle"

    // TODO: wait for car threads to finish & cleanup.

    // TODO: display final state of your oneway simulation before exiting.

    return 0;
}