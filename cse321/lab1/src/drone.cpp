#include <iostream>
#include <unistd.h>
#include <mutex>

#define NBLOCKS 20
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
	bool set_pos(char (&map)[NBLOCKS][NBLOCKS], std::mutex (&mutexes)[NBLOCKS][NBLOCKS], int x, int y, char id);
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

bool Drone::set_pos(char (&map)[NBLOCKS][NBLOCKS], std::mutex (&mutexes)[NBLOCKS][NBLOCKS], int x, int y, char id){
	int dx = x-curr_x;
	int dy = y-curr_y;

	
	if(mutexes[x][y].try_lock()){
		
		if(map[curr_x][curr_y] != 'A'){
			map[curr_x][curr_y] = '.';
		}
		
		move(dx, dy);
		mutexes[curr_x][curr_y].unlock();
		
		if(map[x][y] != 'A'){
			map[x][y] = id;
		}

		usleep(125000);

		return true;
	}

	return false;
	
}

bool Drone::deliver(char (&map)[NBLOCKS][NBLOCKS], std::mutex (&mutexes)[NBLOCKS][NBLOCKS],int x, int y, int goal_x, int goal_y){
	
	
	if(x == goal_x && y == goal_y){
		status = 1;				//delivery successful
		//std::cout << id << ": " << "(" << x << ", " << y << ")" << std::endl;
		return set_pos(map,mutexes, x,y, 'a'+ id);
	}
	if(map[x][y] == '@' || marked_path[x][y] == CHARTED){

		return false;
	}

	//mark block as charted
	marked_path[x][y] = CHARTED;
		


	if (x != 0) // Checks if not on left edge  
        if (deliver(map, mutexes, x-1, y, goal_x, goal_y)) { // Recalls method one to the left
            return set_pos(map,mutexes, x-1,y, 'a'+ id);
        }
    if (x != NBLOCKS - 1) // Checks if not on right edge
        if (deliver(map, mutexes, x+1, y, goal_x, goal_y)) { // Recalls method one to the right
            return set_pos(map,mutexes, x+1,y, 'a'+ id);
        }
    if (y != 0)  // Checks if not on top edge    
        if (deliver(map, mutexes, x, y-1, goal_x, goal_y)) { // Recalls method one up
	        return set_pos(map,mutexes, x,y-1, 'a'+ id);
        }
    if (y != NBLOCKS - 1) // Checks if not on bottom edge     
        if (deliver(map, mutexes, x, y+1, goal_x, goal_y)) { // Recalls method one down
            return set_pos(map,mutexes, x,y+1, 'a'+ id);
        }

    
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

    usleep(125000);
    //send drone back to motherbase
	deliver(map, mutexes,curr_x, curr_y,0,0);
}
