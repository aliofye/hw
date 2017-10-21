#include <iostream>
#include <pthread.h>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <queue>
#include <string>
#include <semaphore.h>

using namespace std;
//Global Variables
const int board_size = 42;
const int num_drones = 4;
char board[board_size][board_size];
sem_t sem_board[board_size][board_size];
volatile int drone_turn = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
queue<int> available_drones;
int airport_x;
int airport_y;
bool timer_bool = true;
// drone struct
struct drone
{
    int current_x;
    int current_y;
    int final_x;
    int final_y;
    int id;
    char img;
    char dest_img;
    char curr_pos_prev_img;

};




// function declarations
void deployDroneFromAirport(drone *drone_arg);
void actuallyMoveDrone(drone *drone_arg, int potential_x, int potential_y);
void printBoard();
void placeAirport();
void moveDrone( drone *drone_arg);
void printDrone( drone *drone_arg);
void placeDroneOnBoard(drone *drone_arg);
void instantiateBoard();
void instantiateSemBoard();
void *activateDrone(void *drone_arg);
void *activateTimer(void *unused);

int main(){

    int rc;
    instantiateBoard();
    instantiateSemBoard();
    string input;
    int demo;
    char temp;
    bool prompt_flag = true;
    // Explain program and promt user for input
    while (prompt_flag){
        printf ("Welcome to DCAS simulator\nPlease select a drone case to run by pressing a number then hit the enter key\n");
        printf ("[0] - Run the simulator spawning 10 drones at random locations\n");
        printf ("[1] - Run the 4 drone collision simulator\n");
        printf ("[2] - Run the 2 drone vertical collision simulator\n");
        printf ("[3] - Run the simulator deploying drones from an airport 'X' to deliver packages\n");
        printf ("[4] - Run the simulator to continuously deploy the drones (MAX 10) from the airport 'X' to deliver packages\n");
        printf ("Press the [ctrl] AND [c] keys together to exit anytime during the simulations\n");
        cin >> input;
        temp = input.at(0);
        if (((temp < 53)&&(temp >= 48))&&(input.length() == 1)){
            prompt_flag = false;
        }
    }

    demo = temp - 48;
    srand (time(NULL));
    // run the case the user specified
    switch(demo){
        case 0:
            
            pthread_t demo0_threads[10];
            drone drone_data[10];
            placeAirport();
            pthread_t demo0_time_thread[1];
            rc = pthread_create(&demo0_time_thread[0],NULL, activateTimer, NULL);

            for (int i = 0; i<10; i++){
                char demo0_drone_img = 'A' + i;             
                char demo0_dest_img = '0' + i;
                drone_data[i].img = demo0_drone_img;
                drone_data[i].dest_img = demo0_dest_img;
                drone_data[i].curr_pos_prev_img = ' ';
                drone_data[i].id = i;
                placeDroneOnBoard(&drone_data[i]);
                // printDrone(&drone_data[i]);
                rc = pthread_create(&demo0_threads[i], NULL, activateDrone, (void *) &drone_data[i]);
                usleep(500000);
            }

            for (int i = 0; i<10; i++){
                rc = pthread_join(demo0_threads[i], NULL);
            }
            timer_bool = false;
            rc = pthread_join(demo0_time_thread[0],NULL);
            break;
        case 1:
            drone drone_a;
            drone *drone_0;
            drone_0 = &drone_a;
            (*drone_0).current_x = 7;
            (*drone_0).current_y = 20;
            (*drone_0).img = 'A';
            (*drone_0).dest_img = '0';
            (*drone_0).final_x = 25;
            (*drone_0).final_y = 20;
            (*drone_0).id = 0;
            drone_0->curr_pos_prev_img = ' ';
            board[(*drone_0).current_x][(*drone_0).current_y] = (*drone_0).img;
            board[(*drone_0).final_x][(*drone_0).final_y] = (*drone_0).dest_img;
            sem_wait(&sem_board[(*drone_0).current_x][(*drone_0).current_y]);

            drone drone_b;
            drone *drone_1;
            drone_1 = &drone_b;
            (*drone_1).current_x = 22;
            (*drone_1).current_y = 34;
            (*drone_1).img = 'B';
            (*drone_1).dest_img = '1';
            (*drone_1).final_x = 22;
            (*drone_1).final_y = 16;
            (*drone_1).id = 1;
            drone_1->curr_pos_prev_img = ' ';
            board[(*drone_1).current_x][(*drone_1).current_y] = (*drone_1).img;
            board[(*drone_1).final_x][(*drone_1).final_y] = (*drone_1).dest_img;
            sem_wait(&sem_board[(*drone_1).current_x][(*drone_1).current_y]);

            drone drone_c;
            drone *drone_2;
            drone_2 = &drone_c;
            (*drone_2).current_x = 36;
            (*drone_2).current_y = 19;
            (*drone_2).img = 'C';
            (*drone_2).dest_img = '2';
            (*drone_2).final_x = 18;
            (*drone_2).final_y = 19;
            (*drone_2).id = 2;
            drone_2->curr_pos_prev_img = ' ';
            board[(*drone_2).current_x][(*drone_2).current_y] = (*drone_2).img;
            board[(*drone_2).final_x][(*drone_2).final_y] = (*drone_2).dest_img;
            sem_wait(&sem_board[(*drone_2).current_x][(*drone_2).current_y]);

            drone drone_d;
            drone *drone_3;
            drone_3 = &drone_d;
            (*drone_3).current_x = 21;
            (*drone_3).current_y = 5;
            (*drone_3).img = 'D';
            (*drone_3).dest_img = '3';
            (*drone_3).final_x = 21;
            (*drone_3).final_y = 23;
            (*drone_3).id = 3;
            drone_3->curr_pos_prev_img = ' ';
            board[(*drone_3).current_x][(*drone_3).current_y] = (*drone_3).img;
            board[(*drone_3).final_x][(*drone_3).final_y] = (*drone_3).dest_img;
            sem_wait(&sem_board[(*drone_3).current_x][(*drone_3).current_y]);

            placeAirport();
            printBoard();
            pthread_t demo1_threads[4];
            pthread_t demo1_time_thread[1];

            rc = pthread_create(&demo1_time_thread[0],NULL, activateTimer, NULL);
            rc = pthread_create(&demo1_threads[0], NULL, activateDrone, (void *)drone_0);
            usleep(500000);
            rc = pthread_create(&demo1_threads[1], NULL, activateDrone, (void *)drone_1);
            usleep(500000);
            rc = pthread_create(&demo1_threads[2], NULL, activateDrone, (void *)drone_2);
            usleep(500000);
            rc = pthread_create(&demo1_threads[3], NULL, activateDrone, (void *)drone_3);
            rc = pthread_join(demo1_threads[0],NULL);
            rc = pthread_join(demo1_threads[1],NULL);
            rc = pthread_join(demo1_threads[2],NULL);
            rc = pthread_join(demo1_threads[3],NULL);
            timer_bool = false;
            rc = pthread_join(demo1_time_thread[0],NULL);

            break;
        
        case 2:
            drone drone_e;
            drone *drone_4;
            drone_4 = &drone_e;
            (*drone_4).current_x = 1;
            (*drone_4).current_y = 20;
            (*drone_4).img = 'E';
            (*drone_4).dest_img = '4';
            (*drone_4).final_x = 30;
            (*drone_4).final_y = 20;
            (*drone_4).id = 4;
            drone_4->curr_pos_prev_img = ' ';
            board[(*drone_4).current_x][(*drone_4).current_y] = (*drone_4).img;
            board[(*drone_4).final_x][(*drone_4).final_y] = (*drone_4).dest_img;
            sem_wait(&sem_board[(*drone_4).current_x][(*drone_4).current_y]);

            drone drone_f;
            drone *drone_5;
            drone_5 = &drone_f;
            (*drone_5).current_x = 40;
            (*drone_5).current_y = 20;
            (*drone_5).img = 'F';
            (*drone_5).dest_img = '5';
            (*drone_5).final_x = 10;
            (*drone_5).final_y = 20;
            (*drone_5).id = 5;
            drone_5->curr_pos_prev_img = ' ';
            board[(*drone_5).current_x][(*drone_5).current_y] = (*drone_5).img;
            board[(*drone_5).final_x][(*drone_5).final_y] = (*drone_5).dest_img;
            sem_wait(&sem_board[(*drone_5).current_x][(*drone_5).current_y]);

            placeAirport();
            printBoard();
            pthread_t demo2_threads[2];
            pthread_t demo2_time_thread[1];

            rc = pthread_create(&demo2_time_thread[0],NULL, activateTimer, NULL);
            rc = pthread_create(&demo2_threads[0], NULL, activateDrone, (void *)drone_4);
            usleep(500000);
            rc = pthread_create(&demo2_threads[1], NULL, activateDrone, (void *)drone_5);
            rc = pthread_join(demo2_threads[0],NULL);
            rc = pthread_join(demo2_threads[1],NULL);
            timer_bool = false;
            rc = pthread_join(demo2_time_thread[0],NULL);

            break;
        case 3:
            pthread_t demo3_threads[10];
            drone demo3_drone_data[10];
            placeAirport();
            printBoard();
            usleep(1000000);
            pthread_t demo3_time_thread[1];

            rc = pthread_create(&demo3_time_thread[0],NULL, activateTimer, NULL);
            for (int i = 0; i<10; i++){
                usleep(500000);
                char demo3_drone_img = 'A' + i;
                char demo3_dest_img = '0' + i;
                demo3_drone_data[i].img = demo3_drone_img;
                demo3_drone_data[i].dest_img = demo3_dest_img;
                demo3_drone_data[i].id = i;
                deployDroneFromAirport(&demo3_drone_data[i]);
                rc = pthread_create(&demo3_threads[i], NULL, activateDrone, (void *) &demo3_drone_data[i]);
            }

            for (int i = 0; i<10; i++){
                rc = pthread_join(demo3_threads[i], NULL);
            }
            timer_bool = false;
            rc = pthread_join(demo3_time_thread[0],NULL);
            break;

        case 4:
            pthread_t demo4_threads[10];
            drone demo4_drone_data[10];
            placeAirport();
            printBoard();
            usleep(1000000);
            for (int i = 0; i<10; i++){
                demo4_drone_data[i].id = i;
                available_drones.push(i);
            }

            pthread_t demo4_time_thread[1];
            rc = pthread_create(&demo4_time_thread[0],NULL, activateTimer, NULL);
            while(true){
                if (!available_drones.empty()){
                    int drone_id = available_drones.front();
                    available_drones.pop();
                    usleep(1000000);
                    char demo4_drone_img = 'A' +drone_id;
                    char demo4_dest_img = '0' + drone_id;
                    demo4_drone_data[drone_id].img = demo4_drone_img;
                    demo4_drone_data[drone_id].dest_img = demo4_dest_img;
                    deployDroneFromAirport(&demo4_drone_data[drone_id]);
                    rc = pthread_create(&demo4_threads[drone_id], NULL, activateDrone, (void *) &demo4_drone_data[drone_id]);
                }

            }
            timer_bool = false;
            rc = pthread_join(demo4_time_thread[0],NULL);
            break;
    }

    printBoard();
    printf("completed");
    return 0;
}

