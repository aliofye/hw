//Problem        : A Compliance Problem
//Language       : C
//Compiled Using : GCC
//Version        : GCC 4.9.1
//Input for your program will be provided from STDIN
//Print out all output from your program to STDOUT

#include <stdio.h>
#include "string.h"

#define nchers 500
int palindrome = 1;
  

int check(char* str)
{
    
    int count[nchers] = {0};
  
    
    int i;
    for (i = 0; str[i];  i++)
        count[str[i]]++;
  
    int odd = 0;
    
    for (i = 0; i < nchers; i++)
    {
        if (count[i] & 1)
            odd++;
 
        if (odd > 1)
            return 1;
    }
  
    return 0;
}

int main() {
    char string[500];
    
    scanf("%s", string);

    palindrome = check(string);

    if(palindrome == 0){
      printf("%s\n", "yes");
    } else {
      printf("%s\n", "no");
    }

    return 0;
}