#include <pthread.h>
#include "dcas.hpp"

int main(int argc, char const *argv[])
{
	//initiliaze airport to be occupied
	map[0][0] = 1;
	//create artificial obstacles
	map[3][3] = 5;
	map[5][4] = 5;
	map[6][2] = 5;
	map[7][4] = 5;
	map[7][5] = 5;
	map[7][6] = 5;
	map[8][6] = 5;
	map[9][6] = 5;
	map[9][5] = 5;
	map[9][4] = 5;
	//set delivery point
	map[8][5] = 8;


	Drone drone(1,8,5);

	drone.deliver(map, 0,0);

	//test if drone del,5ivered
	printf("%i", drone.curr_x);
	printf("%i\n", drone.curr_y);
	

	return 0;
}