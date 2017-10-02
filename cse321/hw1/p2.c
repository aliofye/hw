#include<stdio.h>
#include <ctype.h>
#include <math.h>
 
void printCombinations(int combination[]){
    
    printf("%d", combination[0]);
    printf("%c", ' ');
    printf("%d", combination[1]);
    printf("%c", ' ');
    printf("%d", combination[2]);

    printf("\n");
}

void getCombinations(int score, int points[], int combination[], int index){
        if (index < 2) {
            if (score > 0) {
                int pointValue = points[index];
                if (pointValue <= score) {
                    
                    int i=0;
                    for (i = 0; i <= score / pointValue; i++) {
                        combination[index] = i;
                        getCombinations(score - pointValue * i, points, combination, index + 1);
                    }
                    combination[index] = 0;
                }
                else {
                    getCombinations(score, points, combination,index);
                }
            }
            else {
                printCombinations(combination);
            }
        }
        else {
            if (score > 0) {
                int pointValue = points[index];
                if (pointValue <= score) {
                    if (score % pointValue == 0) {
                        combination[index] = score/pointValue;
                        printCombinations(combination);

                        combination[index] = 0;
                    }
                }
            }
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