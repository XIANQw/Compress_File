#include "freq.h" /* needed for freq_t */
#include "arbre.h" /* needed for arbre_t */
#include "coding.h" /* constuirecodage */
#include <stdlib.h> /* exit, NULL */
#include <stdio.h> /* FILE*, fopen, fclose*/

void parcours_arbre(arbre_t arbre){
  if(!arbre) return;
  parcours_arbre(left_child(arbre));
  printf("%c : %d\n",get_lettre(arbre),get_code(arbre));
  parcours_arbre(right_child(arbre));
}

int teste_bit (unsigned char c, unsigned int pos){
  return (c&(1<<pos))?1:0;
}

int main(){
  freq_t freqs;
  arbre_t Arbrecodage;
  code_t codage;
  char code;
  int a=0;
  FILE * f = fopen("frequence.txt","r");
  fread(freqs,sizeof(freq_t),1,f);
  Arbrecodage = construirecodage(freqs);
  tablecodage(Arbrecodage,codage);
  while(a<257){
    printf("%c,%o\n",a,codage[a]);
    a++;
  }return 0;
}
