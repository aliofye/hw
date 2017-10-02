#include<stdio.h>
#include <ctype.h>
#include <math.h>
 
void printCombinations(int combination[]){
    
    printf("%d", combination[0]);
    printf("%2d", combination[1]);
    printf("%2d", combination[2]);

    printf("\n");
}
void getCombinations(int score, int points[], int combination[], int index){
    // not the last type of coin
        if (index < 2) {
            // if we have not reached our goal value yet
            if (score > 0) {
                int pointValue = points[index];
                if (pointValue <= score) {
                    // try all possible numbers of current coin given the amount
                    // that is left
                    int i=0;
                    for (i = 0; i <= score / pointValue; i++) {
                        combination[index] = i;
                        getCombinations(score - pointValue * i, points, combination, index + 1);
                    }
                    // reset the current coin amount to zero before recursing
                    combination[index] = 0;
                }
                // case when there is a coin whose value is greater than the goal
                else {
                    getCombinations(score, points, combination,index);
                }
            }
            // we've reached our goal, print out the current coin amounts
            else {
                printCombinations(combination);
            }
        }
        // last type of coin
        else {
            // if we have not reached our goal value yet
            if (score > 0) {
                int pointValue = points[index];
                if (pointValue <= score) {
                    // if the remainder of our goal is evenly divisble by our last
                    // coin value, we can make the goal amount
                    if (score % pointValue == 0) {
                        // add last coin amount and print current values out
                        combination[index] = score/pointValue;
                        printCombinations(combination);

                        // reset this coin amount to zero before recursing
                        combination[index] = 0;
                    }
                }
            }
            // we've reached our goal, print out the current coin amounts
            else {
                printCombinations(combination);
            }
    }
}
int main(){
    
   	//get score
    unsigned int score;
    scanf("%d", &score);


    int points[3] = {7,3,2};
    int combination[3] = {0};

    getCombinations(score, points, combination,0);

    return 0;
}