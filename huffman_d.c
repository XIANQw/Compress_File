#include "freq.h" /* freq_t */
#include "arbre.h" /* arbre_t */
#include "coding.h" /* code (mis a part car partage avec le decoding) */
#include <stdio.h>

int teste_bit (unsigned char c, unsigned int pos){
  return (c&(1<<pos))?1:0;
}


int main(){
  /*
   * Le principe du code :
   * 1) La lecture se fait sur l'entrée standard
   * 2) On lit les frequences en début de fichier (scanf)
   * 3) On construit le code à partir des fréquences (fonction construirecodage)
   * 4) On decode le fichier (a priori faisable directement dans le main)
   */
  freq_t freqs;
  arbre_t Arbrecodage;
  arbre_t *iterator;
  char code;
  int tmp, pos=6,output=0;
  FILE * f = fopen("frequence.txt","r");
  fread(freqs,sizeof(freq_t),1,f);
  Arbrecodage = construirecodage(freqs);
  iterator = &Arbrecodage;
  while((tmp=scanf("%c",&code))!=-1){
    if(output) pos = 6;
    for(;pos>-1;pos--){
      if(est_feuille(*iterator)){
        putchar((*iterator)->lettre);
        output = 1;
        iterator = &Arbrecodage;
        break;
      }
      if(teste_bit(code,pos))
      iterator = &((*iterator)->right);
      else iterator = &((*iterator)->left);
      output = 0;
    }

    if(est_feuille(*iterator)){
      putchar((*iterator)->lettre);
      output = 1;
      iterator = &Arbrecodage;
    }
    pos = 7;
  }
  return 0;
}
