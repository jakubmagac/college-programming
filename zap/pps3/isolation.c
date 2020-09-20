#include <stdio.h>

int main()
{

  int n; int layers;
  scanf("%d %d", &n ,&layers);

  for(int i=0;i<n;i++){
    for(int j=0;j<layers;j++){
      getchar();
    }
  }

  printf("%d\n", n);

  return 0;
}