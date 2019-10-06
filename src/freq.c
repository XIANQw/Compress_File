#include "../include/freq.h"
#include <stdio.h>
#include <stdlib.h>


void frequence(freq_t tab, FILE *f){
  int i,length=0;
  int read;
  for(i=0;i<MAXSIZE;i++) tab[i]=0;
  while((read = fgetc(f))!= EOF) length++;
  rewind(f);
  while((read=fgetc(f))!=EOF) tab[read]+=(1.0/length);

  return ;
}
