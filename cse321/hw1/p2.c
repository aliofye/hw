#include<stdio.h>
#include <math.h>
 

void printCombinations(int combination[]){
    
    printf("%d", combination[0]);
    printf("%c", ' ');
    printf("%d", combination[1]);
    printf("%c", ' ');
    printf("%d", combination[2]);

    printf("\n");
}

void calc(int score){
    
    int maxTouchDown = floor(score / 7);
    int maxFieldGoal = floor(score / 3);
    int maxTwo = floor(score / 2);

    int i=0;
    for (i=0; i<= maxTouchDown; ++i)
    {
        int j=0;
        for(j=0; j<=maxFieldGoal; ++j){
            
            int k=0;
            for(k=0; k<=maxTwo; ++k){
                int result = (7*i) + (3*j) + (2*k);

                if(result == score){
                    int combination[3] = {i,j,k};
                    printCombinations(combination);
                }
            }
        }
    }
}



int main(){
    
   	//get score
    unsigned int score;
    scanf("%d", &score);

    calc(score);

    return 0;
}