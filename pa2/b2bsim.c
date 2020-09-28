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
#define wait .1
// global synchronization primitives (e.g., mutexes, condition variables)
//static ints
static int MAXCARS;
static int NUMCARS;
static int RADNSEED;
static int VERBOSITY;
static int crossedIt;
static int changeDir;
static int carsDrivingOneWay = 0;
//static int TO_BRIDGER;
//threading tools for one way safety
pthread_mutex_t crossedLocker; // lock pthread for one way safety
pthread_cond_t crossed; // crossed condition thread
pthread_mutex_t oneWay; // manage the traffic
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
	
}


/**
 * TODO: Implement oneVehicle.
 *
 * This is the main function of a car.
 *
 * 1. It simulates a car driving up to one side of the one-way.
 *    The car waits until it is okay to pass.
 *    => arriveOneWay()
 *
 * 2. Once it is safe to pass, the car proceeds onto the oneway and prints the current state of the simulation.
 *    (It is nice to simulate some time passing here - perhaps with a small "sleep" - cars take time to drive!)
 *    => onOneWay()
 *
 * 3. Finally, the thread (car) exits the one-way and finishes.
 *    => exitOneWay()
 */
// WRITE CODE HERE. (DELETE THIS COMMENT)

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