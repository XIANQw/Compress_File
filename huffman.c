/* Vous n'avez normalement pas besoin d'inclure d'autres fichiers. Si vous le faites, expliquez pourquoi dans votre ReadMe  */
#include "freq.h" /* needed for freq_t */
#include "arbre.h" /* needed for arbre_t */
#include "coding.h" /* coding part (in a separate file sinced shared with uncompression) */
#include <stdio.h>

void usage(char *s){
  s = "makefile";
}

int main(int argc, char *argv[]){
  freq_t freqs;
  code_t codage;
  arbre_t Arbrecodage;
  FILE * stream = fopen(argv[1],"r");
  FILE * file_freqs = fopen("frequence.txt","w+");
  int i;
  if(stream==NULL){
      printf("open file failed!\n");
      exit(1);
  }
  frequence(freqs,stream);
  fwrite(freqs,sizeof(freq_t),1,file_freqs);
  for(i=0;freqs[i];i++) printf("%d : %f",i,freqs[i]);
  rewind(stream);
  Arbrecodage = construirecodage(freqs);
  tablecodage(Arbrecodage,codage);
  text_compression(stream,codage);
  fclose(stream);
  return 0;
}
