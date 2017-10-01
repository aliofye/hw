#include<stdio.h>
#include <ctype.h>
#include <math.h>

int main(){
    
   	//get score
    unsigned int score;
    scanf("%d", &score);

    //declare constants
    const unsigned short CONVERSION = 7;
    const unsigned short TRIE = 3;
    const unsigned short KICK = 2;

    int pset[7][3] = {{0,0,2}, {0,3,0}, {0,3,2}, {7,0,0}, {7,0,2}, {7,3,0}, {7,3,2}};
    
    int i=0;
    
    for(i=0; i<7; ++i){
        int c = 0;
        int t = 0;
        int k = 0;

        int remainder = score;
        int j = 0;

        for(j=0; j<3; j++){

            int x = pset[i][j];
            int tmp = x;
            if(x != 0){
                while(tmp <= remainder){//12<10
                    
                    tmp+=x;//tmp=12

                    if(j==0){
                        c++;
                    } else if(j==1){
                        t++;//t=3
                    } else{
                        k++;
                    }
                }

                if(tmp < remainder){
                    remainder-= tmp; //remainder = 4

                    if(remainder < pset[i][j+1]){//no
                        remainder+=x;
                    }

                } else{
                    tmp-=x;//tmp=9
                    remainder-=tmp; //remainder = 1

                    if(remainder < pset[i][j+1]){//yes
                        remainder+=x; //remainder = 4
                    }
                }
            }
        }

        printf("%d", c);
        printf("%2d", t);
        printf("%2d\n", k);
    }


    return 0;
}