// timer thread method that prints out the board every 0.25 sec
void *activateTimer(void *unused){
    while(timer_bool){
        usleep(125000);
        printBoard();
    }
        pthread_exit(NULL);
}

// instantaiate the 2d semaphore array
void instantiateSemBoard(){
    for (int i =0; i<board_size; i++){
        sem_init(&sem_board[(board_size - board_size)][i], 0, 0);
    }
    for (int i =0; i<board_size; i++){
        sem_init(&sem_board[(board_size - 1)][i], 0, 0);
    }
    for (int x = 1; x < (board_size - 1); x++){
        sem_init(&sem_board[x][board_size - board_size], 0, 0);
        for (int y = 1; y < (board_size - 1); y++){
            sem_init(&sem_board[x][y], 0, 1);
        }
        sem_init(&sem_board[x][(board_size - 1)], 0, 0);
    }
}

// randomly place an airport on the ascii board
void placeAirport(){
    bool airport_loc_set = false;
    while(!airport_loc_set){
        airport_x = rand() % 40 + 1;
        airport_y = rand() % 40 + 1;
        if (board[airport_x][airport_y] == ' '){
            airport_loc_set = true;
            board[airport_x][airport_y] = 'X';
        }
    }
}

// place drone on top of the airport if the area is free (semaphore unlocked) else wait till its free
// also assign the drone a random delivery location
void deployDroneFromAirport(drone *drone_arg){
    bool airport_free = false;
    bool drone_dest_set = false;

    sem_wait(&sem_board[airport_x][airport_y]);
    drone_arg->current_x = airport_x;
    drone_arg->current_y = airport_y;
    drone_arg->curr_pos_prev_img = 'X';
    board[airport_x][airport_y] = drone_arg->img;


    while (!drone_dest_set){
        int drone_dest_x = rand() % 40 + 1;
        int drone_dest_y = rand() % 40 + 1;
        if (board[drone_dest_x][drone_dest_y] == ' '){
            drone_dest_set = true;
            drone_arg->final_x = drone_dest_x;
            drone_arg->final_y = drone_dest_y;
            board[drone_dest_x][drone_dest_y] = drone_arg->dest_img;
        }
    }
}


