#include <stdio.h>
#include <pthread.h>
#include "drone.h"

#define NTHREADS 10

void *thread_function(void *dummyPtr);
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

struct Drones {
	   int drone_id;
	   int clearedForTakeOff;
	   int flightStatus; //if drone is in flight
	   int deliveryStatus; //if drone has delivered
};

int main(int argc, char const *argv[]){
	
	pthread_t thread_id[NTHREADS];
	int i, j;

	for(i=0; i < NTHREADS; i++)
	{
		struct Drones drone, *dronePtr;
		drone.drone_id = i;
		drone.flightStatus = 0;
		drone.clearedForTakeOff = 1;
		drone.deliveryStatus = 0;

		dronePtr = &drone;

		
		pthread_create( &thread_id[i], NULL, thread_function, (void*) dronePtr );
	}

	for(j=0; j < NTHREADS; j++)
	{
		pthread_join( thread_id[j], NULL); 
	}

	return 0;
}


void *thread_function(void *ptr)
{
	
	pthread_mutex_lock( &mutex1 );
	// declare drone ptr and set it to passed argument
	struct Drones *drone;
	drone = (struct Drones *) ptr;
	// access struct variables to do various things
	printf("%i\n", drone->drone_id);
   	pthread_mutex_unlock( &mutex1 );
}