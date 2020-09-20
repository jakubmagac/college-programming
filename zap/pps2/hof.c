#include <stdio.h>
#include <stdlib.h>
#include "hof.h"

int load(struct player list[])
{
  FILE *fp = fopen("score", "r");
  if(fp == NULL){
      return -1;
  }

  struct player tmp;
  int counter = 0;

  for(int i=0;i<10;i++){
    *list[i].name = 0;
    list[i].score = 0;
  }

  for(int i=0;i<10;i++){
    if(fscanf(fp, "%s %d", list[i].name, &list[i].score) == EOF)break;
    counter++;
  }

  for(int i=0;i<10;i++){
    for(int j=0;j<10;j++){
      if(list[i].score > list[j].score){
        tmp = list[i];
        list[i] = list[j];
        list[j] = tmp;
      }
    }
  }

  fclose(fp);
  return counter;
}

bool save(const struct player list[], const int size)
{
  FILE *fp = fopen("score", "w");
  if(fp == NULL){
    return false;
  }

  for(int i=0;i<10;i++){
    if(i < size) fprintf(fp, "%s %d\n", list[i].name, list[i].score);
    else break;
  }

  fclose(fp);
  return true;
}

bool add_player(struct player list[], int* size, const struct player player)
{
  struct player copy[10];
  int counter = 0;
  int check = 0;

  for(int i=0;i<*size;i++){
    copy[i] = list[i];
  }

  //SIZE = 0;
  if(*size == 0){
    list[0] = player;
    check = 1;
    counter = 1;
  }

  // SIZE < 10
  for(int i=0;i<*size;i++){
    if(player.score >= list[i].score){
      list[i] = player;
      counter = i;
      check = 1;
      break;
    }else{
      list[i] = copy[i];
    }
  }

  if(check == 0 && *size < 10){
    list[*size] = player;
    check = 1;
    counter = *size;
  } 

  if(check == 1){
    if(*size+1 <= 10) *size+=1;
    for(int i=counter+1;i<*size;i++)
      list[i] = copy[i-1];
    return true;
  }

  return false;
}
