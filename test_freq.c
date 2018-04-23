#include "freq.h"
#include <stdio.h>



int main(){
  /*
   * Le principe du code :
   * 1) on ouvre le fichier à compresser
   * 2) on calcule les frequences de chaque caractere (fonction frequence)
   * 3) on affiche sur l'entrée standard les fréquences calculées (c'est comme cela qu'on stocke le code ; ce n'est pas optimal, mais on s'en contentera pour ce TP)
   */
   FILE* fstream;
   freq_t tab;
   int i;
   fstream = fopen("test.txt","r");
   if(fstream==NULL){
       printf("open file failed!\n");
       exit(1);
   }
   else frequence(tab,fstream);
   for(i=0;i<257;i++){
       printf("%c code : %f\n",i,tab[i]);
   }
  return 0;
}
