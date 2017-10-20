//Problem        : A Compliance Problem
//Language       : C
//Compiled Using : GCC
//Version        : GCC 4.9.1
//Input for your program will be provided from STDIN
//Print out all output from your program to STDOUT

#include <stdio.h>
#include "string.h"

int isPalindrome = 1;

int check(char *str){
    
    int l = 0;
    int h = strlen(str) - 1;
 
    while (h > l)
    {
        if (str[l++] != str[h--])
        {
            return isPalindrome;
        }
    }
    
    isPalindrome = 0;
    return 0;
}

void swap (char *x, char *y)
{
     char temp;
     temp = *x;
     *x = *y;
     *y = temp;
}

void permute(char *a, int i, int n) 
{
    if(isPalindrome == 0){
         return;
    }
    
    int j; 

    if (i == n){

      isPalindrome = check(a);

    } else {
     
        for (j = i; j <= n; j++){
            swap((a+i), (a+j));
            permute(a, i+1, n);
            swap((a+i), (a+j)); 
        }
    }
}

int main() {
    char string[500];
    
    scanf("%s", string);

    permute(string,0, strlen(string)-1);

    if(isPalindrome == 0){
      printf("%s\n", "yes");
    } else {
      printf("%s\n", "no");
    }

    return 0;
}