#include <iostream>
#include <unistd.h>
#include <mutex>

#define NBLOCKS 20
#define OBSTACLE 5
#define CHARTED 1
#define UNCHARTED 0

std::mutex p;

class Drone{
private:
	int id;												//drone id
	int status; 										//0 if not delivered, 1 if it did
	int marked_path[NBLOCKS][NBLOCKS] = {0};			//path taken by drone to reach delivery
	void move(int xstep, int ystep);					//movement using manhattan bullshit thingy
	void print_map(char (&map)[NBLOCKS][NBLOCKS]);		//prints the map at each move to display drone movement
	void set_pos(char (&map)[NBLOCKS][NBLOCKS], std::mutex (&mutexes)[NBLOCKS][NBLOCKS], int x, int y, char id);
public:
	int curr_x;
	int curr_y;

	Drone(){} //empty constructor
	
	Drone(int id){
		this->id = id;
		curr_x = 0;
		curr_y = 0;
		status = 0;
	}

	bool deliver(char (&map)[NBLOCKS][NBLOCKS], std::mutex (&mutexes)[NBLOCKS][NBLOCKS], int x, int y, int goal_x, int goal_y);
	void report_back(char (&map)[NBLOCKS][NBLOCKS], std::mutex (&mutexes)[NBLOCKS][NBLOCKS]);	//go back to DCAS

	
};

void Drone::move(int xstep, int ystep){
	curr_x += xstep;
	curr_y += ystep;
}

void Drone::set_pos(char (&map)[NBLOCKS][NBLOCKS], std::mutex (&mutexes)[NBLOCKS][NBLOCKS], int x, int y, char id){
	int dx = x-curr_x;
	int dy = y-curr_y;

	while(1){
		if(mutexes[x][y].try_lock()){
			move(dx, dy);
			if(map[x][y] != 'A' /*&& map[x][y] != 'X'*/){
				map[x][y] = '.';
				map[x][y] = id;
			}
			
			usleep(125000);
			mutexes[x][y].unlock();
			return;
		}
	}
	
}

bool Drone::deliver(char (&map)[NBLOCKS][NBLOCKS], std::mutex (&mutexes)[NBLOCKS][NBLOCKS],int x, int y, int goal_x, int goal_y){
	
	
	if(x == goal_x && y == goal_y){
		status = 1;				//delivery successful
		//std::cout << id << ": " << "(" << x << ", " << y << ")" << std::endl;
		return true;
	}

	if(map[x][y] == '@' || marked_path[x][y] == CHARTED){

		return false;
	}

	//mark block as charted
	marked_path[x][y] = CHARTED;
	
	//update map
	set_pos(map,mutexes, x,y, 'a'+ id);
	//std::cout << id << ": " << "(" << x << ", " << y << ")" << std::endl;


	if (x != 0) // Checks if not on left edge  
        if (deliver(map, mutexes, x-1, y, goal_x, goal_y)) { // Recalls method one to the left
			//move(-1,0);
            return true;
        }
    if (x != NBLOCKS - 1) // Checks if not on right edge
        if (deliver(map, mutexes, x+1, y, goal_x, goal_y)) { // Recalls method one to the right
			//move(1,0);
            return true;
        }
    if (y != 0)  // Checks if not on top edge    
        if (deliver(map, mutexes, x, y-1, goal_x, goal_y)) { // Recalls method one up
			//move(0,-1);
	        return true;
        }
    if (y != NBLOCKS - 1) // Checks if not on bottom edge     
        if (deliver(map, mutexes, x, y+1, goal_x, goal_y)) { // Recalls method one down
			//move(0,1);
            return true;
        }

    //mark block as uncharted
	//marked_path[x][y] = UNCHARTED;
    return false;
}

void Drone::print_map(char (&map)[NBLOCKS][NBLOCKS]){
	/*//delay print and clear
	usleep(50000);
	system("clear");
	//print every block
	for(int i=0; i<NBLOCKS; i++){
		for(int j=0; j<NBLOCKS; j++){
			printf("%3c", map[i][j]);
		}
		printf("%s\n", "");
	}*/
}

void Drone::report_back(char (&map)[NBLOCKS][NBLOCKS], std::mutex (&mutexes)[NBLOCKS][NBLOCKS]){	
	//reset charted path to 0
	for (int i = 0; i < NBLOCKS; i++){
    	for(int j = 0; j < NBLOCKS; j++){
    		marked_path[i][j] = 0;
    	}
    }

    //send drone back to motherbase
	deliver(map, mutexes,curr_x, curr_y,0,0);
}