// randomly place drones on random locations on the board and lock the corresponding loactions on the semaphore board
// also assign the drone a random delivery location
void placeDroneOnBoard(drone *drone_arg){
    bool drone_loc_set = false;
    bool drone_dest_set = false;
    while (!drone_loc_set){
        int drone_loc_x = rand() % 40 + 1;
        int drone_loc_y = rand() % 40 + 1;
        if (board[drone_loc_x][drone_loc_y] == ' '){
            drone_loc_set = true;
            drone_arg->current_x = drone_loc_x;
            drone_arg->current_y = drone_loc_y;
            board[drone_loc_x][drone_loc_y] = drone_arg->img;
            sem_wait(&sem_board[drone_loc_x][drone_loc_y]);
        }
    }

    while (!drone_dest_set){
        int drone_dest_x = rand() % 40 + 1;
        int drone_dest_y = rand() % 40 + 1;
        if (board[drone_dest_x][drone_dest_y] == ' '){
            drone_dest_set = true;
            drone_arg->final_x = drone_dest_x;
            drone_arg->final_y = drone_dest_y;
            board[drone_dest_x][drone_dest_y] = drone_arg->dest_img;
        }
    }


}

// this method describes the logic for handling collisions and drone movements
void moveDrone(drone *drone_arg){

    drone *cur_moving_drone = (drone *) drone_arg;
    int drone_current_x = drone_arg->current_x;
    int drone_current_y = drone_arg->current_y;
    int drone_final_x = drone_arg->final_x;
    int drone_final_y = drone_arg->final_y;
    int drone_potential_x;
    int drone_potential_y;
    char drone_char = drone_arg->img;
    char dest_char = drone_arg->dest_img;
    // srand (time(NULL));
    int dir = rand() % 2;

    //start with x dir
    if (dir == 0){
        // x arith
        if (drone_current_x < drone_final_x){
            drone_potential_x = drone_current_x + 1;
        }
        else if(drone_current_x > drone_final_x){
            drone_potential_x = drone_current_x - 1;
        }
        else{
            drone_potential_x = drone_current_x;
        }
        //do y
        if (drone_potential_x == drone_current_x){
            // y arith
            if (drone_current_y < drone_final_y){
                drone_potential_y = drone_current_y + 1;
            }
            else if(drone_current_y > drone_final_y){
                drone_potential_y = drone_current_y - 1;
            }
            else{
                drone_potential_y = drone_current_y;
            }

            if (drone_potential_y == drone_current_y){
                //do nothing?
            }
            else{
                int sem_ret = sem_trywait(&sem_board[drone_current_x][drone_potential_y]);
                if (sem_ret == 0){
                    actuallyMoveDrone(cur_moving_drone, drone_current_x, drone_potential_y);
                }
                else{
                    sem_ret = sem_trywait(&sem_board[drone_current_x+1][drone_current_y]);
                    if (sem_ret == 0){
                        actuallyMoveDrone(cur_moving_drone, (drone_current_x + 1), drone_current_y);
                    }
                    else{
                        sem_ret = sem_trywait(&sem_board[drone_current_x-1][drone_current_y]);
                        if (sem_ret == 0){
                            actuallyMoveDrone(cur_moving_drone, (drone_current_x - 1), drone_current_y);
                        }
                        else{
                            sem_ret = sem_trywait(&sem_board[drone_current_x][drone_current_y-1]);
                            if (sem_ret == 0){
                                actuallyMoveDrone(cur_moving_drone, drone_current_x, (drone_current_y - 1));
                            }
                            else{
                                sem_ret = sem_trywait(&sem_board[drone_current_x][drone_current_y+1]);
                                if (sem_ret == 0){
                                    actuallyMoveDrone(cur_moving_drone, drone_current_x, (drone_current_y + 1));
                                }
                                else{
                                }
                            }
                        }
                    }
                }           
            }
        }
        //do x
        else{       
            int sem_ret = sem_trywait(&sem_board[drone_potential_x][drone_current_y]);
            if (sem_ret == 0){
                actuallyMoveDrone(cur_moving_drone, drone_potential_x, drone_current_y);
            }
            else{
                sem_ret = sem_trywait(&sem_board[drone_current_x][drone_current_y - 1]);
                if (sem_ret == 0){
                    actuallyMoveDrone(cur_moving_drone, drone_current_x, (drone_current_y-1));
                }
                else{
                    sem_ret = sem_trywait(&sem_board[drone_current_x][drone_current_y + 1]);
                    if (sem_ret == 0){
                        actuallyMoveDrone(cur_moving_drone, drone_current_x, (drone_current_y+1));
                    }
                    else{
                        sem_ret = sem_trywait(&sem_board[drone_current_x-1][drone_current_y]);
                        if (sem_ret == 0){
                            actuallyMoveDrone(cur_moving_drone, (drone_current_x-1), drone_current_y);
                        }
                        else{
                            sem_ret = sem_trywait(&sem_board[drone_current_x][drone_current_y+1]);
                            if (sem_ret == 0){
                                actuallyMoveDrone(cur_moving_drone, (drone_current_x+1), drone_current_y);
                            }
                            else{
                            }
                        }
                    }
                }
            }
        }
    }

    //start with y dir
    else{
        // y arith
        if (drone_current_y < drone_final_y){
            drone_potential_y = drone_current_y + 1;
        }
        else if(drone_current_y > drone_final_y){
            drone_potential_y = drone_current_y - 1;
        }
        else{
            drone_potential_y = drone_current_y;
        }

        //do x
        if (drone_potential_y == drone_current_y){
            // y arith
            if (drone_current_x < drone_final_x){
                drone_potential_x = drone_current_x + 1;
            }
            else if(drone_current_x > drone_final_x){
                drone_potential_x = drone_current_x - 1;
            }
            else{
                drone_potential_x = drone_current_x;
            }

            if (drone_potential_x == drone_current_x){
                //do nothing?
            }

            else{   
                int sem_ret = sem_trywait(&sem_board[drone_potential_x][drone_current_y]);
                if (sem_ret == 0){
                    actuallyMoveDrone(cur_moving_drone, drone_potential_x, drone_current_y);
                }
                else{
                    sem_ret = sem_trywait(&sem_board[drone_current_x][drone_current_y - 1]);
                    if (sem_ret == 0){
                        actuallyMoveDrone(cur_moving_drone, drone_current_x, (drone_current_y-1));
                    }
                    else{
                        sem_ret = sem_trywait(&sem_board[drone_current_x][drone_current_y + 1]);
                        if (sem_ret == 0){
                            actuallyMoveDrone(cur_moving_drone, drone_current_x, (drone_current_y+1));
                        }
                        else{
                            sem_ret = sem_trywait(&sem_board[drone_current_x-1][drone_current_y]);
                            if (sem_ret == 0){
                                actuallyMoveDrone(cur_moving_drone, (drone_current_x-1), drone_current_y);
                            }
                            else{
                                sem_ret = sem_trywait(&sem_board[drone_current_x][drone_current_y+1]);
                                if (sem_ret == 0){
                                    actuallyMoveDrone(cur_moving_drone, (drone_current_x+1), drone_current_y);
                                }
                                else{
                                }
                            }
                        }
                    }
                }           
            }
        }
        //do y
        else{
            int sem_ret = sem_trywait(&sem_board[drone_current_x][drone_potential_y]);
            if (sem_ret == 0){
                actuallyMoveDrone(cur_moving_drone, drone_current_x, drone_potential_y);
            }
            else{
                sem_ret = sem_trywait(&sem_board[drone_current_x+1][drone_current_y]);
                if (sem_ret == 0){
                    actuallyMoveDrone(cur_moving_drone, (drone_current_x + 1), drone_current_y);
                }
                else{
                    sem_ret = sem_trywait(&sem_board[drone_current_x-1][drone_current_y]);
                    if (sem_ret == 0){
                        actuallyMoveDrone(cur_moving_drone, (drone_current_x - 1), drone_current_y);
                    }
                    else{
                        sem_ret = sem_trywait(&sem_board[drone_current_x][drone_current_y-1]);
                        if (sem_ret == 0){
                            actuallyMoveDrone(cur_moving_drone, drone_current_x, (drone_current_y - 1));
                        }
                        else{
                            sem_ret = sem_trywait(&sem_board[drone_current_x][drone_current_y+1]);
                            if (sem_ret == 0){
                                actuallyMoveDrone(cur_moving_drone, drone_current_x, (drone_current_y + 1));
                            }
                            else{
                            }
                        }
                    }
                }
            }
        }       
    }
}

