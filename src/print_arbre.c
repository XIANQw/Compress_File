#include "../include/freq.h" /* needed for freq_t */
#include "../include/arbre.h" /* needed for arbre_t */
#include "../include/coding.h" /* constuirecodage */
#include <stdlib.h> /* exit, NULL */
#include <stdio.h> /* FILE*, fopen, fclose*/

void usage(char *s){
  fprintf(stderr,"Usage:\n%s filename_to_compress\n",s);
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]){
  freq_t tab;
  arbre_t T;
  FILE *fic;
  if (argc<1)
    usage(argv[0]);
  fic=fopen(argv[1],"r");
  if (fic==NULL)
    usage(argv[0]);
  frequence(tab,fic);
  T=construirecodage(tab);
  dot_arbre(T);
  free_arbre(T);
  fclose (fic);
  return 0;
}
