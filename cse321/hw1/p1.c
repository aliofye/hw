#include<stdio.h>
#include <ctype.h>
#include <math.h>

int main(){
    
   	char X[99999];
	char Y[99999];

	scanf("%s", X);
	scanf("%s", Y);

	unsigned short baseX=0;
	unsigned short baseY=0;
	//min is used to find the minimum base number
	unsigned short min = 0;
	
	unsigned short digitsX = 0;
	unsigned short digitsY = 0;

    unsigned short i = 0;

	//find the minimum base for X[]
	for(i=0; X[i] != '\0'; i++){

		digitsX++;

		int v = 0;

		char c = X[i];
        
        if (c >= '0' && c <= '9') {
            v = c - '0';
        } else if (c >= 'A' && c <= 'Z') {
            v = 10 + (c - 'A');
        }
        if (v > min) {
            min = v;
        }
	}

	baseX = min+1;

	min = 0;

	//find the minimum base for Y[]
	for(i=0; Y[i] != '\0'; i++){
		//printf("%c\n", X[i]);

		digitsY++;

		int v = 0;

		char c = Y[i];
        
        if (c >= '0' && c <= '9') {
            v = c - '0';
        } else if (c >= 'A' && c <= 'Z') {
            v = 10 + (c - 'A');
        }

        if (v > min) {
            min = v;
        }
	}

	
	baseY = min+1;

  
    //convert X[] and Y[] to base10
    long long int X_10 = 0;
    long long int Y_10 = 0;


    for (i = 0; X[i] != '\0'; ++i)
    {
    	digitsX--;
    	
    	char c = X[i];
    	
    	if (c >= '0' && c <= '9') {
            c = c - '0';
        } else if (c >= 'A' && c <= 'Z') {
            c = 10 + (c - 'A');
        }

    	int p = pow(baseX, digitsX);
    	
    	X_10 += (c * p); 

    }

    for (i = 0; Y[i] != '\0'; ++i)
    {
    	digitsY--;
    	
    	char c = Y[i];
    	
    	if (c >= '0' && c <= '9') {
            c = c - '0';
        } else if (c >= 'A' && c <= 'Z') {
            c = 10 + (c - 'A');
        }

    	int p = pow(baseY, digitsY);
    	
    	Y_10 += (c * p); 

    }

    long long int total = X_10 + Y_10;

    
    printf("%llu\n", total);

    


    return 0;
}