// the actual assignments, semaphore unlocks and the changing of drone locations on the ascii board and semaphore board
void actuallyMoveDrone(drone *drone_arg, int potential_x, int potential_y){
    board[drone_arg->current_x][drone_arg->current_y] = drone_arg->curr_pos_prev_img;
    sem_post(&sem_board[drone_arg->current_x][drone_arg->current_y]);
    drone_arg->curr_pos_prev_img = board[potential_x][potential_y];
    board[potential_x][potential_y] = drone_arg->img;
    drone_arg->current_x = potential_x;
    drone_arg->current_y = potential_y;
}

// the drone thread method that runs during the drones lifetime of delivering the package and returning to the airport
void *activateDrone(void *drone_arg){
    drone *cur_drone = (drone *)drone_arg;
    int cur_drone_id = cur_drone->id; 

    srand(time(NULL));
    while (((cur_drone->current_x)!=(cur_drone->final_x)) || ((cur_drone->current_y)!=(cur_drone->final_y))){
        moveDrone(cur_drone);
        // srand (time(NULL));
        int delay = rand() % 4 + 1;
        delay = delay * 250000;
        // printf("id: %d delay: %d\n",cur_drone_id,delay); 
        usleep(delay);
    }
    cur_drone->final_x = airport_x;
    cur_drone->final_y = airport_y;
    cur_drone->dest_img = 'X';
    cur_drone->curr_pos_prev_img = ' ';

    while (((cur_drone->current_x)!=(cur_drone->final_x)) || ((cur_drone->current_y)!=(cur_drone->final_y))){
        moveDrone(cur_drone);
        // srand (time(NULL));
        int delay = rand() % 4 + 1;
        delay = delay * 250000;
        // printf("id: %d delay: %d\n",cur_drone_id,delay); 
        usleep(delay);
    }
    board[(cur_drone->current_x)][(cur_drone->current_y)] = 'X';
    sem_post(&sem_board[cur_drone->current_x][cur_drone->current_y]);
    available_drones.push((cur_drone->id));
    pthread_exit(NULL);
}

// instantiate the ascii board to be empty
void instantiateBoard(){
    for (int i =0; i<board_size; i++){
        board[(board_size - board_size)][i] = '-';
    }
    for (int i =0; i<board_size; i++){
        board[(board_size - 1)][i] = '-';
    }
    for (int x = 1; x < (board_size - 1); x++){
        board[x][board_size - board_size] = '|';
        for (int y = 1; y < (board_size - 1); y++){
            board[x][y] = ' ';
        }
        board[x][(board_size - 1)] = '|';
    }
}

// print the board
void printBoard(){
    for (int x = 0; x < board_size; x++){
        for (int y = 0; y < board_size; y++){
            printf("%c", board[x][y]);
        }
        printf("\n");;
    }
}


// irrelevant method that prints drone information
void printDrone(drone *drone_arg){

    int x = (*drone_arg).current_x;
    int y = (*drone_arg).current_y;
    int fx = (*drone_arg).final_x;
    int fy = (*drone_arg).final_y;
    char c = (*drone_arg).img;

    printf("%c %d %d %d %d\n",c,x,y,fx,fy  );
}