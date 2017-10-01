#include<stdio.h>
#include <ctype.h>
#include <math.h>

int duplicates[100][3];
int pos = 0;
char last[3];

void printArray(int arr[], int arr_size, int score){
    //declare constants
    const unsigned short CONVERSION = 7;
    const unsigned short TRIE = 3;
    const unsigned short KICK = 2;

    int c=0;
    int t=0;
    int k=0;


    int i;
    for (i = 0; i < arr_size; i++){
        switch(arr[i]){
            case 2:
                k++;
                break;
            case 3:
                t++;
                break;
            case 7:
                c++;
                break;
        }
    }

    int total = (c*CONVERSION) + (t*TRIE) + (k*KICK);
    char current[] = {(char) c, (char) t, (char) k};
    
    //check equality
    int eqCount = 0;
    for(i=0; i<3; ++i){
        if(last[i] == current[i]){
            eqCount++;
        }
    }

    if(total == score && eqCount!=3){
        printf("%d", c);
        printf("%2d", t);
        printf("%2d\n", k);

        last[0] = (char) c;
        last[1] = (char) t;
        last[2] = (char) k;

        /*
        duplicates[pos][0] = c;
        duplicates[pos][1] = t;
        duplicates[pos][2] = k;

        pos++;*/
    }  
}

void printCompositions(int n, int i, int score){
        /* array must be static as we want to keep track
        of values stored in arr[] using current calls of
        printCompositions() in function call stack*/
        static int arr[100];
         
        if (n == 0)
        {
            printArray(arr, i, score);
        }
        else if(n > 0)
        {
            int k; 
            for (k = 2; k <= 7; k++)
            {
                arr[i]= k;
                printCompositions(n-k, i+1, score);
            }
        }
    }
 

int main(){
    
   	//get score
    unsigned int score;
    scanf("%d", &score);


    int points[3] = {7,3,2};

    printCompositions(score, 0, score);

    /*int i=0;
    for(i=0; i<100; ++i){
        
        int j=0;
        for (j=0; j < 3; ++j){
           printf("%d", duplicates[i][j]);
        }

        printf("\n");
    }*/

    return 0;
}