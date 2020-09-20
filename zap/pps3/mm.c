#include <stdio.h>
#include <stdlib.h>

int mm_recursion(int id)
{
  int sum = 0;
  if(id / 10 == 0) return id;
  
  else{
    while(id != 0){
      sum += id % 10;
      id /= 10;
    }
    return mm_recursion(sum);
  }
}

int main()
{ 
  int sum = 0;
  int c;

  while((c = fgetc(stdin))!= EOF){
    if(c == '\n') continue;
    sum += (int)(c-48);
  }

  printf("%d\n", mm_recursion(sum));
  return 0;
}