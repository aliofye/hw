#include <iostream>
#include <unistd.h>

#define NBLOCKS 10
#define OBSTACLE 5
#define CHARTED 1
#define UNCHARTED 0

class Drone{
private:
	int id;
	int end_x;
	int end_y;
	int marked_path[NBLOCKS][NBLOCKS] = {0};
	void move(int xstep, int ystep);
	void print_map(int (&map)[NBLOCKS][NBLOCKS]);
public:
	int curr_x;
	int curr_y;

	Drone(){} //empty constructor
	
	Drone(int id, int end_x, int end_y){
		this->id = id;
		this->end_x = end_x;
		this->end_y = end_y;
		curr_x = 0;
		curr_y = 0;
	}

	bool deliver(int (&map)[NBLOCKS][NBLOCKS], int x, int y);
	
};

void Drone::move(int xstep, int ystep){
	
	curr_x += xstep;
	curr_y += ystep;
}

bool Drone::deliver(int (&map)[NBLOCKS][NBLOCKS], int x, int y){
	
	if(x == end_x && y == end_y){
		return true;
	}

	if(map[x][y] == OBSTACLE || marked_path[x][y] == CHARTED){

		return false;
	}

	marked_path[x][y] = CHARTED;
	map[x][y] = 1;
	print_map(map);
	map[x][y] = 0;

	if (x != 0) // Checks if not on left edge  
        if (deliver(map, x-1, y)) { // Recalls method one to the left
			move(-1,0);
            return true;
        }
    if (x != NBLOCKS - 1) // Checks if not on right edge
        if (deliver(map, x+1, y)) { // Recalls method one to the right
			move(1,0);
            return true;
        }
    if (y != 0)  // Checks if not on top edge    
        if (deliver(map, x, y-1)) { // Recalls method one up
			move(0,-1);
	        return true;
        }
    if (y != NBLOCKS - 1) // Checks if not on bottom edge     
        if (deliver(map, x, y+1)) { // Recalls method one down
			move(0,1);
            return true;
        }

    return false;
}

void Drone::print_map(int (&map)[NBLOCKS][NBLOCKS]){
	usleep(100000);
	system("clear");
	for(int i=0; i<NBLOCKS; i++){
		for(int j=0; j<NBLOCKS; j++){
			printf("%3i", map[i][j]);
		}
		printf("%s\n", "");
	}
}
