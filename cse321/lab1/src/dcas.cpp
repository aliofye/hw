#include "drone.cpp"
#include <thread>
#include <stdlib.h>

#define NDRONES 10

char map[NBLOCKS][NBLOCKS];
std::mutex mutexes[NBLOCKS][NBLOCKS];
std::thread threads[NDRONES];
Drone drones[NDRONES];
bool refresh = true;

void init_map(char (&map)[NBLOCKS][NBLOCKS]){
	for(int i=0; i<NBLOCKS; i++){
		for(int j=0; j<NBLOCKS; j++){
			map[i][j] = '.';
		}
	}
}

void launch_drone(int *id)
{
       	int x = std::rand() % NBLOCKS + 1;
       	int y = std::rand() % NBLOCKS + 1;

       	//set delivery point
		map[x][y] = 'X';
       	
       	drones[*id].deliver(map, mutexes, 0, 0, x, y);
       	//UNCOMMENT LINE BELOW TO SEE DRONES GO BACK TO AIRPORT
        drones[*id].report_back(map, mutexes);
}

void print_map(){
	//delay print and clear
	system("clear");
	//print every block
	for(int i=0; i<NBLOCKS; i++){
		for(int j=0; j<NBLOCKS; j++){
			printf("%3c", map[i][j]);
		}
		printf("%s\n", "");
	}
}

void display_map(){
	while(refresh){
		usleep(125000);
		print_map();
	}
}

int main(int argc, char const *argv[])
{

	init_map(map);

	std::thread print_thread(display_map);

	//initiliaze airport to be A
	map[0][0] = 'A';
	
	//create artificial obstacles
	for(int i=0; i<NDRONES; i++){
		
		int x = std::rand() % NBLOCKS + 1;
       	int y = std::rand() % NBLOCKS + 1;

       	map[x][y] = '@';
	}

	//set up drones
	for(int i=0; i<NDRONES; i++){
		Drone drone(i);
		drones[i] = drone;
	}

	//set up threads
	for(int i=0; i<NDRONES; i++){
		threads[i] = std::thread(launch_drone,&i);
		usleep(125000);
	}


	// join threads
	for(int i=0; i<NDRONES; i++){
		if(threads[i].joinable())
			threads[i].join();
	}

	if(print_thread.joinable()){
		print_thread.join();
	}



	refresh = false;

	//check final locations of drones
	printf("%s\n", "Compare final steps above, to final position below!");
	for(int i=0; i<NDRONES; i++){
		std::cout << i << ": " << drones[i].curr_x << ", " << drones[i].curr_y << std::endl;
	}
	return 0;
}