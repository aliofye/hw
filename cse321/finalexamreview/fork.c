#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//ref: http://www.ibm.com/developerworks/aix/library/au-toughgame/
char *func ( )
  {
    char * x = (char *)malloc(20);
    return (x); 

  }

int main()
{
  // #1 uninitialized memory
  char *p = (char*)malloc(10); // allocate 10 bytes
  printf("  %s \n", p);
  // always initialize
  memset(p, 'a', 10);
  printf(" %s \n", p);

  //#2 memory overrite
  char *name = (char *) malloc(11); 
  memcpy(name, "This is 321", 11);
  memcpy ( p,name,11); // Problem begins here: p was allocated only 10 bytes
  // but name is 11 bytes!
  printf(" %s \n", p);

  //#3 memory overread
  char *ptr = (char *)malloc(10);
  char name1[20] ;
  memcpy ( name1,ptr,20); // Problem begins here; copying 20 bytes from a 
  // space that was allocated 10 bytes
  printf(" %s \n", ptr);
  printf(" %s \n", name1);


  //#4 memory leak
  char *memoryArea = (char *)malloc(10);
  char *newArea = (char *)malloc(10);
  memoryArea = newArea;

  free (memoryArea); // newArea is leaked

  // correct version free (memmoryArea->newArea; free(memoryArea);

  //#5 improper handling of return value

    func ( ); // Problem lies here
  
    return 0;
}  