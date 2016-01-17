#include <stdlib.h>
#include <stdio.h>

void printFunc(const char* s)
{
  printf("%s\n", s);
}

int main()
{
  char charArray[6] = {'s', 't', 'r', 'i', 'n', 'g'};
  printFunc(&charArray[0]);
  //printf("ptr2 : %X\n", ptr2);
  return 0;
}
