#include<stdio.h>
#include <ctype.h>
#include <math.h>

int main(){
    
   	char X[10000];
	char Y[10000];

	scanf("%s", X);
	scanf("%s", Y);

	int xBase=0;
	int yBase=0;
	int max = 0;
	int xDigits = 0;
	int yDigits = 0;

    int i = 0;

	for(i=0; X[i] != '\0'; i++){

		xDigits++;

		int count = 0;

		char c = X[i];
        
        if (c >= '0' && c <= '9') {

            count = c - '0';

        } else if (c >= 'A' && c <= 'Z') {

            count = 10 + (c - 'A');

        }

        if (count > max) {

            max = count;
        }
	}

	xBase = max+1;

	max = 0;

	for(i=0; Y[i] != '\0'; i++){

		yDigits++;

		int count = 0;

		char c = Y[i];
        
        if (c >= '0' && c <= '9') {
            count = c - '0';

        } else if (c >= 'A' && c <= 'Z') {

            count = 10 + (c - 'A');

        }

        if (count > max) {
            max = count;
        }
	}

	
	yBase = max+1;

  
    long long int X_10 = 0;
    long long int Y_10 = 0;


    for (i = 0; X[i] != '\0'; ++i)
    {
    	xDigits--;
    	
    	char c = X[i];
    	
    	if (c >= '0' && c <= '9') {

            c = c - '0';

        } else if (c >= 'A' && c <= 'Z') {

            c = 10 + (c - 'A');

        }

    	int p = pow(xBase, xDigits);
    	
    	X_10 += (c * p); 

    }

    for (i = 0; Y[i] != '\0'; ++i)
    {
    	yDigits--;
    	
    	char c = Y[i];
    	
    	if (c >= '0' && c <= '9') {

            c = c - '0';

        } else if (c >= 'A' && c <= 'Z') {

            c = 10 + (c - 'A');
        }

    	int p = pow(yBase, yDigits);
    	
    	Y_10 += (c * p); 

    }

    long long int total = X_10 + Y_10;

    
    printf("%llu\n", total);

    


    return 0;
}