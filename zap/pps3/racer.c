#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
  int n;  
  double t; 
  double k = 0;
  scanf("%d %lf", &n, &t);
  int s[n], v[n];
  double magnifier;
  double time0 = 0; double time1 = 0;

  for(int i=0;i<n;i++){
    scanf("%d %d", &s[i], &v[i]);
    if(v[i]<0 && abs(v[i]) > k) k = abs(v[i]);
  }

  for(int i=0;i<n;i++){
    if(v[i] != 0) time0 += s[i] / (v[i]);
    if(v[i] + 1 != 0) time1 += s[i] / (v[i]+1);
  }

  if(time0 < time1) magnifier = 0.000001;
  else magnifier = -0.000001;
  
  k += magnifier;

  do{
    time0 = 0;

    for(int i=0;i<n;i++){
      if(v[i]+k != 0) time0 += s[i] / (v[i] + k);
      else{
        time0 = 0;
        break;
      }
    }
    
    if(fabs(t-time0) > 1){
      k += (magnifier * 1000);
    }

    if(magnifier>0 && (float)time0<=(float)t) break;
    if(magnifier<0 && (float)time0>=(float)t) break;
    k += magnifier;
  }while(1);

  if((float)time0 != t) k -= magnifier;
  printf("%f\n", k);
  return 0;
}